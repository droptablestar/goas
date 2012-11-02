#ifndef _RECORD_H_
#define _RECORD_H_

#include <vector>
#include <string>

class Record {
public:
    void addElement(std::string data);
    std::string getElement(unsigned int position);
    void print();
    std::vector<std::string> data;
};

#endif /*_RECORD_H_*/
