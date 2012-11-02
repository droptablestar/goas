
#include "MMapLinux.hpp"

#include <string.h>
#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <vector>

using namespace std;

inline string read_string_type(char* &s){
    char raw_data;
    vector<char> data;
 
    memcpy(&raw_data, s, sizeof(raw_data));
    s = s + sizeof(raw_data);

    while(raw_data!='\0'){
        data.push_back(raw_data);
        memcpy(&raw_data, s, sizeof(raw_data));
        s = s + sizeof(raw_data);
    }
    string name(data.begin(), data.end());
    return name;
}

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

        string column_name = read_string_type(data);
        meta.column_names.push_back(column_name);
    }
}

void MMapLinux::set_relation(Relation& relation){
    for(int i=0; i<relation.get_meta().number_of_rows; ++i){
        Record* rec = new Record;
        for(int j=0; j<relation.get_meta().number_of_columns; ++j){
            if(relation.get_meta().column_types[j]==0) {
                int number = 0;
                memcpy(&number, data, sizeof(number));
                data = data + sizeof(number);
                rec->data.push_back(to_string(number));
            }
            else if(relation.get_meta().column_types[j]==1){
                rec->data.push_back(read_string_type(data));
            }
        }
        relation.addRecord(rec);//passing the pointer is much more efficient
    }
}



