
#ifndef RECORD_W98HRG9WEH8RG9W8HERG98WHERG
#define RECORD_W98HRG9WEH8RG9W8HERG98WHERG

#include "IntegerField.hpp"
#include "RawStringField.hpp"
#include "Constants.hpp"
#include "Meta.hpp"

#include <vector>
#include <iostream>
#include <cstring>

class Record{
    public:
        Record(const unsigned int size, Meta* meta);
        bool operator==(const Record& other) const;

        bool less_than(const Record& other, std::vector<unsigned int>& indexes) const;
        void add(RawStringField& field);
        void add(IntegerField& field);
        void print() const;
        unsigned int size() const;
        void remove(std::vector<unsigned int> indexes);
        bool is(std::vector<std::string> predicate); //only one predicate
        

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

    const unsigned int padding_string = 2;
    const unsigned int padding_integer = 1;

    for(int i=0; i<number_of_columns; ++i){

        if(meta->get_type(i)==TYPE_STRING){
            unsigned int len = meta->get_name(i).size() + padding_string - container_SF[SF_index].length();
            for(int k = 0; k < len; ++k) cout<<" ";
            container_SF[SF_index].print(); 
            cout<<" |";
            ++SF_index;
        }
        else if(meta->get_type(i)==TYPE_INTEGER){
            unsigned int len = meta->get_name(i).size() + padding_integer - container_IF[IF_index].number_of_digits();
            for(int k = 0; k < len; ++k) cout<<" ";
            container_IF[IF_index].print();    
            cout<<" |";
            ++IF_index;
        }
    }
    cout<<endl;
}

/*This cannot be that complicated!!!!!!!!*/
inline
void Record::remove(std::vector<unsigned int> indexes){
    std::vector<int> types;
    for(auto& i:indexes) types.push_back(meta->get_type(i));
    
    std::vector<unsigned int> indexes_original(indexes.size());
    std::copy(indexes.begin(), indexes.end(), indexes_original.begin());

    unsigned int count_SF = 0;
    unsigned int count_IF = 0;

    for(int i=0; i<indexes.size(); ++i){
        if(types[i] == TYPE_STRING){
            unsigned int number_of_strings = 0;
            for(unsigned int x = 0; x <= indexes_original[i]; ++x){
                if(meta->get_type(x) == TYPE_STRING) ++number_of_strings;
            }
            unsigned int index = 0;
            if(number_of_strings == 0) index = 0;
            else index = number_of_strings-1-count_SF;
            container_SF.erase(container_SF.cbegin()+index); 
            ++count_SF;
            for(auto& j : indexes) --j;
        }
        else{
            unsigned int number_of_integers = 0;
            for(unsigned int x = 0; x <= indexes_original[i]; ++x){
                if(meta->get_type(x) == TYPE_INTEGER) ++number_of_integers;
            }
            unsigned int index = 0;
            if(number_of_integers == 0) index = 0;
            else index = number_of_integers-1-count_IF;
            container_IF.erase(container_IF.cbegin()+index); 
            for(auto& j : indexes) --j;
            ++count_IF;
        }
    }
}

inline
bool Record::is(std::vector<std::string> predicate){//single predicate
    std::string op1 = predicate[0];
    std::string op2 = predicate[2];
    std::string op = predicate[1];

    //if(!meta->is_present(op2))//operator 2 is a number. 

    std::vector<std::string> operands = {op1};
    auto keys_indexes = meta->keys_indexes(operands);

    int type_op1 = meta->get_type(keys_indexes[0]);

    //std::cout<<"op1: "<<op1<<" id: "<<keys_indexes[0]<<" op2: "<<op2<<" op: "<<op<<" type: "<<meta->get_type(keys_indexes[0])<<std::endl;
    
    if(type_op1 == TYPE_STRING){
        unsigned int number_of_strings = 0;
        for(unsigned int x = 0; x <= keys_indexes[0]; ++x){
            if(meta->get_type(x) == TYPE_STRING) ++number_of_strings;
        }

        RawStringField field = container_SF[number_of_strings-1]; 

        if(op.compare("=")){
            field.print();
            std::cout<<"="<<op2<<std::endl;
            if(strcmp(field.raw_ptr(), op2.c_str()) == 0) return true;    
            return false;
        }
        else if(op.compare("<")){
            field.print();
            std::cout<<"<"<<op2<<std::endl;
            if(strcmp(field.raw_ptr(), op2.c_str())<0) return true;
            return false;
        }
        else if(op.compare(">")){
            field.print();
            std::cout<<">"<<op2<<std::endl;
            if(strcmp(field.raw_ptr(), op2.c_str())>0) return true;
            return false;
        }
    }
    else{
        std::cout<<"here!"<<std::endl;
        unsigned int number_of_ints = 0;
        for(unsigned int x = 0; x <= keys_indexes[0]; ++x){
            if(meta->get_type(x) == TYPE_INTEGER) ++number_of_ints;
        }
        std::cout<<"here1!"<<std::endl;

        IntegerField field = container_IF[number_of_ints-1]; 
        IntegerField tmp(atoi(op2.c_str()));
        field.print();
        std::cout<<op;
        tmp.print();
        std::cout<<"\n";
        std::cout<<"here2!"<<std::endl;


        if(!op.compare("=")) return field == tmp;    
        else if(!op.compare("<")) return field < tmp;
        else if(!op.compare(">")) return field > tmp;
    }
}

#endif //RECORD_W98HRG9WEH8RG9W8HERG98WHERG


