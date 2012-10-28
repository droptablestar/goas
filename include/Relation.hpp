#ifndef _RELATION_H_
#define _RELATION_H_

#include "Record.hpp"
#include <vector>
#include <string>

#define INT 0
#define STRING 1

class Relation {
public:
    void setNumberOfColumns(unsigned short);
    void setNumberOfRows(unsigned int);
    void addColumnType(char);
    void addColumnName(std::string);
    void addRecord(Record rec);
    unsigned short getNumberOfColumns();
    unsigned int getNumberOfRows();
    char getColumnType(unsigned int);
    std::string getColumnName(unsigned int);
    Record getRecord(unsigned int);

private:
    unsigned short number_of_columns;
    unsigned int number_of_rows;
    std::vector<char> column_types;
    std::vector<std::string> column_names;
    std::vector<Record> records;
};
void printRelation(Relation *);

#endif /*_RELATION_H_*/
