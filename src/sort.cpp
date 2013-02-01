
#include "Relation.hpp"
#include "Meta.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void sort(Relation& relation, vector<string>& keys, bool order) {
    cout<<"Sorting......."<<endl;
    cout<<"---------------------------------------------------"<<endl;

    /*check for an empty relation*/
    Meta* meta = relation.get_meta();
    auto keys_present = meta->keys_intersection(keys);
    cout<<"present? "<<keys_present.size()<<endl;
    auto keys_indexes = meta->keys_indexes(keys_present);
    cout<<"indexes? "<<keys_indexes.size()<<endl;

    relation.sort(keys_indexes);

    cout<<endl;
    cout<<"---------------------------------------------------"<<endl;
}
