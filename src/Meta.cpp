
#include "Meta.hpp"
#include "Constants.hpp"

#include <iostream>
#include <algorithm>

using namespace std;

Meta::Meta():ints_in_record(0),
            strs_in_record(0),
            n_columns(0),
            n_rows(0){}

void Meta::print() const{
    cout<<"number of columns: "<<n_columns<<endl;
    cout<<"number of rows: "<<n_rows<<endl;

    for(auto i:column_names){
        cout<<"|  "<<i<<"  ";    
    }
}

unsigned short Meta::number_of_columns() const{
    return n_columns;    
}

unsigned int Meta::number_of_rows() const{
    return n_rows;   
}

void Meta::set_number_of_columns(const unsigned short n_columns){
    this->n_columns = n_columns;    
}

void Meta::set_number_of_rows(const unsigned int n_rows){
    this->n_rows = n_rows;    
}

void Meta::add_column_name(const string name){
    column_names.push_back(name);
}

void Meta::add_column_type(const unsigned short type){
    if(type==TYPE_STRING) ++strs_in_record;
    else if(type==TYPE_INTEGER) ++ints_in_record;
    column_types.push_back(type);
}

unsigned short Meta::get_type(const unsigned int index) const{
    return column_types[index];    
}

unsigned short Meta::integers_in_record() const{
    return ints_in_record;    
}

unsigned short Meta::strings_in_record() const{
    return strs_in_record;    
}



