#include <stdio.h>

#include "record.h"
#include "scan.h"
#include "project.h"
#include "sort.h"
#include "select.h"

int main(int argc, char *argv[]) {
  r_list *relation = scan(argv[1]);

  /* const char *keys[] = {"name", "rating", NULL}; */
  const char *keys[4] = {"id", "col3", "random", NULL};
  relation = project(relation, keys);
  /* print_r_list(relation); */

  const char *keys3[8] = {"random",">","3000","|","random","=","34",NULL};
  select(relation, keys3);

  s_order order = ASC;
  const char *keys2[3] = {"random", "id", NULL};
  sort(relation, keys2, order);
  print_r_list(relation);
  
  free_r_list(relation);
  return 0;
}
