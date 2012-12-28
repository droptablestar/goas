
#include "IntegerField.hpp"

#include <iostream>

using namespace std;

IntegerField::IntegerField(const int field):field(field){}

void IntegerField::print() const{
    cout<<field;    
}

Field* IntegerField::clone() const{
    return new IntegerField(field);    
}
