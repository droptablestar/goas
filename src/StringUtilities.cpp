
#include "StringUtilities.hpp"

#include <string.h>

using namespace std;

unsigned int StringUtilities::get_size_of_string(const char* s){
    return strlen(s) + 1;
}

string StringUtilities::read_string_type(char* &s){
    unsigned int size = get_size_of_string(s);
    string field(s, size);
    s = s + size;
    return field;
}

