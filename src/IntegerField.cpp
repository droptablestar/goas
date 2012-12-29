
#include "IntegerField.hpp"

#include <iostream>

using namespace std;

IntegerField::IntegerField(const int field):field(field){}

IntegerField::IntegerField(const IntegerField& other):field(other.field){}

/*IntegerField& IntegerField::operator=(const IntegerField& other){
    field = other.field;
    return *this;
}*/

void IntegerField::print() const{
    cout<<field;    
}

Field* IntegerField::clone() const{
    return new IntegerField(field);    
}
