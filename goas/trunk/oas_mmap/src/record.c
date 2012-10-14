#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "record.h"

unsigned int NUM_COLS;
unsigned int NUM_RECS;

record *rec;

void create_records(r_list *relation, char *map, unsigned long offset,
		       struct stat *sb) {
  unsigned int c_count = 0;
  long addr, start=offset;
  int i,j;
  
  rec = malloc(sizeof(record));
  rec->data = malloc(NUM_COLS * sizeof(char *));

  /* Make sure the allocations worked. */
  if (rec->data == NULL) {
    printf("Malloc problem in init_record().\n");
    exit(-1);
  }
  rec->data = malloc(NUM_COLS * sizeof(char *));
  
  if (rec->data == NULL) {
    printf("Malloc problem in init_record().\n");
    exit(-1);
  }
  c_count = 0;

  for (addr=offset; addr<sb->st_size; ++addr) {
    if (map[addr] == '\t') {
      rec->data[c_count] = malloc((addr - start) * sizeof(char) + 1);

      if (rec->data == NULL) {
	printf("Malloc problem in init_record().\n");
	exit(-1);
      }

      for (i=0; i<(addr-start); i++)
	rec->data[c_count][i] = map[start + i];

      rec->data[c_count][i] = '\0';

      c_count++;
      start = addr+1;
    }
    else if (map[addr] == '\n') {
      rec->data[c_count] = malloc((addr - start) * sizeof(char) + 1);

      if (rec->data == NULL) {
	printf("Malloc problem in init_record().\n");
	exit(-1);
      }

      for (i=0; i<(addr-start); i++)
	rec->data[c_count][i] = map[start + i];

      rec->data[c_count][i] = '\0';

      c_count++;
      start = addr+1;

      add_record(relation, rec);
      free(rec);
      rec = malloc(sizeof(record));

      if (rec == NULL) {
	printf("Malloc problem in init_record().\n");
	exit(-1);
      }
      
      rec->data = malloc(NUM_COLS * sizeof(char *));
      
      if (rec->data == NULL) {
	printf("Malloc problem in init_record().\n");
	exit(-1);
      }
      c_count = 0;
    }
  }
  NUM_RECS = relation->rec_count;
} /* create_records() */

/* Basic initialization for an r_list. Allocates memory and sets the record
 * count to 0. */
r_list *init_r_list(char **names) {
  r_list *r = malloc(sizeof(r_list));
  check_malloc(r,"init_r_list()");

  r->records = malloc(NUM_RECS * sizeof(record));
  check_malloc(r->records,"init_r_list()");

  r->c_names = malloc(NUM_COLS * sizeof(char *));
  check_malloc(r->c_names,"init_r_list()");

  unsigned int i;
  for (i=0; i<NUM_COLS; i++) {
    r->c_names[i] = malloc(strlen(names[i]) * sizeof(char));
    check_malloc(r->c_names,"init_r_list()");
    strcpy(r->c_names[i], names[i]);
  }

  r->rec_count = 0;

  return r;
} /* init_r_list() */

/* Adds record r to the list llist. */
void add_record(r_list *list, record *r) {
  unsigned int r_count = list->rec_count;

  /* Make sure there is room in the array of records. */
  if (r_count < NUM_RECS) {
    list->records[r_count] = *r;
    list->rec_count++;
  }
  /* Not enough room for this records, resize, add. */
  else {
    NUM_RECS*=2;
    list->records = realloc(list->records, sizeof(record) * NUM_RECS);
    check_malloc(list->records, "add_record()");
    add_record(list, r);
  }
} /* add_record() */

/* Prints the contents of each record in the list passed as the first
 * parameter. */
void print_r_list(r_list *rel) {
  unsigned int i,j,k;

  if (NUM_RECS == 0) {
      free(rel->records);
      free(rel);
      printf("(%d rows)\n",NUM_RECS);
      printf("\n");
      return;
  }
  /* Print column names */
  for (i=0; i<NUM_COLS; i++) {
    if (i != NUM_COLS-1)
      printf(" %s |",rel->c_names[i]);
    else
      printf(" %s",rel->c_names[i]);
  }
  printf(" \n");
  for (i=0; i<NUM_COLS; i++) {
    for (j=0; j<strlen(rel->c_names[i])+2; j++) 
      printf("-");
    if (i != NUM_COLS-1)
      printf("+");
  }
  printf("\n");
  int len;

  for (i=0; i<NUM_RECS; i++) {
    for (j=0; j<NUM_COLS; j++) {
      len = strlen(rel->c_names[j]) + 1 -
	strlen(rel->records[i].data[j]);
      for (k=0; k<len; k++)
	printf(" ");
      printf("%s",rel->records[i].data[j]);
      if (j != NUM_COLS-1)
	printf(" |");

      free(rel->records[i].data[j]);
    }
    printf("\n");
    free(rel->records[i].data);
  }
  for (i=0; i<NUM_COLS; i++)
    free(rel->c_names[i]);
  free(rel->c_names);

  free(rel->records);
  free(rel);

  printf("(%d rows)\n",NUM_RECS);
  printf("\n");
} /* Print_r_list() */

void check_malloc(void *array, char *errormsg) {
  if (array == NULL) {
    printf("Unable to allocate memory in %s.\n",errormsg);
    exit(-1);
  }
}
