
#include "Record.hpp"

#include <algorithm>
#include <iostream>

using namespace std;

void Record::addElement(string data) {
    this->data.push_back(data);
}

string Record::getElement(unsigned int position) {
    return this->data.at(position);
}

void Record::print(){
    for_each(data.begin(), data.end(), [](string& e){
            cout<<e<<"|";    
        });
    cout<<endl;
}
