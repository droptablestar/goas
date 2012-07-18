#include <stdio.h>
#include <stdlib.h>

#include "record.h"
#include "project.h"

unsigned int *key_array;

/* Takes a relation and an array of keys as parameters. Returns the relation
 * with only the keys remaining in each record. */
r_list *project(r_list *relation, const char **keys) {
  /* Make sure there is something in the relation first. */
  if (relation == NULL) {
    printf("Empty relation passed to projection.\n");
    return relation;
  }

  int i,j,k,m;
  unsigned int num_keys = 0;

  for (i=0;keys[i];i++) num_keys++;
  key_array = malloc(num_keys * sizeof(int));

  /* will let us check to see if any keys matched in this relation. */
  unsigned int is_projectable = 0;
  unsigned int c_count = relation->records[0].col_count;
  /* Find out which index each key is associated with. */
  for (i=0,k=0; i<num_keys; i++) {
    key_array[k] = -1;
    for (j=0; j<c_count; j++) {
      if (!strcmp(keys[i], relation->records[0].names[j])) {
	key_array[k++] = j;
	is_projectable = 1;
	break;
      }
    }
    if (key_array[k] == -1)
      printf("KEY: %s not found in this relation and is not being used for this"
	     " projection.\n",keys[i]);
  }
  /* No columns match in this relation. */
  if (!is_projectable) return relation;

  /* There were keys in this projection not actually in the relation. */
  if (k != i) {
    num_keys = k;
    key_array = realloc(key_array, num_keys * sizeof(int));
  }
  
  int is_valid;
  qsort(key_array, num_keys, sizeof(int), int_cmp);
#pragma omp parallel  shared(relation, key_array, num_keys) private(i,j,k,m,is_valid)
  {
    omp_set_num_threads(8);
    int chunk = relation->rec_count / omp_get_num_threads();
#pragma omp for schedule(dynamic,chunk)	
    for (i=0; i<relation->rec_count; i++) {
      for (j=0; j<relation->records[i].col_count; j++) {
	is_valid = 0;
	for (k=key_array[0],m=0; m<num_keys; m++,k=key_array[m]) {
	  if (k==j) {
	    is_valid = 1;
	    break;}
	}
	if (!is_valid) {
	  free(relation->records[i].names[j]);
	  free(relation->records[i].data[j]);
	}
      }
    }
    
    int back;
#pragma omp for schedule(dynamic,chunk) 
    for (i=0; i<relation->rec_count; i++) {
      back = 1;
      int c_count = relation->records[i].col_count;
      for (j=0; j<num_keys; j++) {
	relation->records[i].names[j] = relation->records[i].names[key_array[j]];
	relation->records[i].data[j] = relation->records[i].data[key_array[j]];
      }
      relation->records[i].names = realloc(relation->records[i].names,
					   (num_keys) * sizeof(char *));
	relation->records[i].data = realloc(relation->records[i].data,
					    (num_keys) * sizeof(char *));
	
	relation->records[i].col_count = num_keys;
    }
  } /* end omp parallal */

  free(key_array);
  
  return relation;
} /* project() */

/* This is the callback function for sorting keys. */
int int_cmp(const void *a, const void *b) {
  int *ia = (int *)a;
  int *ib = (int *)b;

  return *ia - *ib;
} /* int_cmp() */
