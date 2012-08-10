#ifndef _SELECT_H_
#define _SELECT_H_

extern r_list *select_oas(r_list *, const char **);
extern r_list *par_select(r_list *, const char **, unsigned int, unsigned int);
extern r_list *seq_select(r_list *, const char **, unsigned int, unsigned int);
extern int evaluate(record *, const char **, unsigned int, unsigned int);
#endif /* !SELECT_H_ */
