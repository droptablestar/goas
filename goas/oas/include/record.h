#ifndef _RECORD_H_
#define _RECORD_H_

typedef struct record_s record;
typedef struct list_node_s node;
typedef struct list_s r_list;

extern record *init_record();
extern r_list *init_r_list(char **);

extern void add_to_record(record *, char *, char *);
extern void create_records(r_list *, char *, FILE *);
extern void add_record(r_list *, record *);
extern void print_r_list(r_list *);
extern void check_malloc(void *, char *);
extern int int_cmp(const void *, const void *);

/* These are the initial sizes for the columns array and record array.
 * Let's assume these numbers come from the query optimizer. */
#define MAX_COLS 500
#define MAX_RECS 1000000

/* These variables represent the actual sizes of the records array and column
 * arrays in each record. */
extern unsigned int NUM_COLS;
extern unsigned int NUM_RECS;

/* This is a record for a row of our database schema. All data is the data
 * represented as a string. data is an array of strings that make up a record */
struct record_s {
  char **data;
  int *lengths;
};

/* This is an array to maintain records. */
struct list_s {
  char **c_names;
  record *records;
  unsigned int rec_count;
};

#endif /* !_RECORD_H_ */
