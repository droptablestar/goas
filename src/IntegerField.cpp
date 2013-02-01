
#include "IntegerField.hpp"

#include <iostream>

using namespace std;

IntegerField::IntegerField(const int field):field(field){}

IntegerField::IntegerField(const IntegerField& other):field(other.field){}

IntegerField& IntegerField::operator=(const IntegerField& other){
    field = other.field;
    return *this;
}

bool IntegerField::operator==(const IntegerField& other) const{
    return field == other.field;
}

bool IntegerField::operator<(const IntegerField& other) const{
    return field < other.field;    
}

bool IntegerField::operator>(const IntegerField& other) const{
    return field > other.field;    
}

bool IntegerField::operator!=(const IntegerField& other) const{
    return field != other.field;
}

void IntegerField::print() const{
    cout<<field;    
}

