
#include "RawStringField.hpp"

#include <iostream>
#include <algorithm>
#include <cstring>

RawStringField::RawStringField(const unsigned int size):size(size),
                                                        field(size? new char[size] : nullptr){}

RawStringField::~RawStringField(){
    if(field) {
        delete [] field;    
        field = nullptr;
    }
}

RawStringField::RawStringField(const RawStringField& other):size(other.size),
                                                            field(size? new char[size] : nullptr){
    std::copy(other.field, other.field+size, field);
}

RawStringField::RawStringField(RawStringField&& other){
    size = 0;
    field = nullptr;
    swap(*this, other);    
}
                                                            
RawStringField& RawStringField::operator=(RawStringField other){
    swap(*this, other);
    return *this;
}

bool RawStringField::operator==(const RawStringField& other) const{
    if(strncmp(field, other.field, size)==0 && size==other.size) return true;
    return false;
}

bool RawStringField::operator>(const RawStringField& other) const{
    if(strncmp(field, other.field, size) > 0) return true;
    return false;
}

bool RawStringField::operator<(const RawStringField& other) const{
    if(strncmp(field, other.field, size) < 0) return true;
    return false;
}

bool RawStringField::operator!=(const RawStringField& other) const{
    if(strncmp(field, other.field, size)!=0 || size!=other.size) return true;
    return false;
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

unsigned int RawStringField::length() const{
    return size;    
}

