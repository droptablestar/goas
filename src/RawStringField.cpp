
#include <iostream>

#include "RawStringField.hpp"

using namespace std;

RawStringField::RawStringField(const unsigned int size):_field(new char[size]){}

RawStringField::~RawStringField(){
    delete [] _field;    
}

void RawStringField::print() const{
    cout<<_field;    
}

char* RawStringField::raw_ptr() const{
    return _field;    
}

