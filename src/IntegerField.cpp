
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

unsigned int IntegerField::number_of_digits() const{
    if(!field) return 1;

    unsigned int count = 0;
    int tmp = field;
    while(tmp){
        tmp /= 10;
        ++count;
    }

    return count;
}

