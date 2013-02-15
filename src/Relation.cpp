
#include "Relation.hpp"
#include "Record.hpp"

#include <iostream>
#include <algorithm>

using namespace std;

class Comparator{
    public:
        Comparator(vector<unsigned int>& indexes):indexes(indexes){}
        bool operator()(Record* a, Record* b){
            /*this should be < not less_than*/
            bool ret = (*a).less_than(*b, indexes);
            return ret;
        }

    private:
        vector<unsigned int>& indexes;
};

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
    
    for(auto& i:records){
        i->print();    
    }
    cout<<"("<<meta.rows()<<" rows)"<<endl;
}

void Relation::sort_ascendant(vector<unsigned int>& indexes){
    Comparator comparator(indexes);
    using std::sort;
    sort(records.begin(), records.end(), comparator); 
}

void Relation::sort_descendant(vector<unsigned int>& indexes){
    Comparator comparator(indexes);
    using std::sort;
    sort(records.rbegin(), records.rend(), comparator); 
}

void Relation::project(vector<unsigned int>& indexes){
    for(auto& i : records) i->remove(indexes);
    meta.remove(indexes);
}

