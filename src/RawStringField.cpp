
#include <iostream>
#include <algorithm>

#include "RawStringField.hpp"

RawStringField::RawStringField(const unsigned int size):size(size),
                                                        field(size? new char[size] : nullptr){}

RawStringField::~RawStringField(){
    delete [] field;    
}

RawStringField::RawStringField(const RawStringField& other):size(other.size),
                                                            field(size? new char[size] : nullptr){
    std::copy(other.field, other.field+size, field);
}

RawStringField::RawStringField(RawStringField&& other){
    swap(*this, other);    
}
                                                            
RawStringField& RawStringField::operator=(RawStringField other){
    swap(*this, other);
    return *this;
}

void RawStringField::swap(RawStringField& a, RawStringField& b){
    using std::swap;
    swap(a.size, b.size);
    swap(a.field, b.field);
}

void RawStringField::print() const{
    std::cout<<field;    
}

char* RawStringField::raw_ptr() const{//I dont like this function at all!
    return field;    
}

