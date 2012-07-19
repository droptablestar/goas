#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "record.h"

/* This function initializes the memory required for a record and initializs
 * the beginnings of the arrays to NULL (though I can't remember why). Also,
 * we set the column count to 0 */
record *init_record() {
  record *rec = malloc(sizeof(record));
  rec->names = malloc(NUM_COLS * sizeof(char *));
  rec->data = malloc(NUM_COLS * sizeof(char *));

  /* Make sure the allocations worked. */
  check_malloc(rec->names,"init_record()");
  check_malloc(rec->data,"init_record()");

  rec->names[0] = NULL;
  rec->data[0] = NULL;
  rec->col_count = 0;

  return rec;
} /* init_record() */

/* Adds the strings name and data to the names and data arrays in index
 * loc for record rec. */
void add_to_record(record *rec, char *name, char *data) {
  int c_count = rec->col_count;
  /* Make sure there is room in the arrays for a new column. */
  if (c_count < NUM_COLS) {
    rec->names[c_count] = malloc(strlen(name) * sizeof(char) + 1);
    rec->data[c_count] = malloc(strlen(data) * sizeof(char) + 1);

    check_malloc(rec->names[c_count],"add_to_record()");
    check_malloc(rec->data[c_count],"add_to_record()");

    strcpy(rec->names[c_count], name);
    strcpy(rec->data[c_count], data);
    rec->col_count++;
  }
  /* There wasn't room for this columns, resize and add. */
  else {
    NUM_COLS*=2;
    rec->names = realloc(rec->names, sizeof(char *) * NUM_COLS);
    rec->data = realloc(rec->data, sizeof(char *) * NUM_COLS);

    add_to_record(rec, name, data);
  }
} /* add_to_record() */

/* Basic initialization for an r_list. Allocates memory and sets the record
 * count to 0. */
r_list *init_r_list() {
  r_list *r = malloc(sizeof(r_list));
  check_malloc(r,"init_r_list()");

  r->records = malloc(NUM_RECS * sizeof(record));
  check_malloc(r->records,"init_r_list()");

  r->rec_count = 0;

  return r;
} /* init_r_list() */

/* Adds record r to the list llist. */
void add_record(r_list *list, record *r) {
  int r_count = list->rec_count;
  /* Make sure there is room in the array of records. */
  if (r_count < NUM_RECS) {
    list->records[r_count] = *r;
    list->rec_count++;
  }
  /* Not enough room for this records, resize, add. */
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
    for (j=0; j<list->records[i].col_count; j++) {
      free(list->records[i].names[j]);
      free(list->records[i].data[j]);
    }
    /* Free the column array for this record. */
    free(list->records[i].names);
    free(list->records[i].data);
  }
  /* Free the records array and the r_list. */
  free(list->records);
  free(list);
} /* free_r_list() */

void check_malloc(void *array, char *errormsg) {
  if (array == NULL) {
    printf("Unable to allocate memory in %s.\n",errormsg);
    exit(-1);
  }
}
