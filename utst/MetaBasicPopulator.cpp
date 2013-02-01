
#include "MetaBasicPopulator.hpp"

#include "Meta.hpp"

#include <iostream>

using namespace std;

MetaBasicPopulator::MetaBasicPopulator(Meta& meta):meta(meta){}

void MetaBasicPopulator::columns(const unsigned short columns){
    meta.set_columns(columns);
}

void MetaBasicPopulator::rows(const unsigned int rows){
    meta.set_rows(rows);
}

void MetaBasicPopulator::column_names_and_types(string field){
    for(unsigned short i=0; i<meta.columns(); ++i){
        meta.add_column_name(field);
        meta.add_column_type(TYPE_STRING);
    }
}

void MetaBasicPopulator::colum_names(){
    meta.add_column_name("name1");
    meta.add_column_name("name2");
    meta.add_column_name("name3");
    meta.add_column_name("name4");
    meta.add_column_name("name5");
    meta.add_column_name("name6");
    meta.add_column_name("name7");
    meta.add_column_name("name8");
    meta.add_column_name("num1");
    meta.add_column_name("num2");
    meta.add_column_name("num3");
    meta.add_column_name("num4");
    meta.add_column_name("num5");
    meta.add_column_name("num6");
    meta.add_column_name("num7");
    meta.add_column_name("num8");
}

void MetaBasicPopulator::column_types(){
    meta.add_column_type(TYPE_STRING);
    meta.add_column_type(TYPE_STRING);
    meta.add_column_type(TYPE_STRING);
    meta.add_column_type(TYPE_STRING);
    meta.add_column_type(TYPE_STRING);
    meta.add_column_type(TYPE_STRING);
    meta.add_column_type(TYPE_STRING);
    meta.add_column_type(TYPE_STRING);
    meta.add_column_type(TYPE_INTEGER);
    meta.add_column_type(TYPE_INTEGER);
    meta.add_column_type(TYPE_INTEGER);
    meta.add_column_type(TYPE_INTEGER);
    meta.add_column_type(TYPE_INTEGER);
    meta.add_column_type(TYPE_INTEGER);
    meta.add_column_type(TYPE_INTEGER);
    meta.add_column_type(TYPE_INTEGER);    
}



