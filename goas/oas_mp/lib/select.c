#include <stdio.h>
#include <stdlib.h>

#include "record.h"
#include "select.h"

unsigned int *key_array;

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
  
  if (relation->rec_count > REC_THRESH) 
    relation = parallel_select(relation, keys, num_keys, len_keys);
  else
    relation = sequential_select(relation, keys, num_keys, len_keys);
    
  return relation;
}

r_list *parallel_select(r_list *relation, const char **keys,
			unsigned int num_keys, unsigned int len_keys) {
  int num_kept = 0;
  int keep[relation->rec_count];
  int i,j,k;

  #pragma omp parallel \
    shared(relation, keys, num_keys, len_keys, num_kept) \
    private(i,j)
  {
    int chunk = relation->rec_count / omp_get_num_threads();
    #pragma omp for schedule(dynamic,chunk)

    /* Determine which records fit the selection. */
    for (i=0;i<relation->rec_count;i++) {
      if (evaluate(&(relation->records[i]), keys, num_keys, len_keys)) {
	#pragma omp critical
	keep[num_kept++] = i;
      }
      else {
	for (j=0;j<relation->records[i].col_count;j++) {
	  free(relation->records[i].names[j]);
	  free(relation->records[i].data[j]);
	}
	free(relation->records[i].names);
	free(relation->records[i].data);
      }
    }
  } /* end omp parallel */
    
  for (j=0; j<num_kept; j++) 
    relation->records[j] = relation->records[keep[j]];
  relation->records = realloc(relation->records,
			      (num_kept) * sizeof(record));
    
  /* Tidy up memory and the records count. */
  relation->rec_count = num_kept;
  free(key_array);

  return relation;
}
r_list *sequential_select(r_list *relation, const char **keys,
			unsigned int num_keys, unsigned int len_keys) {

  int num_kept = 0;
  int keep[relation->rec_count];
  int i,j,k;

  #pragma omp parallel \
    shared(relation, keys, num_keys, len_keys, num_kept) \
    private(i,j)
  {
    int chunk = relation->rec_count / omp_get_num_threads();
    #pragma omp for schedule(dynamic,chunk)

    /* Determine which records fit the selection. */
    for (i=0;i<relation->rec_count;i++) {
      if (evaluate(&(relation->records[i]), keys, num_keys, len_keys)) {
	#pragma omp critical
	keep[num_kept++] = i;
      }
      else {
	for (j=0;j<relation->records[i].col_count;j++) {
	  free(relation->records[i].names[j]);
	  free(relation->records[i].data[j]);
	}
	free(relation->records[i].names);
	free(relation->records[i].data);
      }
    }
  } /* end omp parallel */
    
  for (j=0; j<num_kept; j++) 
    relation->records[j] = relation->records[keep[j]];
  relation->records = realloc(relation->records,
			      (num_kept) * sizeof(record));
    
  /* Tidy up memory and the records count. */
  relation->rec_count = num_kept;
  free(key_array);

  return relation;
} /* sequential_select() */

int eq(const char *a, const char *b) {
  /* printf("EQ %s %s\n",a,b); */
  if (!strcmp(a,b)) return 1;
  else return 0;
} /* eq() */

int gt(const char *a, const char *b) {
  /* printf("GT %s %s\n",a,b); */
  if (atoi(a) > atoi(b)) return 1;
  else return 0;
} /* eq() */

int lt(const char *a, const char *b) {
  /* printf("LT %s %s\n",a,b); */
  if (atoi(a) < atoi(b)) return 1;
  else return 0;

} /* lt() */

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
    
int eval_part(record *rec, const char **keys, int d_index, int k_index) {
  int result;
  switch ((char)(*keys[k_index+1])) {
  case '=': result = eq(rec->data[key_array[d_index]],keys[k_index+2]); break;
  case '>': result = gt(rec->data[key_array[d_index]],keys[k_index+2]); break;
  case '<': result = lt(rec->data[key_array[d_index]],keys[k_index+2]); break;
  }

  return result;
} /* eval_part() */
