
#include "MMapLinux.hpp"
#include "Record.hpp"
#include "Record1.hpp"
#include "Relation.hpp"
#include "StringUtilities.hpp"

#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <vector>

using namespace std;

MMapLinux::MMapLinux(const string file):file(file){}

void MMapLinux::open_file(){
    struct stat sb;
    int fd = open(file.c_str(), O_RDONLY);
    if(fd == -1){
        perror ("open");
    }

    if(fstat(fd, &sb) == -1){
        perror ("fstat");
    }

    if(!S_ISREG(sb.st_mode)){
        fprintf (stderr, "%s is not a file\n", file.c_str());
    }

    data = (char*)mmap(0, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if(data == MAP_FAILED){
        perror ("mmap");
    }
}

void MMapLinux::set_meta(Meta& meta){

    memcpy(&meta.number_of_columns, data, sizeof(meta.number_of_columns));
    data = data + sizeof(meta.number_of_columns);
    memcpy(&meta.number_of_rows, data, sizeof(meta.number_of_rows));
    data = data + sizeof(meta.number_of_rows);


    for(int i = 0; i< meta.number_of_columns; ++i){
        char type_column;
        memcpy(&type_column, data, sizeof(type_column));
        data = data + sizeof(type_column);
        meta.column_types.push_back(type_column);

        string column_name = StringUtilities::read_string_type(data);

        meta.column_names.push_back(column_name);
    }
}

void MMapLinux::set_relation(Relation& relation){
    for(int i=0; i<relation.get_meta().number_of_rows; ++i){
        Record1* rec = new Record1;
        for(int j=0; j<relation.get_meta().number_of_columns; ++j){
            if(relation.get_meta().column_types[j]==0) {
                int number = 0;
                memcpy(&number, data, sizeof(number));

                data = data + sizeof(int);
                Field* field = new Field(number);

                rec->add_element(field);
            }
            else if(relation.get_meta().column_types[j]==1){

                unsigned int size = StringUtilities::get_size_of_string(data);
                char* snum = new char[size];
                memcpy(snum, data, size);
                data = data + size;

                Field* field = new Field(size,snum);
                rec->add_element(field);
            }
        }
        relation.add_record(rec);//passing the pointer is much more efficient
    }
}



