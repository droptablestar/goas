#ifndef _RECORD_H_
#define _RECORD_H_

typedef struct record_s record;
typedef struct list_node_s node;
typedef struct list_s r_list;

extern record *init_record();
extern r_list *init_r_list();

extern void add_to_record(record *, char *, char *, int);
extern void add_record(r_list *, record *);
extern void print_r_list(r_list *);
extern void free_r_list(r_list *);

#define MAX_COLS 500000
#define MAX_RECS 500000

#define REC_THRESH 10000

#define THREAD_COUNT 4

/* This is a record for a row of our database schema. name indicated the name
 * of the column data is the data present in column. */
struct record_s {
  char **names;
  char **data;
  unsigned int col_count;
};

/* This is an array to maintain records. */
struct list_s {
  record *records;
  unsigned int rec_count;
};

#endif /* !_RECORD_H_ */
