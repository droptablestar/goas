#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#include "record.h"
#include "project.h"


unsigned int *key_array;
unsigned int NUM_COLS;
unsigned int NUM_RECS;

/* Takes a relation and an array of keys as parameters. Returns the relation
 * with only the keys remaining in each record. The array keys should always
 * end with NULL. */
r_list *project(r_list *relation, const char **keys) {
  /* This is an array that will hold which index each key is in the names
   * and data arrays of each record. */
  unsigned int num_keys = 0;
  /* Make sure there is something in the relation first. */
  if (relation == NULL) {
    printf("Empty relation passed to projection.\n");
    return relation;
  }

  int i,j,k,m;

  /* Find out how many keys there are and allocate enough memory for the
   * keys array. */
  for (i=0;keys[i];i++) num_keys++;
  key_array = malloc(num_keys * sizeof(unsigned int));

  /* will let us check to see if any keys matched in this relation. */
  unsigned int is_projectable = 0;

  /* Find out which index each key is associated with. */
  for (i=0,k=0; i<num_keys; i++) {
      key_array[k] = -1;
      for (j=0; j<NUM_COLS; j++) {
	  if (!strcmp(keys[i], relation->c_names[j])) {
	      key_array[k] = j;
	      is_projectable = 1;
	      break;
	  }
      }
      if (key_array[k] == -1)
	  printf("KEY: [%s] not found in this relation and is not being used for this"
		 " projection.\n",keys[i]);
      else
	  k++;
  }
  
  /* No columns match in this relation. */
  if (!is_projectable) {free(key_array); return relation;}
  
  /* There were keys in this projection not actually in the relation. */
  if (k != i) {
    num_keys = k;
    key_array = realloc(key_array, num_keys * sizeof(unsigned int));
  }

  /* Sort the array of indices (key_array). */
  qsort(key_array, num_keys, sizeof(int), int_cmp);
  if (relation->rec_count > REC_THRESH)
    relation = par_project(relation, num_keys);
  else
    relation = seq_project(relation, num_keys);

  return relation;
} /* project() */

r_list *par_project(r_list *relation, unsigned int num_keys) {
  int i,j,k,m, is_valid;

  #pragma omp parallel			  \
    shared(relation, key_array, num_keys) \
    private(i,j,k,m,is_valid) 
  {
    #pragma omp for schedule(dynamic)
    for (i=0; i<NUM_RECS; i++) {
      for (j=0; j<NUM_COLS; j++) {
	is_valid = 0;
	for (k=key_array[0],m=0; m<num_keys; m++,k=key_array[m]) {
	  if (k==j) {
	    is_valid = 1;
	    break;}
	}
	if (!is_valid) {
	  free(relation->records[i].data[j]);
	}
      }
    }

    #pragma omp for schedule(dynamic)
    for (i=0; i<NUM_RECS; i++) {
      for (j=0; j<num_keys; j++) 
	relation->records[i].data[j] = relation->records[i].data[key_array[j]];

      relation->records[i].data = realloc(relation->records[i].data,
					  (num_keys) * sizeof(char *));
    }
  } /* end omp parallal */
  NUM_COLS = num_keys;

  free(key_array);
  
  return relation;
} /* par_project() */

r_list *seq_project(r_list *relation, unsigned int num_keys) {
  int i,j,k,m, is_valid;
  for (i=0; i<NUM_RECS; i++) {
    for (j=0; j<NUM_COLS; j++) {
      is_valid = 0;
      for (k=key_array[0],m=0; m<num_keys; m++,k=key_array[m]) {
	if (k==j) {
	  is_valid = 1;
	  break;}
      }
      if (!is_valid) 
	free(relation->records[i].data[j]);
    }
  }
  
  for (i=0; i<NUM_RECS; i++) {
    for (j=0; j<num_keys; j++) 
      relation->records[i].data[j] = relation->records[i].data[key_array[j]];

    relation->records[i].data = realloc(relation->records[i].data,
					(num_keys) * sizeof(char *));
  }

  NUM_COLS = num_keys;
  free(key_array);
  
  return relation;
} /* seq_project() */
