
#include "Record1.hpp"

Field::Field(const unsigned int size, const char* field):
                                    size(size), field(field), n_field(-1),
                                    is_integer(false){}

Field::Field(const int field):n_field(field), field(NULL), size(0),
                            is_integer(true){}

const char* Field::get_field() const{
   return field;     
}

unsigned int Field::get_n_field() const{
   return n_field;     
}

unsigned int Field::get_size() const{
    return size;    
}

bool Field::is_int() const{
    return is_integer;    
}

Field* Record1::get_element(const unsigned int index) const{
    return fields[index];
}

void Record1::add_element(Field* field){
    fields.push_back(field);    
}



