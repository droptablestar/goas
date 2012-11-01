#include "Relation.hpp"

#include <iostream>

using namespace std;

Meta& Relation::get_meta(){
    return meta;    
}

unsigned short Relation::getNumberOfColumns() {
    return meta.number_of_columns;
}
unsigned int Relation::getNumberOfRows() {
    return meta.number_of_rows;
}
char Relation::getColumnType(unsigned int position) {
    return meta.column_types[position];
}
string Relation::getColumnName(unsigned int position) {
    return meta.column_names[position];
}
Record* Relation::getRecord(unsigned int position) {
    return this->records.at(position);
}

void Relation::addRecord(Record* rec) {
    this->records.push_back(rec);
}

void Relation::print(){
    unsigned short num_cols = getNumberOfColumns();
    unsigned int num_rows = getNumberOfRows();
    int i,j;

    for (i=0; i<num_cols; i++) {
	if (i != num_cols-1)
	    cout<<" "<< getColumnName(i)<<" |";
	else
	    cout<<" "<<getColumnName(i);
    }
    cout<<endl;

    for (i=0; i<num_cols; i++) {
    	for (j=0; j<getColumnName(i).length()+2; j++)
    	    cout<<"-";
    	if (i != num_cols-1)
    	    cout<<"+";
    }

    cout<<endl;

    unsigned short len,k;
    for (i=0; i<num_rows; i++) {
    	for (j=0; j<num_cols; j++) {
    	    len = (getColumnName(j).length() + 1) - getRecord(i)->getElement(j).length();
    	    for (k=0; k<len; k++)
    	    	cout<<" ";
    	    cout<<getRecord(i)->getElement(j);
    	    if (j != num_cols-1)
    		cout<<" |";
    	}
    	cout<<endl;
    }
    cout<<"("<<num_rows<<" rows)"<<endl;

}


