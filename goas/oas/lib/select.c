#include <stdio.h>
#include <stdlib.h>

#include "record.h"
#include "select.h"

unsigned int *key_array;

/* Removes records from the list of records that don't match the arguments
 * found in the keys array. */
r_list *select(r_list *relation, const char **keys) {
  /* Make sure there is something in the relation first. */
  if (relation == NULL) {
    printf("Empty relation passed to selection.\n");
    return relation;
  }
  
  int i;
  unsigned int len_keys=1;
  for (i=0;keys[i];i++) len_keys++;
  unsigned int num_keys = len_keys / 4;

  key_array = malloc(num_keys * sizeof(int));
  check_malloc(key_array, "select()");
  
  unsigned int is_selectable = 0;
  int j,k;
  
  /* Find out which index each key is associated with. */
  for (i=0,k=0; i<len_keys; i+=4,k++) {
    for (j=0; j<relation->records[0].col_count; j++) {
      if (!strcmp(keys[i], relation->records[0].names[j])) {
	key_array[k] = j;
	is_selectable = 1;
	break;
      }
    }
  }
  
  /* No indexes match these keys...return the original relation. */
  if (!is_selectable) return relation;
  
  k=0;
  int num_kept=0;
  int r_count = relation->rec_count;
  int keep[r_count];
  /* Determine which records fit the selection. */
  for (i=0; i<r_count; i++) {
    if (evaluate(&(relation->records[i]), keys, num_keys, len_keys)) {
      keep[num_kept++] = i;
    }
    else {
      for (j=0; j<relation->records[i].col_count; j++) {
	free(relation->records[i].names[j]);
	free(relation->records[i].data[j]);
      }
      free(relation->records[i].names);
      free(relation->records[i].data);
    }
  }

  /* Move the records that were kept to the beginning of the records array. */
  for (j=0; j<num_kept; j++) 
    relation->records[j] = relation->records[keep[j]];

  /* Tidy up memory and the records count. */
  relation->records = realloc(relation->records,
			      (num_kept) * sizeof(record));
  relation->rec_count = num_kept;
  free(key_array);
} /* select() */

/* Implements the = predicate. */
int eq(const char *a, const char *b) {
  if (!strcmp(a,b)) return 1;
  else return 0;
} /* eq() */

/* Implements the greater than predicate. Currently only suited for digits. */
int gt(const char *a, const char *b) {
  if (atoi(a) > atoi(b)) return 1;
  else return 0;
} /* gt() */

/* Implements the less than predicate. Currently only suited for digits. */
int lt(const char *a, const char *b) {
  if (atoi(a) < atoi(b)) return 1;
  else return 0;
} /* lt() */

/* Evaluates ALL the predicates found in keys. */
int evaluate(record *rec, const char **keys, int num_keys, int len_keys) {
  int i,j;
  int result[num_keys];
  /* i:keys, j:data */
  for (i=3,j=0;j<num_keys;i+=4,j++) {
    result[j] = eval_part(rec, keys, j, i-3);
  }

  for (i=3,j=0;j<num_keys-1;i+=4,j+=2) {
    switch ((char)(*keys[i])) {
    case '&': result[j] = result[j] && result[j+1]; result[j+1]=0; break;
    case '|': result[j] = result[j] || result[j+1]; result[j+1]=0; break;
    }
  }

  for (i=0;i<num_keys;i++) 
    if (result[i] == 1)
      return 1;
  return 0;
} /* evaluate() */

/* Evaluates one predicate from the keys array. */
int eval_part(record *rec, const char **keys, int d_index, int k_index) {
  int result;
  switch ((char)(*keys[k_index+1])) {
  case '=': result = eq(rec->data[key_array[d_index]],keys[k_index+2]); break;
  case '>': result = gt(rec->data[key_array[d_index]],keys[k_index+2]); break;
  case '<': result = lt(rec->data[key_array[d_index]],keys[k_index+2]); break;
  }

  return result;
} /* eval_part() */
