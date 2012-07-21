#ifndef _SELECT_H_
#define _SELECT_H_

extern r_list *select(r_list *, const char **);
extern int eq(const char *, const char *);
extern int gt(const char *, const char *);
extern int lt(const char *, const char *);
extern int evaluate(record *, const char **, int, int);
extern int int_cmp2(const void *, const void *);

#endif /* !SELECT_H_ */
