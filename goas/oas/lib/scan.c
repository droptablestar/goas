#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "record.h"
#include "scan.h"

/* scans the file specified by file_name */
r_list *scan(char *file_name) {
  /* Variables for getting the column names. */
  char **column_names;
  column_names = malloc(NUM_COLS * sizeof(char *));
  check_malloc(column_names, "scan()");
  
  char delims[2] = "\t";
  char *parsed_line = NULL;

  /* For reading from the file. */
  ssize_t bytes_read;
  size_t nbytes=80;
  char *line = NULL;

  FILE *fr = fopen(file_name, "r");

  if (fr == NULL) {
    printf("Unable to open file [%s].\n",file_name);
    exit(-1);
  }

  /* Take care of the first line - column names */
  bytes_read = getline(&line, &nbytes, fr);
  if (bytes_read == -1) {
    printf("File [%s] appears to be empty.\n",file_name);
    fclose(fr);
    exit(-1);
  }

  int i=0;
  parsed_line = strtok(line, delims);

  /* strip out the column names. separated by \t */
  while (parsed_line != NULL) {
    if (i < NUM_COLS) 
      column_names[i] = malloc(strlen(parsed_line) * sizeof(char));
    else {
      NUM_COLS*=2;
      column_names = realloc(column_names, NUM_COLS * sizeof(char *));
      column_names[i] = malloc(strlen(parsed_line) * sizeof(char));
    }
    check_malloc(column_names[i], "scan()");
    
    strcpy(column_names[i++], parsed_line);
    parsed_line = strtok(NULL, delims);
  }
  i--;

  /* Remove trailing \n */
  if (column_names[i][strlen(column_names[i])-1] == '\n')
    column_names[i][strlen(column_names[i])-1] = '\0';

  /* This will only happen if there are no records in the table. */
  bytes_read = getline(&line, &nbytes, fr);
  if (bytes_read == -1) {
    printf("This table appears to not have any entries.\n");
    fclose(fr);
    exit(-1);
  }

  /* Initialize the relation. */
  r_list *relation = init_r_list();
  
  /* Read the lines and create a record for each entry. */
  do {
    record *rec = init_record();
    parsed_line = strtok(line, delims);
    i=0;
    /* Add each field to the record. */
    while (parsed_line != NULL && parsed_line[0] != '\n') {
      if (parsed_line[strlen(parsed_line)-1] == '\n')
	parsed_line[strlen(parsed_line)-1] = '\0';
      add_to_record(rec, column_names[i++], parsed_line);
      parsed_line = strtok(NULL, delims);
    }
    /* Make sure this wasn't a blank line or some other unusual nonsense. */
    if (parsed_line == NULL || rec->names[0] != NULL) {
      /* Resize the names and data arrays to the real size. */
      rec->names = realloc(rec->names, rec->col_count * sizeof(char *));
      rec->data = realloc(rec->data, rec->col_count * sizeof(char *));
      add_record(relation, rec);
      free(rec);
    }
    /* Free the record if this line was junk. */
    else {
      free(rec->names);
      free(rec->data);
      free(rec);
    }
  } while ((bytes_read = getline(&line, &nbytes, fr)) != -1);
  /* Clean up. */
  if (parsed_line != NULL &&parsed_line[0] != '\n')
    free(parsed_line);

  fclose(fr);

  /* Free the memory created for the column names. */
  for (i=0;i<relation->records[0].col_count;i++) 
    free(column_names[i]);

  return relation;
} /* scan() */
