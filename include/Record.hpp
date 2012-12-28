
#ifndef RECORD_W98HRG9WEH8RG9W8HERG98WHERG
#define RECORD_W98HRG9WEH8RG9W8HERG98WHERG

#include "Field.hpp"

#include <vector>
#include <iostream>

using namespace std;

class Record{
    public:
        Record(const unsigned int size){
            /*not further allocation of memory after this
             avoid wastefull copies, size is the number of 
             columns in the relation*/
            container.reserve(size);    
        }

        ~Record(){
            for(auto i:container){
                delete i;    
            }
        }

        Record(const Record& other):container(other.container.size()){//this prevent the resizing.
            for(int i=0; i<container.size(); ++i){
                container[i] = other.container[i]->clone();
            }
        }

        void add(Field* field){
            container.push_back(field);        
        }

        /*which would be the maximum number of this vector, 
        number of columns. For now I'll limit this container
        to unsigned int*/
        /*Return a reference to avoid copy*/
        Field* get(const unsigned int index) const{
            /*not "at" to avoid exceptions
            (will trust in the programmer for now).*/
            return container[index]; 
        }

        void print() const{
            for(auto i:container){
                std::cout<<"|  ";
                i->print();
                std::cout<<"  ";
            }    
            std::cout<<std::endl;
        }

    private:
        std::vector<Field*> container;
};

#endif //RECORD_W98HRG9WEH8RG9W8HERG98WHERG
