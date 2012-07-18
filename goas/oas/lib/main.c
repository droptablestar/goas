#include <stdio.h>

#include "record.h"
#include "scan.h"
#include "project.h"
#include "sort.h"
#include "select.h"

int main(int argc, char *argv[]) {
  r_list *relation = scan(argv[1]);

  /* const char *keys[] = {"name", "rating", NULL}; */
  const char *keys[] = {"id", "col2", "col3", "random", NULL};
  relation = project(relation, keys);
  /* print_r_list(relation); */

  /* const char *keys3[] = {"random",">","199990","|","id","=","0",NULL}; */
  /* select(relation, keys3); */

  /* s_order order = DESC; */
  /* sort(relation, keys, order); */
  /* print_r_list(relation); */
  
  free_r_list(relation);
  return 0;
}
