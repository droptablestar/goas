
#include "MMapLinux.hpp"
#include "Record.hpp"
#include "Relation.hpp"
#include "StringUtilities.hpp"
#include "RawStringField.hpp"
#include "IntegerField.hpp"
#include "Constants.hpp"

#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

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
    unsigned short n_columns;
    memcpy(&n_columns, data, sizeof(n_columns));
    data = data + sizeof(n_columns);
    meta.set_number_of_columns(n_columns);

    unsigned int n_rows;
    memcpy(&n_rows, data, sizeof(n_rows));
    data = data + sizeof(n_rows);
    meta.set_number_of_rows(n_rows);

    for(int i = 0; i< n_columns; ++i){
        char type_column;
        memcpy(&type_column, data, sizeof(type_column));
        data = data + sizeof(type_column);
        meta.add_column_type(type_column);

        string column_name = StringUtilities::read_string_type(data);
        meta.add_column_name(column_name);
    }
}

void MMapLinux::set_relation(Relation& relation){
    Meta& meta = relation.get_meta();
    unsigned int number_of_rows = meta.number_of_rows();
    for(int i=0; i<number_of_rows; ++i){
        unsigned int number_of_columns = meta.number_of_columns();
        Record* record = new Record(number_of_columns, meta);

        for(int j=0; j<number_of_columns; ++j){
            if(meta.get_type(j)==TYPE_INTEGER) {
                int number = 0;
                memcpy(&number, data, sizeof(number));
                data = data + sizeof(int);

                IntegerField tmp(number);
                record->add(tmp);
            }
            else if(meta.get_type(j)==TYPE_STRING){
                const unsigned int size = StringUtilities::get_size_of_string(data);
                RawStringField* field = new RawStringField(size);

                memcpy(field->raw_ptr(), data, size);
                data = data + size;

                record->add(field);
            }
        }
        relation.add_record(record);
    }
}



