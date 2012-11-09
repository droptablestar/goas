
#include "Meta.hpp"

#include <iostream>
#include <algorithm>

using namespace std;


void Meta::print(){
    cout<<"number of columns: "<<number_of_columns<<endl;
    cout<<"number of rows: "<<number_of_rows<<endl;

    for_each(column_names.begin(), column_names.end(), [](string &e){
            cout<<e<<'\t'; 
        });
     
    cout<<endl;
     
    for_each(column_types.begin(), column_types.end(), [](unsigned short &e){
            cout<<e<<'\t';
        });
}




