
#include "Relation.hpp"
#include "Record.hpp"
#include "Record1.hpp"

#include <iostream>

using namespace std;

Meta& Relation::get_meta(){
    return meta;    
}

unsigned short Relation::get_number_of_columns() const{
    return meta.number_of_columns;
}
unsigned int Relation::get_number_of_rows() const{
    return meta.number_of_rows;
}
char Relation::get_column_type(unsigned int position) const{
    return meta.column_types[position];
}
string Relation::get_column_name(unsigned int position) const{
    return meta.column_names[position];
}
Record1* Relation::get_record(unsigned int position) const{
    return this->records.at(position);
}

void Relation::add_record(Record1* rec){
    this->records.push_back(rec);
}

void Relation::print() const{
    unsigned short num_cols = get_number_of_columns();
    unsigned int num_rows = get_number_of_rows();
    int i,j;

    for (i=0; i<num_cols; i++) {
	if (i != num_cols-1)
	    cout<<" "<< get_column_name(i)<<" |";
	else
	    cout<<" "<<get_column_name(i);
    }
    cout<<endl;

    for (i=0; i<num_cols; i++) {
    	for (j=0; j<get_column_name(i).length()+2; j++)
    	    cout<<"-";
    	if (i != num_cols-1)
    	    cout<<"+";
    }

    cout<<endl;

    //cout<<get_record(0)->get_element(0)->get_field()<<endl;
    unsigned short len,k;
    for (i=0; i<num_rows; i++) {
    	for (j=0; j<num_cols; j++) {
            Field* field = get_record(i)->get_element(j);
    	    len = (get_column_name(j).length() + 1) - field->get_size();
    	    for (k=0; k<len; k++)
    	    	cout<<" ";
            if(field->is_integer){
    	        cout<<field->n_field;
            }
            else{
    	        cout<<field->field;
            }
    	    if (j != num_cols-1)
    		cout<<" |";

    	}
    	cout<<endl;
    }
    cout<<"("<<num_rows<<" rows)"<<endl;

}


