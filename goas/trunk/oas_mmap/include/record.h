#ifndef _RECORD_H_
#define _RECORD_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

typedef struct record_s record;
typedef struct list_node_s node;
typedef struct list_s r_list;

extern r_list *init_r_list(char **);

extern void add_to_record(record *, char *, char *);
extern void create_records(r_list *, char *, unsigned long, struct stat *);
extern void add_record(r_list *, record *);
extern void print_r_list(r_list *);
extern void check_malloc(void *, char *);

/* These are the initial sizes for the columns arrays and record array.
 * Let's assume these numbers come from the query optimizer. */
#define MAX_COLS 500
#define MAX_RECS 500000

/* These variables represent the actualy size of the records array and column
 * arrays in each record. */
extern unsigned int NUM_COLS;
extern unsigned int NUM_RECS;

/* This is a record for a row of our database schema. name indicates the name
 * of the column while data is the data present in column. */
struct record_s {
  char **data;
  /* unsigned int col_count; */
};

/* This is an array to maintain records. */
struct list_s {
  char **c_names;
  record *records;
  unsigned int rec_count;
};

#endif /* !_RECORD_H_ */
