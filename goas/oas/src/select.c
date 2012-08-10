#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "record.h"
#include "select.h"

/* Accurate mesaures of current column & record counts. */
unsigned int NUM_COLS;
unsigned int NUM_RECS;

/* This will hold the indices of each key. */
unsigned int *key_array;

/* Removes records from the list of records that don't match the arguments
 * found in the keys array. */
r_list *select_oas(r_list *relation, const char **keys) {
  /* Make sure there is something in the relation first. */
  if (relation == NULL) {
    printf("Empty relation passed to selection.\n");
    return relation;
  }
  
  unsigned int i;
  unsigned int len_keys=1;
  for (i=0;keys[i];i++) len_keys++;
  unsigned int num_keys = len_keys / 4;

  key_array = malloc(num_keys * sizeof(unsigned int));
  check_malloc(key_array, "select()");
  
  unsigned int is_selectable = 0;
  unsigned int j,k;
  

  /* Find out which index each key is associated with. */
  for (i=0,k=0; i<len_keys; i+=4) {
    key_array[k] = -1;
    for (j=0; j<NUM_COLS; j++) {
      if (!strcmp(keys[i], relation->c_names[j])) {
	key_array[k] = j;
	is_selectable = 1;
	break;
      }
    }
    /* This key isn't part of this relation. */
    if (key_array[k] == -1)
      printf("KEY: [%s] not found in this relation and is not being used for this"
	     " selection.\n",keys[i]);
    else
      k++;
  }

  /* No indexes match these keys...return the original relation. */
  if (!is_selectable) return relation;

  /* There were keys in this projection not actually in the relation. */
  if (k != (i/4)) {
      num_keys = k;
      key_array = realloc(key_array, num_keys * sizeof(unsigned int));
  }
  unsigned int num_kept=0;
  unsigned int keep[NUM_RECS];

  /* Determine which records fit the selection. */
  for (i=0; i<NUM_RECS; i++) {
    if (evaluate(&(relation->records[i]), keys, num_keys, len_keys)) {
      keep[num_kept++] = i;
    }
    else {
      for (j=0; j<NUM_COLS; j++) {
	free(relation->records[i].data[j]);
      }
      free(relation->records[i].data);
    }
  }
  NUM_RECS = num_kept;

  /* Move the records that were kept to the beginning of the records array. */
  for (j=0; j<num_kept; j++) 
    if (j != keep[j])
      relation->records[j] = relation->records[keep[j]];

  /* Tidy up memory and the records count. */
  relation->records = realloc(relation->records,
			      (num_kept) * sizeof(record));
  relation->rec_count = NUM_RECS;

  free(key_array);

  return relation;
} /* select() */

/* Evaluates ALL the predicates found in keys. */
int evaluate(record *rec, const char **keys, unsigned int num_keys,
	     unsigned int len_keys) {
  unsigned int i,j;
  int result[num_keys];
  int r=0;
  /* i:keys, j:data */

  for (i=3,j=0;j<num_keys;i+=4,j++) {
    switch ((char)(*keys[i-2])) {
    case '=': r = !strcmp(rec->data[key_array[j]],keys[i-1]); break;
    case '>': r = atoi(rec->data[key_array[j]]) > atoi(keys[i-1]); break;
    case '<': r = atoi(rec->data[key_array[j]]) < atoi(keys[i-1]); break;
    }

    result[j] = r;
  }

  for (i=3,j=0;j<num_keys-1;i+=4,j++) {
    switch ((char)(*keys[i])) {
    case '&': result[j] = result[j] && result[j+1]; result[j+1] = result[j]; break;
    case '|': result[j] = result[j] || result[j+1]; result[j+1] = result[j]; break;
    }
  }

  for (i=0;i<num_keys;i++) 
    if (result[i])
      return 1;
  return 0;
} /* evaluate() */
