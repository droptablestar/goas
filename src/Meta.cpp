
#include "Meta.hpp"

#include <iostream>
#include <algorithm>

using namespace std;

void Meta::print() const{
    cout<<"number of columns: "<<number_of_columns<<endl;
    cout<<"number of rows: "<<number_of_rows<<endl;

    for_each(column_names.begin(), column_names.end(), [](const string &e){
            cout<<" "<<e<<" "<<'|'; 
        });
     
    cout<<endl;
     
    for (int i=0; i<number_of_columns; i++) {
    	for(int j=0; j<column_names[i].length()+1; j++)
    	    cout<<"-";
    	    if (i != number_of_columns)
    	        cout<<"+";
    }
}




