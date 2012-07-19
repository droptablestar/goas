#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#include "record.h"
#include "project.h"


/* Takes a relation and an array of keys as parameters. Returns the relation
 * with only the keys remaining in each record. The array keys should always
 * end with NULL. */
r_list *project(r_list *relation, const char **keys) {
  /* This is an array that will hold which index each key is in the names
   * and data arrays of each record. */
  unsigned int *key_array;
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
      printf("KEY: [%s] not found in this relation and is not being used for this"
	     " projection.\n",keys[i]);
  }

  /* No columns match in this relation. */
  if (!is_projectable) return relation;

  /* There were keys in this projection not actually in the relation. */
  if (k != i) {
    num_keys = k;
    key_array = realloc(key_array, num_keys * sizeof(int));
  }

  /* Sort the array of indices (key_array). */
  qsort(key_array, num_keys, sizeof(int), int_cmp);

  int keep = 0;
  int r_count = relation->rec_count;

  /* Go through each column and remove it if it isn't the project list. */
  for (i=0; i<r_count; i++) {
    int c_count = relation->records[i].col_count;
    for (j=0,k=0; j<c_count; j++) {
      if (j != key_array[k]) {
    	free(relation->records[i].names[j]);
    	free(relation->records[i].data[j]);
      }
      else
    	k++;
    }
  }

  /* Go through each record and move the columns that weren't freed to the
   * beginning of the array. */
  int back;
  for (i=0; i<r_count; i++) {
    back = 1;
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

  free(key_array);
  
  return relation;
} /* project() */

/* This is the callback function for sorting keys. */
int int_cmp(const void *a, const void *b) {
  int *ia = (int *)a;
  int *ib = (int *)b;

  return *ia - *ib;
} /* int_cmp() */
