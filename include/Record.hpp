#ifndef RECORD_Q987WHE9Q8WHEF98HWEF 
#define RECORD_Q987WHE9Q8WHEF98HWEF

#include <vector>
#include <string>

class Record {
public:
    void add_element(std::string data);
    std::string get_element(unsigned int position);
    void print();

private:
    std::vector<std::string> data;
};

#endif //RECORD_Q987WHE9Q8WHEF98HWEF
