#include "Relation.hpp"
#include "Record.hpp"
#include "Scan.hpp"
#include "MMapLinux.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

void scan(const char *file_name, Relation& relation){
    MMapLinux input(file_name);

    input.open_file();
    input.set_meta(relation.get_meta());
    input.set_relation(relation);
}


