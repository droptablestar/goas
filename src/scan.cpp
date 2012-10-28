#include "Relation.hpp"
#include "Record.hpp"
#include "Scan.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

string read_string_type(ifstream &file){
    char raw_data;
    vector<char> data;

    file.read(&raw_data, 1);
    while(raw_data!='\0'){
        data.push_back(raw_data);
        file.read(&raw_data, 1);
    }

    string name(data.begin(), data.end());
    return name;
}

void readMeta(ifstream &file, Relation *relation){
    unsigned short num_cols;
    unsigned int num_rows;
    file.read((char*)&num_cols, sizeof(num_cols));
    file.read((char*)&num_rows, sizeof(num_rows));

    relation->setNumberOfColumns(num_cols);
    relation->setNumberOfRows(num_rows);

    for(int i=0; i<num_cols; ++i){
        char type;
        file.read(&type, sizeof(type));

        relation->addColumnType(type);
        relation->addColumnName(read_string_type(file));
    }
}

void readTable(ifstream &file, Relation *relation){
    unsigned short num_cols = relation->getNumberOfColumns();
    unsigned int num_rows = relation->getNumberOfRows();
    stringstream ss;
    
    for(int i = 0; i<num_rows; ++i){
	Record rec;
        for(int j=0; j<num_cols; ++j){
	    char type;
	    type = relation->getColumnType(j);
            if(type == INT) {
                int number = 0;
                file.read((char*)&number, sizeof(number));
		ss << number;
		rec.addElement(ss.str());
		ss.str("");
	    }
	    else if(type == STRING){
		rec.addElement(read_string_type(file));
	    }
        }
	relation->addRecord(rec);
    }
}

void print(Relation *relation){
    unsigned short num_cols = relation->getNumberOfColumns();
    unsigned int num_rows = relation->getNumberOfRows();
    int i,j;

    for (i=0; i<num_cols; i++) {
	if (i != num_cols-1)
	    cout<<" "<< relation->getColumnName(i)<<" |";
	else
	    cout<<" "<<relation->getColumnName(i);
    }
    cout<<endl;

    for (i=0; i<num_cols; i++) {
    	for (j=0; j<relation->getColumnName(i).length()+2; j++)
    	    cout<<"-";
    	if (i != num_cols-1)
    	    cout<<"+";
    }
    cout<<endl;

    unsigned short len,k;
    for (i=0; i<num_rows; i++) {
    	for (j=0; j<num_cols; j++) {
    	    len = (relation->getColumnName(j).length() + 1) -
		relation->getRecord(i).getElement(j).length();
    	    for (k=0; k<len; k++)
    	    	cout<<" ";
    	    cout<<relation->getRecord(i).getElement(j);
    	    if (j != num_cols-1)
    		cout<<" |";
    	}
    	cout<<endl;
    }
    cout<<"("<<num_rows<<" rows)"<<endl;
}

Relation* scan(const char *file_name){
    ifstream myfile(file_name, ios::in|ios::binary);
    Relation *relation = new Relation;
    if(myfile.is_open()){
        readMeta(myfile, relation);
        readTable(myfile, relation);
	print(relation);
        // cout<<endl<<endl;
        // data.print();
    }
    else{cout<<"cuek!!!!!!!";}

    return relation;
}
