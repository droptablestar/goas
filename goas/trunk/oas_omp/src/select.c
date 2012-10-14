#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "record.h"
#include "select.h"

unsigned int NUM_COLS;
unsigned int NUM_RECS;

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
    if (key_array[k] == -1)
      printf("KEY: [%s] not found in this relation and is not being used for this"
	     " selection.\n",keys[i]);
    else
      k++;
  }

  if (!is_selectable) return relation;

  /* There were keys in this projection not actually in the relation. */
  if (k != i) {
    num_keys = k;
    key_array = realloc(key_array, num_keys * sizeof(unsigned int));
  }

  if (NUM_RECS >= REC_THRESH) 
    relation = par_select(relation, keys, num_keys, len_keys);
  else
    relation = seq_select(relation, keys, num_keys, len_keys);

  return relation;
} /* select_oas() */

r_list *par_select(r_list *relation, const char **keys,
			unsigned int num_keys, unsigned int len_keys) {
  int num_kept = 0;
  int keep[relation->rec_count];
  int i,j,k;

  r_list *tmp_rel = init_r_list(relation->c_names);
  #pragma omp parallel \
    shared(relation, keys, num_keys, len_keys, num_kept, keep, tmp_rel) \
    private(i,j) 
  {
    #pragma omp for schedule(dynamic)
    /* Determine which records fit the selection. */
    for (i=0;i<relation->rec_count;i++) {
      if (evaluate(&(relation->records[i]), keys, num_keys, len_keys))
	#pragma omp critical
	tmp_rel->records[num_kept++] = relation->records[i];
      else {
      	for (j=0; j<NUM_COLS; j++) {
      	  free(relation->records[i].data[j]);
      	}
      	free(relation->records[i].data);
      }
    }

    #pragma omp for schedule(dynamic)
    for (j=0; j<num_kept; j++) 
       relation->records[j] = tmp_rel->records[j];
  } /* end omp parallel */
  
  /* Tidy up memory and the records count. */
  relation->records = realloc(relation->records,
  			      (num_kept) * sizeof(record));
  NUM_RECS = num_kept;
  relation->rec_count = num_kept;
  free(key_array);

  return relation;
} /* par_select() */

r_list *seq_select(r_list *relation, const char **keys,
			unsigned int num_keys, unsigned int len_keys) {

  int num_kept = 0;
  int keep[relation->rec_count];
  int i,j,k;

  /* Determine which records fit the selection. */
  for (i=0;i<relation->rec_count;i++) {
    if (evaluate(&(relation->records[i]), keys, num_keys, len_keys))
      keep[num_kept++] = i;
      else {
	for (j=0; j<NUM_COLS; j++) {
	  free(relation->records[i].data[j]);
	}
	free(relation->records[i].data);
      }
    }
  
    for (j=0; j<num_kept; j++) 
      relation->records[j] = relation->records[keep[j]];
    relation->records = realloc(relation->records,
				(num_kept) * sizeof(record));
    
    /* Tidy up memory and the records count. */
    NUM_RECS = num_kept;
    relation->rec_count = num_kept;

    free(key_array);
    
    return relation;
} /*seq_select() */

/* Evaluates ALL the predicates found in keys. */
int evaluate(record *rec_p, const char **keys, unsigned int num_keys,
	     unsigned int len_keys) {
  record rec = *rec_p;
  unsigned int i,j;
  int result[num_keys];
  int r=0;
  /* i:keys, j:data */

  for (i=3,j=0;j<num_keys;i+=4,j++) {
    switch ((char)(*keys[i-2])) {
    case '=': r = !strcmp(rec.data[key_array[j]],keys[i-1]); break;
    case '>': r = atoi(rec.data[key_array[j]]) > atoi(keys[i-1]); break;
    case '<': r = atoi(rec.data[key_array[j]]) < atoi(keys[i-1]); break;
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
