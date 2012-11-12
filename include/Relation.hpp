#ifndef RELATION_Q9HF9QWHEF98WHEF9
#define RELATION_Q9HF9QWHEF98WHEF9

#include "Meta.hpp"

#include <vector>
#include <string>

#define INT 0
#define STRING 1

class Record;
class Record1;

class Relation {
    public:
        void add_record(Record1* rec);
        unsigned short get_number_of_columns() const;
        unsigned int get_number_of_rows() const;
        char get_column_type(unsigned int) const;
        std::string get_column_name(unsigned int) const;
        Record1* get_record(unsigned int) const;
    
        void print() const;
        Meta& get_meta();


    private:
        std::vector<Record1*> records;
        Meta meta;
};

#endif //RELATION_Q9HF9QWHEF98WHEF9
