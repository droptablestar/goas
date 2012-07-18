#ifndef _PROJECT_H_
#define _PROJECT_H_

extern r_list *project(r_list *, const char **);
extern r_list *parallel_project(r_list *, const char **, unsigned int);
extern int int_cmp(const void *, const void *);
extern void *project_p(void *);
extern void *project_p2(void *);

#endif /*!_PROJECT_H_*/
