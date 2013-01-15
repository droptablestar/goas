
#include "Relation.hpp"

#include <iostream>
#include <algorithm>

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

/*is returning a pointer because other classes store
 * a pointer to a unique meta object, this is the more
 * performant option that I found, not a nice design though*/
Meta* Relation::get_meta(){
    return &meta;        
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

void Relation::sort(){
    cout<<"relation sorting.....!!!!!"<<endl;    
    using std::sort;
    sort(records.begin(), records.end()); 
}



