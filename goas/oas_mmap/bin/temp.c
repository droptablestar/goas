#include <stdio.h>

#include "record.h"
#include "scan.h"
#include "select.h"
#include "project.h"
#include "sort.h"

int main() {
	r_list *x0 = scan("../testing/oas_tables/100k");
	print_r_list(x0);
	return 0;
}
