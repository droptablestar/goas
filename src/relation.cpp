#include "Relation.hpp"

using namespace std;

void Relation::setNumberOfColumns(unsigned short num) {
    this->number_of_columns = num;
}
void Relation::setNumberOfRows(unsigned int num) {
    this->number_of_rows = num;
}
void Relation::addColumnType(char type) {
    this->column_types.push_back(type);
}
void Relation::addColumnName(string name) {
    this->column_names.push_back(name);
}
void Relation::addRecord(Record rec) {
    this->records.push_back(rec);
}
unsigned short Relation::getNumberOfColumns() {
    return this->number_of_columns;
}
unsigned int Relation::getNumberOfRows() {
    return this->number_of_rows;
}
char Relation::getColumnType(unsigned int position) {
    return this->column_types.at(position);
}
string Relation::getColumnName(unsigned int position) {
    return this->column_names.at(position);
}
Record Relation::getRecord(unsigned int position) {
    return this->records.at(position);
}
void printRelation(Relation *rel) {
    ;
}
