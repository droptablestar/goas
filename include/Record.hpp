
#ifndef RECORD_W98HRG9WEH8RG9W8HERG98WHERG
#define RECORD_W98HRG9WEH8RG9W8HERG98WHERG

#include "IntegerField.hpp"
#include "RawStringField.hpp"
#include "Constants.hpp"
#include "Meta.hpp"

#include <vector>
#include <iostream>

class Record{
    public:
        Record(const unsigned int size, Meta& meta);

        void add(RawStringField& field);
        void add(IntegerField& field);
        void print() const;

    private:
        std::vector<IntegerField> container_IF;
        std::vector<RawStringField> container_SF;
        const Meta& meta;
};

inline
Record::Record(const unsigned int size, Meta& meta):meta(meta){
    /*not further allocation of memory after this
    avoid wastefull copies, size is the number of 
    columns in the relation*/
    container_IF.reserve(meta.integers_in_record());    
    container_SF.reserve(meta.strings_in_record()); 
}

/*This is pretty cool, calling move, Im just calling
* the move constructor of RawStringField not the copy 
* constructor, improving the performance of the operation*/
inline
void Record::add(RawStringField& field){
    container_SF.push_back(std::move(field));        
}

inline
void Record::add(IntegerField& field){
    container_IF.push_back(field);        
}

inline
void Record::print() const{
    unsigned number_of_columns = meta.columns();
    unsigned int SF_index = 0;
    unsigned int IF_index = 0;

    using std::cout;
    using std::endl;

    for(int i=0; i<number_of_columns; ++i){
        if(meta.get_type(i)==TYPE_STRING){
            cout<<"| ";
            container_SF[SF_index].print(); 
            cout<<"  ";
            ++SF_index;
        }
        else if(meta.get_type(i)==TYPE_INTEGER){
            cout<<"| ";
            container_IF[IF_index].print();    
            cout<<"  ";
            ++IF_index;
        }
    }
    cout<<endl;
}

#endif //RECORD_W98HRG9WEH8RG9W8HERG98WHERG


