
#ifndef META_98RHG9E8HRG98HERG
#define META_98RHG9E8HRG98HERG

#include <vector>
#include <string>

struct Meta{
    void print();
        
    unsigned short number_of_columns;
    unsigned int number_of_rows;
    std::vector<std::string> column_names;
    std::vector<unsigned short> column_types;
};

#endif //META_98RHG9E8HRG98HERG

    
