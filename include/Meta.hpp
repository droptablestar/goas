
#ifndef META_98RHG9E8HRG98HERG
#define META_98RHG9E8HRG98HERG

#include <vector>
#include <string>

class Meta{
    public:
        Meta();

        void print() const;
        unsigned short number_of_columns() const;
        unsigned int number_of_rows() const;
        void set_number_of_columns(const unsigned short n_columns);
        void set_number_of_rows(const unsigned int n_rows);
        void add_column_name(const std::string name);
        void add_column_type(const unsigned short type);
        unsigned short get_type(const unsigned int index) const;
        unsigned short integers_in_record() const;
        unsigned short strings_in_record() const;
       
    private:
        unsigned short ints_in_record;
        unsigned short strs_in_record;
        unsigned short n_columns;
        unsigned int n_rows;
        std::vector<std::string> column_names;
        std::vector<unsigned short> column_types;
};

#endif //META_98RHG9E8HRG98HERG

    
