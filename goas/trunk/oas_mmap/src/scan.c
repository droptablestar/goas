#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include "record.h"
#include "scan.h"

unsigned int NUM_COLS = MAX_COLS;
unsigned int NUM_RECS = MAX_RECS;

/* scans the file specified by file_name */
r_list *scan(char *file_name) {
  /* Variables for getting the column names. */
  char **column_names;
  column_names = malloc(NUM_COLS * sizeof(char *));
  check_malloc(column_names, "scan()");
  
  /* Get size of file. */
  int fd;
  if ((fd = open(file_name, O_RDONLY)) < 0) {
    perror("Couldnt open file.\n");
    exit(-1);
  }
  struct stat sb;
  if (fstat(fd, &sb) < 0) {
    perror("fstat");
    exit(-1);
  }
  if (!S_ISREG(sb.st_mode)) {
    fprintf(stderr, "[%s] is not a file\n",file_name);
    exit(-1);
  }
  char *map = (char *)mmap(0, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (map == MAP_FAILED) {
    close(fd);
    printf("Error mapping input file.\n");
    exit(-1);
  }

  long i=1;
  int j=0, k, start=0;

  /* strip out the column names. separated by \t */
  while (i < sb.st_size && map[i-1] != '\n') {
    if (map[i] == '\t' || map[i] == '\n') {
      if (j < NUM_COLS) {
	column_names[j] = malloc((i - start) * sizeof(char) + 1);
	check_malloc(column_names[j], "scan()");
	for (k=0; k<(i-start); k++) {
	  column_names[j][k] = map[start + k];
	}
	column_names[j][k] = '\0';
	start = i+1;
      }
      else {
	NUM_COLS*=2;
	column_names = realloc(column_names, NUM_COLS * sizeof(char *));
	check_malloc(column_names, "scan()");
	column_names[j] = malloc((i - start) * sizeof(char));
	check_malloc(column_names[j], "scan()");
	for (k=0; k<(i-start); k++) {
	  column_names[j][k] = map[start + k];
	}
	start = i+1;
      }
      j++;
    }
    i++;
  }
  NUM_COLS = j;

  long offset = i;

  /* This will only happen if there are no records in the table. */
  if (map[i] == EOF) {
    printf("This table appears to not have any entries.\n");
    close(fd);
    exit(-1);
  }

  /* Initialize the relation. */
  r_list *relation = init_r_list(column_names);

  create_records(relation, map, offset, &sb);
  
  /* Free the memory created for the column names. */
  for (i=0; i<MAX_COLS; i++) 
    free(column_names[i]);
  free(column_names);
  
  return relation;
} /* scan() */
