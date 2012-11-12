
#include "MMapLinux.hpp"
#include "Record.hpp"
#include "Record1.hpp"
#include "Relation.hpp"

#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <vector>

using namespace std;

unsigned int get_size_of_string(const char* s){
    unsigned int length = 0;
    while(*s!='\0'){
        ++length;    
        ++s;
    }
    return length + 1;
}

string read_string_type(char* &s){
    unsigned int size = get_size_of_string(s);
    string field(s, size);
    s = s + size;
    return field;
}

MMapLinux::MMapLinux(const string file):file(file){}

unsigned int number_of_digits_in_an_integer(int integer){
    unsigned int number_of_digits = 0;

    while(integer){
        integer = integer/10;
        ++number_of_digits;
    }
    return number_of_digits;
}


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

        string column_name = read_string_type(data);

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

                //unsigned int size = number_of_digits_in_an_integer(number);
                //char* snum = new char[size];
                //sprintf(snum, "%d\0", number);
                data = data + sizeof(int);
                
                Field* field = new Field(number);
                
             //   cout<<"field: ["<<field->get_field()<<"]"<<" size ["<<field->get_size()<<"]"<<endl;

                rec->add_element(field);
            }
            else if(relation.get_meta().column_types[j]==1){

                unsigned int size = get_size_of_string(data);
                char* snum = new char[size];
                 memcpy(snum, data, size);
                data = data + size;

                Field* field = new Field(size,snum);

            //    cout<<"field: ["<<field->get_field()<<"]"<<" size ["<<field->get_size()<<"]"<<endl;
                rec->add_element(field);

            }
        }
        relation.add_record(rec);//passing the pointer is much more efficient
    }
}



