#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "record.h"
#include "scan.h"

/* r_list relation; */

r_list *scan(char *file_name) {
  /* Variables for getting the column names. */
  char *column_names[MAX_COLS];
  char delims[2] = "\t";
  char *parsed_line = NULL;

  /* For reading from the file. */
  ssize_t bytes_read;
  size_t nbytes=80;
  char *line = NULL;

  FILE *fr = fopen(file_name, "r");

  if (fr == NULL) {
    printf("Unable to open file [%s].\n",file_name);
    exit(1);
  }

  /* Take care of the first line - column names */
  bytes_read = getline(&line, &nbytes, fr);
  if (bytes_read == -1) {
    printf("File [%s] appears to be empty.\n",file_name);
    fclose(fr);
    exit(1);
  }
  int i=0;
  parsed_line = strtok(line, delims);

  while (parsed_line != NULL) {
    column_names[i] = malloc(strlen(parsed_line) * sizeof(char));
    strcpy(column_names[i++], parsed_line);

    parsed_line = strtok(NULL, delims);
  }
  column_names[i--] = NULL;

  /* Remove trailing \n */
  if (column_names[i][strlen(column_names[i])-1] == '\n')
    column_names[i][strlen(column_names[i])-1] = '\0';

  bytes_read = getline(&line, &nbytes, fr);
  if (bytes_read == -1) {
    fclose(fr);
    printf("This table appears to not have any entries.\n");
    exit(1);
  }
  r_list *relation = init_r_list();
  
  char *to_add;
  /* We need to check if this iteration was the first time through as well as
     if it is just a \n. */
  do {
    record *rec = init_record();
    parsed_line = strtok(line, delims);
    i=0;
    while (parsed_line != NULL && parsed_line[0] != '\n') {
      to_add = parsed_line;
      if (to_add[strlen(to_add)-1] == '\n')
	to_add[strlen(to_add)-1] = '\0';
      add_to_record(rec, column_names[i], to_add, i);
      i++;
      parsed_line = strtok(NULL, delims);
    }
    if (parsed_line == NULL || rec->names[0] != NULL) {
      rec->names = realloc(rec->names, rec->col_count * sizeof(char *));
      rec->data = realloc(rec->data, rec->col_count * sizeof(char *));
      add_record(relation, rec);
      free(rec);
    }
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
  
  for (i=0;i<relation->records[0].col_count;i++) 
    free(column_names[i]);

  return relation;
}
