#ifndef _SORT_H_
#define _SORT_H_

typedef enum sort_order_tag s_order;

extern int struct_cmp_asc(const void *, const void *);
extern int struct_cmp_desc(const void *, const void *);
extern r_list *sort(r_list *, const char **, s_order);

enum sort_order_tag {
  ASC,
  DESC
};

#endif /*!_SORT_H_*/
