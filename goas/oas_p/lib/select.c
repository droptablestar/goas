#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "record.h"
#include "select.h"

unsigned int *key_array;
unsigned int len_keys=1;
unsigned int num_keys = len_keys / 4;

unsigned int num_kept=0;
unsigned int *keep;

unsigned int count0 = 0;
unsigned int count1 = 0;

pthread_barrier_t barr;
pthread_mutex_t mutex;

r_list *select(r_list *relation, const char **keys) {
  /* Make sure there is something in the relation first. */
  if (relation == NULL) {
    printf("Empty relation passed to selection.\n");
    return relation;
  }
  
  int i;
  for (i=0;keys[i];i++) len_keys++;
  num_keys = len_keys / 4;

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
  keep = malloc(relation->rec_count * sizeof(int));
  k=0;

  pthread_t thread[THREAD_COUNT];
  pthread_mutex_init(&mutex, NULL);
  pthread_barrier_init(&barr, NULL, THREAD_COUNT);

  for (i=0; i<THREAD_COUNT; i++)
    pthread_create(&thread[i], NULL, select_p, (void *)relation);

  for (i=0; i<THREAD_COUNT; i++)
    pthread_join(&thread[i], NULL);
  
  /* Determine which records fit the selection. */
  /* for (i=0;i<relation->rec_count;i++) { */
  /*   if (evaluate(&(relation->records[i]), keys, num_keys, len_keys)) { */
  /*     keep[k++] = i; */
  /*     num_kept++; */
  /*   } */
  /*   else { */
  /*     for (j=0;j<relation->records[i].col_count;j++) { */
  /*    free(relation->records[i].names[j]); */
  /*    free(relation->records[i].data[j]); */
  /*     } */
  /*     free(relation->records[i].names); */
  /*     free(relation->records[i].data); */
  /*   } */
  /* } */
  
  /* for (j=0; j<num_kept; j++)  */
  /*   relation->records[j] = relation->records[keep[j]]; */
  /* relation->records = realloc(relation->records, */
  /*                          (num_kept) * sizeof(record)); */


  /* Tidy up memory and the records count. */
  relation->rec_count = num_kept;
  free(key_array);
  free(keep);
} /* select() */

int eq(const char *a, const char *b) {
  /* printf("EQ %s %s\n",a,b); */
  if (!strcmp(a,b)) return 1;
  else return 0;
}

int gt(const char *a, const char *b) {
  /* printf("GT %s %s\n",a,b); */
  if (atoi(a) > atoi(b)) return 1;
  else return 0;
}

int lt(const char *a, const char *b) {
  /* printf("LT %s %s\n",a,b); */
  if (atoi(a) < atoi(b)) return 1;
  else return 0;

}

int evaluate(record *rec, const char **keys, int num_keys, int len_keys) {
  int i,j;
  int result[num_keys];
  /* i:keys, j:data */
  for (i=3,j=0;j<num_keys;i+=4,j++) {
    result[j] = eval_part(rec, keys, j, i-3);
  }
  /* printf("FIRST:\n"); */
  /* for (i=0;i<num_keys;i++) printf("%d ",result[i]); */
  /* printf("\n"); */
  for (i=3,j=0;j<num_keys-1;i+=4,j+=2) {
    switch ((char)(*keys[i])) {
    case '&': result[j] = result[j] && result[j+1]; result[j+1]=0; break;
    case '|': result[j] = result[j] || result[j+1]; result[j+1]=0; break;
    }
  }

  /* printf("SECOND:\n"); */
  /* for (i=0;i<num_keys;i++) printf("%d ",result[i]); */
  /* printf("\n"); */
  for (i=0;i<num_keys;i++) 
    if (result[i] == 1)
      return 1;
  return 0;
}
    
int eval_part(record *rec, const char **keys, int d_index, int k_index) {
  int result;
  switch ((char)(*keys[k_index+1])) {
  case '=': result = eq(rec->data[key_array[d_index]],keys[k_index+2]); break;
  case '>': result = gt(rec->data[key_array[d_index]],keys[k_index+2]); break;
  case '<': result = lt(rec->data[key_array[d_index]],keys[k_index+2]); break;
  }

  return result;
}

void *select_p(void *r) {
  r_list *rel = (r_list *)r;
  int i,r_count,j;
  r_count = rel->rec_count;
  
  /* Determine which records fit the selection. */
  pthread_mutex_lock(&mutex);
  while(count0 < r_count) {
    i = count0++;
    pthread_mutex_unlock(&mutex);
    if (evaluate(&(relation->records[i]), keys, num_keys, len_keys)) {
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
    pthread_mutex_lock(&mutex);
  }
  
  int rc = pthread_barrier_wait(&barr);
  if (rc != 0 && rc != PTHREAD_BARRIER_SERIAL_THREAD) {
    printf("Counld't wait for projection barrier. Bailing.\n");
    exit(-1);
  }

  pthread_mutex_lock(&mutex);
  while (count1 < num_kept) {
    i = count1++;
    pthread_mutex_unlock(&mutex);
    relation->records[j] = relation->records[keep[j]];
  relation->records = realloc(relation->records,
                              (num_kept) * sizeof(record));

}
