
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
        Record(const unsigned int size, Meta* meta);
        bool operator==(const Record& other) const;

        bool less_than(const Record& other, std::vector<unsigned int>& indexes) const;
        void add(RawStringField& field);
        void add(IntegerField& field);
        void print() const;
        unsigned int size() const;
        

    private:
        std::vector<IntegerField> container_IF;
        std::vector<RawStringField> container_SF;
        Meta* meta;/*this has to be a pointer to 
                    provide value semantics to this type*/
};

inline
Record::Record(const unsigned int size, Meta* meta):meta(meta){
    /*not further allocation of memory after this
    avoid wastefull copies, size is the number of 
    columns in the relation*/
    container_IF.reserve(meta->integers_in_record());    
    container_SF.reserve(meta->strings_in_record()); 
}

inline 
bool Record::operator==(const Record& other) const{
    bool cont_if = equal(container_IF.begin(), container_IF.end(), other.container_IF.begin());
    bool cont_sf = equal(container_SF.begin(), container_SF.end(), other.container_SF.begin());

    return cont_if && cont_sf && (meta == other.meta);
}

/*I dont like it, is inneficient, transversing every time part of the record to get the right field!!!!!
 * maybe sacrifice a little time in scanning and put there the information already in record*/
inline 
bool Record::less_than(const Record& other, std::vector<unsigned int>& indexes) const{
    for(unsigned int i = 0; i < indexes.size(); ++i){
        if(meta->get_type(indexes[i]) == TYPE_INTEGER){
            unsigned int number_of_integers = 0;
            for(unsigned int x = 0; x <= indexes[i]; ++x){
                if(meta->get_type(x) == TYPE_INTEGER) ++number_of_integers;
            }

            if(this->container_IF[number_of_integers-1] < other.container_IF[number_of_integers-1]) return true;
            if(this->container_IF[number_of_integers-1] > other.container_IF[number_of_integers-1]) return false;
        }
        if(meta->get_type(indexes[i]) == TYPE_STRING){
            unsigned int number_of_strings = 0;
            for(unsigned int x = 0; x <= indexes[i]; ++x){
                if(meta->get_type(x) == TYPE_STRING) ++number_of_strings;
            }

            if(this->container_SF[number_of_strings-1] < other.container_SF[number_of_strings-1]) return true;
            if(this->container_SF[number_of_strings-1] > other.container_SF[number_of_strings-1]) return false;
        }
    }
    return false;// could be any return at this point because the records are completely equal given the keys.
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
unsigned int Record::size() const{
    return container_IF.size() + container_SF.size();    
}

inline
void Record::print() const{
    unsigned number_of_columns = meta->columns();
    unsigned int SF_index = 0;
    unsigned int IF_index = 0;

    using std::cout;
    using std::endl;

    for(int i=0; i<number_of_columns; ++i){
        if(meta->get_type(i)==TYPE_STRING){
            cout<<"| ";
            container_SF[SF_index].print(); 
            cout<<"  ";
            ++SF_index;
        }
        else if(meta->get_type(i)==TYPE_INTEGER){
            cout<<"| ";
            container_IF[IF_index].print();    
            cout<<"  ";
            ++IF_index;
        }
    }
    cout<<endl;
}

#endif //RECORD_W98HRG9WEH8RG9W8HERG98WHERG


