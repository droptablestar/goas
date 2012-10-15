#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "record.h"
#include "sort.h"

unsigned int *key_array;
unsigned int num_keys;

/* Takes a relation and array of keys. Returns the relation with
 * relations->records sorted on those keys. */
r_list *sort(r_list *relation, const char **keys, s_order sort_order) {
  num_keys = 0;
  /* Check for empty relation. */
  if (relation->records == NULL) {
    printf("Empty relation passed to sort.\n");
    exit(1);
  }
  
  int i,j,k;
  for(i=0;keys[i];i++) num_keys++;

  key_array = malloc(num_keys * sizeof(int));

  /* will let us check to see if any keys matched in this relation. */
  unsigned int is_sortable = 0;

  /* Find out which index each key is associated with. */
  for (i=0,k=0; i<num_keys; i++) {
    key_array[k] = -1;
    for (j=0; j<relation->records[0].col_count; j++) {
      if (!strcmp(keys[i], relation->records[0].names[j])) {
	key_array[k] = j;
	is_sortable = 1;
	break;
      }
    }
    if (key_array[k++] == -1)
      printf("KEY: %s not found in this relation and is not being used for this"
	     " sort.\n",keys[i]);
  }


  /* There were keys in this projection not actually in the relation. */
  if (k != i) {
    num_keys = k;
    key_array = realloc(key_array, num_keys * sizeof(int));
  }

  if (is_sortable) {
    if (sort_order == ASC)
      qsort(relation->records, relation->rec_count, sizeof(record), struct_cmp_asc);
    else
      qsort(relation->records, relation->rec_count, sizeof(record), struct_cmp_desc);
  }

  free(key_array);
  return relation;
} /* sort() */

/* This is the callback function for qsort (sorting in ascending order. Takes two
 * records and returns
 * an int determining which is the smallest. */
int struct_cmp_asc(const void *a, const void *b) {
  record *ia = (record *)a;
  record *ib = (record *)b;

  int i,cmp_result;
  for (i=0; i<num_keys; i++) {
    if (isdigit(ia->data[key_array[i]][0]) && isdigit(ib->data[key_array[i]][0]))
      cmp_result = atoi(ia->data[key_array[i]]) - atoi(ib->data[key_array[i]]);
    else 
      cmp_result = strcmp(ia->data[key_array[i]], ib->data[key_array[i]]);
    if (cmp_result) return cmp_result;
  }
  return 1;
} /* struct_cmp_asc() */

/* This is the callback function for qsort (sorting in ascending order. Takes two
 * records and returns
 * an int determining which is the smallest. */
int struct_cmp_desc(const void *a, const void *b) {
  record *ia = (record *)a;
  record *ib = (record *)b;

  int i,cmp_result;
  for (i=0; i<num_keys; i++) {
    if (isdigit(ia->data[key_array[i]][0]) && isdigit(ib->data[key_array[i]][0]))
      cmp_result = atoi(ib->data[key_array[i]]) - atoi(ia->data[key_array[i]]);
    else 
      cmp_result = strcmp(ib->data[key_array[i]], ia->data[key_array[i]]);
    if (cmp_result) return cmp_result;
  }
  return 1;
} /* struct_cmp_desc() */
