
#include "Relation.hpp"

#include <iostream>

using namespace std;

Relation::Relation(){
}

Relation::~Relation(){
    for(auto i:records){
        delete i;    
    }
}

void Relation::add_record(Record* rec){
    this->records.push_back(rec);
}

Meta& Relation::get_meta(){
    return meta;        
}

void Relation::set_size(){
    records.reserve(meta.rows());    
}

void Relation::print() const{
    meta.print();
    cout<<endl;
    
    for(auto i:records){
        i->print();    
    }
    cout<<"("<<meta.rows()<<" rows)"<<endl;
}



