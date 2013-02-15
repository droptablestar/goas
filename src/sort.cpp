
#include "Relation.hpp"
#include "Meta.hpp"

#include <vector>
#include <string>

using namespace std;

void sort(Relation& relation, vector<string>& keys, bool order) {

    /*check for an empty relation*/
    Meta* meta = relation.get_meta();

    auto keys_present = meta->keys_intersection(keys);
    auto keys_indexes = meta->keys_indexes(keys_present);
    
    if(order) relation.sort_ascendant(keys_indexes);
    else relation.sort_descendant(keys_indexes);
}
