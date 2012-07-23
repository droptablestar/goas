#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "record.h"

/* These variables represent the actualy size of the records array and column
 * arrays in each record. */
int NUM_COLS = MAX_COLS;
int NUM_RECS = MAX_RECS;

record *init_record() {
  record *rec = malloc(sizeof(record));
  rec->names = malloc(NUM_COLS * sizeof(char *));
  rec->data = malloc(NUM_COLS * sizeof(char *));
  rec->names[0] = NULL;
  rec->data[0] = NULL;
  rec->col_count = 0;

  return rec;
} /* init_record() */

/* Adds the strings name and data to the names and data arrays in index
 * loc for record rec. */
void add_to_record(record *rec, char *name, char *data, int loc) {
  /* Reserve a place at the end of the arrays for a NULL element. */
  if (loc < NUM_COLS) {
    rec->names[loc] = malloc(strlen(name) * sizeof(char) + 1);
    rec->data[loc] = malloc(strlen(data) * sizeof(char) + 1);
    strcpy(rec->names[loc], name);
    strcpy(rec->data[loc], data);
    rec->col_count+=1;
  }
  else {
    NUM_COLS*=2;
    rec->names = realloc(rec->names, sizeof(char *) * NUM_COLS);
    rec->data = realloc(rec->data, sizeof(char *) * NUM_COLS);

    add_to_record(rec, name, data, loc);
  }
} /* add_to_record() */

/* Basic initialization for an r_list. */
r_list *init_r_list() {
  r_list *r = malloc(sizeof(r_list));
  r->records = malloc(NUM_RECS * sizeof(record));
  r->rec_count = 0;

  return r;
} /* init_r_list() */

/* Adds record r to the list llist at index loc. */
void add_record(r_list *list, record *r) {
  if (list->rec_count < NUM_RECS) {
    list->records[list->rec_count++] = *r;
  }
  else {
    NUM_RECS*=2;
    list->records = realloc(list->records, sizeof(record) * NUM_RECS);
    add_record(list, r);
  }
} /* add_record() */

/* Prints the contents of each record in the list passed as the first
 * parameter. */
void print_r_list(r_list *list) {
  int i,j;
  for (i=0; i<list->rec_count; i++) {
    printf("RECORD NUMBER %d:\n",i);
    for (j=0; j<list->records[i].col_count; j++) {
      printf("\tNAME:[%s]\tDATA:[%s]\n",list->records[i].names[j],
  	     list->records[i].data[j]);
    }
  }
} /* print_r_list() */

/* Frees the memory that was allocated for r_list list and each record. */
void free_r_list (r_list *list) {
  int i,j;
  for (i=0; i<list->rec_count; i++) {
    /* Free all the strings in this record. */
    /* printf("REC[%d]:%d\n",i,list->records[i].col_count); */
    for (j=0; j<list->records[i].col_count; j++) {
      /* printf("FREEING %d %d %p\n",i,j,list->records[i].names[j]); */
      free(list->records[i].names[j]);
      free(list->records[i].data[j]);
    }
    /* Free the column array for this record. */
    free(list->records[i].names);
    free(list->records[i].data);
  }
  free(list->records);
  free(list);
} /* free_r_list() */

/* This is the callback function for sorting keys. */
int int_cmp(const void *a, const void *b) {
  int *ia = (int *)a;
  int *ib = (int *)b;

  return *ia - *ib;
} /* int_cmp() */
