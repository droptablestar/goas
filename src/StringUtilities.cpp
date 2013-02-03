
#include "StringUtilities.hpp"

#include <string.h>

using namespace std;

string StringUtilities::read_string_type(char* &s){
    unsigned int size = strlen(s);
    /*no need for extra char '\0'
     * string provides that*/
    string field(s, size);
    s = s + size + 1;/*extra char for '\0'*/
    return field;
}

