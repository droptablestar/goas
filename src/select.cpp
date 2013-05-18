
#include "Select.hpp"
#include "Relation.hpp"

#include <iostream>

using namespace std;

void select(Relation& relation, std::vector<std::string>& predicates){
    cout<<"selecting..."<<endl;
    
    /*check that the relation is not empty.*/ 

    /*TODO: arguments is a transformation vector or regular expression*/
    //auto result = relation.transform(predicates);

    /*check if the keys are in the relation*/
    /*check, wich kes are in the relation*/
    /*if no keys in the relation match keys return the relation*/
    /*get the indexes of the keys present in the relation*/
    /*delete the records that doesnt match the selection*/
    relation.erase(predicates);
    /*maintain everything tidy and adjacent*/
}
