#ifndef _RELATION_H_
#define _RELATION_H_

#include "Record.hpp"
#include "Meta.hpp"

#include <vector>
#include <string>

#define INT 0
#define STRING 1

class Relation {
    public:
        void addRecord(Record* rec);
        unsigned short getNumberOfColumns();
        unsigned int getNumberOfRows();
        char getColumnType(unsigned int);
        std::string getColumnName(unsigned int);
        Record* getRecord(unsigned int);
    
        void print();
        Meta& get_meta();


    private:
        std::vector<Record*> records;
        Meta meta;
};


#endif /*_RELATION_H_*/
