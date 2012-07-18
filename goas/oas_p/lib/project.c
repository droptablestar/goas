#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#include "record.h"
#include "project.h"

unsigned int *key_array;
r_list *rel;
unsigned int num_keys;
unsigned int count0 = 0;
unsigned int count1 = 0;

sem_t lock;

/* Takes a relation and an array of keys as parameters. Returns the relation
 * with only the keys remaining in each record. */
r_list *project(r_list *relation, const char **keys) {
  rel = relation;
  /* Make sure there is something in the relation first. */
  if (relation == NULL) {
    printf("Empty relation passed to projection.\n");
    return relation;
  }

  int i,j,k,m;
  num_keys = 0;

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
  
  qsort(key_array, num_keys, sizeof(int), int_cmp);
  pthread_t thread[THREAD_COUNT];
  int ids[THREAD_COUNT];
  sem_init(&lock, 0, 1);
  for (i=0; i<THREAD_COUNT; i++) {
    ids[i] = i;
    pthread_create(&thread[i], NULL, project_p2, (void *)&ids[i]);
  }

  for (i=0; i<THREAD_COUNT; i++) 
    pthread_join(thread[i], NULL);

  free(key_array);
  
  return relation;
} /* project() */

/* This is the callback function for sorting keys. */
int int_cmp(const void *a, const void *b) {
  int *ia = (int *)a;
  int *ib = (int *)b;

  return *ia - *ib;
} /* int_cmp() */

void *project_p(void *arg) {
  int bottom, top, chunk, i, j, k, m, index;
  index = *(int *)arg;
  chunk = rel->rec_count / THREAD_COUNT;
  if (index != 0)
    bottom = chunk * index + 1;
  else
    bottom = chunk * index;
  if (index == THREAD_COUNT-1)
    top = rel->rec_count;
  else
    top = bottom + chunk;
  int keep=0;
  for (i=bottom; i<top; i++) {
    for (j=0; j<rel->records[i].col_count; j++) {
      for (k=key_array[0],m=0; m<num_keys; m++,k=key_array[m]) {
  	if (k==j) {
	  keep = 1;
  	  break;
  	}
      }
      if (!keep) {
	free(rel->records[i].names[j]);
	free(rel->records[i].data[j]);
      }
      keep = 0;
    }
  }
    
  int back;
  for (i=bottom; i<top; i++) {
    back = 1;
    for (j=0; j<num_keys; j++) {
      rel->records[i].names[j] = rel->records[i].names[key_array[j]];
      rel->records[i].data[j] = rel->records[i].data[key_array[j]];
    }
    rel->records[i].names = realloc(rel->records[i].names,
  					 (num_keys) * sizeof(char *));
    rel->records[i].data = realloc(rel->records[i].data,
  					(num_keys) * sizeof(char *));
	
    rel->records[i].col_count = num_keys;
  }
}

void *project_p2(void *arg) {
  int keep=0,i,j,k,m;
  while (count0 < num_keys + 1) {
    sem_wait(&lock);
    count0++;
    i = count0-1;
    sem_post(&lock);
    for (j=0; j<rel->records[i].col_count; j++) {
      for (k=key_array[0],m=0; m<num_keys; m++,k=key_array[m]) {
  	if (k==j) {
	  keep = 1;
  	  break;
  	}
      }
      if (!keep) {
	free(rel->records[i].names[j]);
	free(rel->records[i].data[j]);
      }
      keep = 0;
    }
  }
    
  int back;
  while (count1 < num_keys+1) {
    sem_wait(&lock);
    count1++;
    i = count1-1;
    sem_post(&lock);
    back = 1;
    for (j=0; j<num_keys; j++) {
      rel->records[i].names[j] = rel->records[i].names[key_array[j]];
      rel->records[i].data[j] = rel->records[i].data[key_array[j]];
    }
    rel->records[i].names = realloc(rel->records[i].names,
  					 (num_keys) * sizeof(char *));
    rel->records[i].data = realloc(rel->records[i].data,
  					(num_keys) * sizeof(char *));
	
    rel->records[i].col_count = num_keys;
  }
}
