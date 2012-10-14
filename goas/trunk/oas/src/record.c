#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "record.h"

unsigned int NUM_COLS;
unsigned int NUM_RECS;

/* This function initializes the memory required for a record and goes through
 * each line of the file creating records and adding them to the record array.
 * relation is a pointer to the relation to be modified, lines is the next line
 * following the column names in the file pointed to by fr. */
void create_records(r_list *relation, char *line, FILE *fr) {
  /* These variables are used for extracting field data from a line and placing
   * it in the correct record and location. */
  int c_count = 0;
  int i=0;
  char delims[2] = "\t";
  char *parsed_line = NULL;

  /* For file reading. */
  ssize_t bytes_read;
  size_t nbytes = 512;
  /* Loop through each line, splitting on '\t' and allocate memory for each
   * field. */
  do {
    /* Initialize memory for this records. */
    record *rec = malloc(sizeof(record));
    rec->data = malloc(NUM_COLS * sizeof(char *));

    if (rec->data == NULL) {
      printf("Malloc problem in init_record().\n");
      exit(-1);
    }
    c_count = 0;
    parsed_line = strtok(line, delims);
    
    /* Add each field to the record. */
    while (parsed_line != NULL && parsed_line[0] != '\n') {
      if (parsed_line[strlen(parsed_line)-1] == '\n')
	parsed_line[strlen(parsed_line)-1] = '\0';

      rec->data[c_count] = malloc(strlen(parsed_line) * sizeof(char) + 1);
      
      /* Make sure the allocations worked. Don't call check_malloc() because
       * if there are lots of records there will be too many function calls. */
      if (rec->data[c_count] == NULL) {
	printf("Malloc problem in create_record().\n");
	exit(-1);
      }
      strcpy(rec->data[c_count], parsed_line);
      c_count++;

      parsed_line = strtok(NULL, delims);
    }

    /* Make sure this wasn't a blank line or some other unusual nonsense. */
    if (parsed_line == NULL) {
      add_record(relation, rec);
      free(rec);
    }
    /* Free the record and the data if this line was junk. Sanity check.*/
    else {
      free(rec->data);
      free(rec);
    }
  } while ((bytes_read = getline(&line, &nbytes, fr)) != -1);

  NUM_RECS = relation->rec_count;

  if (parsed_line != NULL && parsed_line[0] != '\n')
    free(parsed_line);
} /* create_record() */

/* Basic initialization for an r_list. Allocates memory, sets the record
 * count to 0, and initializes the column names array. */
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

/* Adds record r to the relation list. */
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
    check_malloc(list->records, "add_record()");
    add_record(list, r);
  }
} /* add_record() */

/* Prints the contents of each record in the list passed as the first
 * parameter freeing memory for the relation as it goes. */
void print_r_list(r_list *list) {
  int i,j,k;

  /* Print column names */
  for (i=0; i<NUM_COLS; i++) {
    if (i != NUM_COLS-1)
      /* printf(" %s |",list->records[0].names[i]); */
      printf(" %s |",list->c_names[i]);
    else
      /* printf(" %s",list->records[0].names[i]); */
      printf(" %s",list->c_names[i]);
  }
  printf(" \n");
  for (i=0; i<NUM_COLS; i++) {
    for (j=0; j<strlen(list->c_names[i])+2; j++)
      printf("-");
    if (i != NUM_COLS-1)
      printf("+");
  }
  printf("\n");
  int len;
  for (i=0; i<NUM_RECS; i++) {
    for (j=0; j<NUM_COLS; j++) {
      len = strlen(list->c_names[j])+1 -
      	strlen(list->records[i].data[j]);
      for (k=0; k<len; k++)
	printf(" ");
      printf("%s",list->records[i].data[j]);
      if (j != NUM_COLS-1)
	printf(" |");
      free(list->records[i].data[j]);
    }
    printf("\n");
    free(list->records[i].data);
  }
  for (i=0; i<NUM_COLS; i++)
    free(list->c_names[i]);

  free(list->c_names);
  free(list->records);
  free(list);

  printf("(%d rows)\n",NUM_RECS);
  printf("\n");
} /* print_r_list() */

/* Checks if the pointer array is NULL. If so print errormsg and exit. */
void check_malloc(void *array, char *errormsg) {
  if (array == NULL) {
    printf("Unable to allocate memory in %s.\n",errormsg);
    exit(-1);
  }
} /* check_malloc() */


/* This is the callback function for sorting integer keys. */
int int_cmp(const void *a, const void *b) {
  int *ia = (int *)a;
  int *ib = (int *)b;

  return *ia - *ib;
} /* int_cmp() */
