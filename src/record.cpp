#include "Record.hpp"

using namespace std;

void Record::addElement(string data) {
    this->data.push_back(data);
}

string Record::getElement(unsigned int position) {
    return this->data.at(position);
}
