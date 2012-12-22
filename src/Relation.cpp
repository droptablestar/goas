
#include "Relation.hpp"

#include <iostream>

using namespace std;

void Relation::add_record(Record& rec){
    this->records.push_back(rec);
}

Meta& Relation::get_meta(){
    return meta;        
}

void Relation::set_size(){
    records.reserve(meta.number_of_rows());    
}

void Relation::print() const{

    meta.print();
    cout<<endl;
    
    for(auto i:records){
        i.print();    
    }

    cout<<"("<<meta.number_of_rows()<<" rows)"<<endl;
}



