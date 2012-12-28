
#include <iostream>
#include <cstring>

#include "RawStringField.hpp"

using namespace std;

RawStringField::RawStringField(const unsigned int size):_field(new char[size]),
                                                        size(size){}

RawStringField::~RawStringField(){
    delete [] _field;    
}

void RawStringField::print() const{
    cout<<_field;    
}

char* RawStringField::raw_ptr() const{//I dont like this function at all!
    return _field;    
}

Field* RawStringField::clone() const{
    RawStringField* other = new RawStringField(size);
    memcpy(other->raw_ptr(), _field, size);
    return other;
}

