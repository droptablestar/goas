
#include "Record.hpp"

#include <algorithm>
#include <iostream>

using namespace std;

void Record::add_element(string data) {
        this->data.push_back(data);
}

string Record::get_element(unsigned int position) {
        return this->data.at(position);
}

void Record::print(){
    for_each(data.begin(), data.end(), [](string& e){
            cout<<e<<"|";    
        });
    cout<<endl;
}

