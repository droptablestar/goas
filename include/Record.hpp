#ifndef _RECORD_H_
#define _RECORD_H_

#include <vector>
#include <string>
#include "Element.hpp"

class Record {
public:
    void addElement(std::string);
    std::string getElement(unsigned int);
    // void print();
    std::vector<std::string> data;
};

#endif /*_RECORD_H_*/
