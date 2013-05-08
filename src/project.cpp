
#include "Project.hpp"
#include "Relation.hpp"

using namespace std;

void project(Relation& relation, vector<string>& keys){
   /*check for an empty relation*/

   Meta* meta = relation.get_meta();

   /*what happens if any of the keys are in the relation!!!! is_projectable() the relation*/
    auto keys_present = meta->keys_intersection(keys);
    auto keys_indexes = meta->keys_indexes(keys_present);

    relation.project(keys_indexes);

}
