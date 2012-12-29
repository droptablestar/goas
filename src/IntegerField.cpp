
#include "IntegerField.hpp"

#include <iostream>

using namespace std;

IntegerField::IntegerField(const int field):field(field){}

IntegerField::IntegerField(const IntegerField& other):field(other.field){}

void IntegerField::print() const{
    cout<<field;    
}

