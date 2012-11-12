
#ifndef RECORD_W98HRG9WEH8RG9W8HERG98WHERG
#define RECORD_W98HRG9WEH8RG9W8HERG98WHERG

#include <vector>

class Field{
    public:
        Field(const unsigned int size, const char* field);
        Field(int field);

        const char* get_field() const;
        unsigned int get_n_field() const;
        unsigned int get_size() const;
        bool is_int() const;

    //private:
        const unsigned int size;
        const char* field;
        int n_field;
        bool is_integer;
};

class Record1{
    public:
        
        void add_element(Field* field);
        Field* get_element(const unsigned int index) const;

    private:
        std::vector<Field*> fields;
};

#endif //RECORD_W98HRG9WEH8RG9W8HERG98WHERG
