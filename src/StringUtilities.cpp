
#include "StringUtilities.hpp"

#include <string>

using namespace std;

unsigned int StringUtilities::get_size_of_string(const char* s){
    unsigned int length = 0;
    while(*s!='\0'){
        ++length;    
        ++s;
    }
    return length + 1;
}

string StringUtilities::read_string_type(char* &s){
    unsigned int size = get_size_of_string(s);
    string field(s, size);
    s = s + size;
    return field;
}

