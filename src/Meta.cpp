
#include "Meta.hpp"
#include "Constants.hpp"

#include <iostream>
#include <algorithm>
#include <unordered_set>

using namespace std;

Meta::Meta():ints_in_record(0),
            strs_in_record(0),
            n_columns(0),
            n_rows(0){}

bool Meta::operator==(const Meta& other) const{
    return ints_in_record == other.ints_in_record &&
        strs_in_record == other.strs_in_record &&
        n_columns == other.n_columns &&
        n_rows == other.n_rows &&
        equal(column_names.begin(), column_names.end(), other.column_names.begin()) &&
        equal(column_types.begin(), column_types.end(), other.column_types.begin());
}

void Meta::print() const{
    cout<<"number of columns: "<<n_columns<<endl;
    cout<<"number of rows: "<<n_rows<<endl;

    for(auto i:column_names){
        cout<<"|  "<<i<<"  ";    
    }
}

unsigned short Meta::columns() const{
    return n_columns;    
}

unsigned int Meta::rows() const{
    return n_rows;   
}

void Meta::set_columns(const unsigned short n_columns){
    this->n_columns = n_columns;    
}

void Meta::set_rows(const unsigned int n_rows){
    this->n_rows = n_rows;    
}

void Meta::add_column_name(string name){
    name.pop_back();/*this is because the string came from the file with
                    a weird character at the end!!!!*/
    column_names.push_back(name);
}

void Meta::add_column_type(const unsigned short type){
    if(type==TYPE_STRING) ++strs_in_record;
    else if(type==TYPE_INTEGER) ++ints_in_record;
    column_types.push_back(type);
}

unsigned short Meta::get_type(const unsigned int index) const{
    return column_types[index];    
}

string Meta::get_name(const unsigned int index) const{
    return column_names[index];    
}

unsigned short Meta::integers_in_record() const{
    return ints_in_record;    
}

unsigned short Meta::strings_in_record() const{
    return strs_in_record;    
}

/*interesting trade off, if i sorted the arrays im going to lose time
 * copying strings from one array to another, because i dont want to 
 * destroy the inputs arrays, copying I will achieved O(nlog(n)) without
 * considering the copies, if i dont do copies, i can do the O(n^2) approach,
 * but avoiding the copies and the extra data structures, because like I said
 * I cannot destroy the input vectors.*/

/*try to return the constness of this method*/
vector<string> Meta::keys_intersection(const vector<string>& keys) const{
    vector<string> result;
    for(auto a:keys){
        for(auto b:column_names){
            if(a.compare(b) == 0){
                result.push_back(a);
            }
        }
    }
    return result;
}

vector<unsigned int> Meta::keys_indexes(const vector<string>& keys) const{
    vector<unsigned int> result;
    for(auto i:keys){
        auto it = find(column_names.begin(), column_names.end(), i);
        result.push_back(distance(column_names.begin(), it));
    }

    return result;
}



