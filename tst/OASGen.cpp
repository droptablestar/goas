#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

#define INT 0
#define STRING 1
string EOS = "\0";

class MetaData {

private:
  unsigned short num_cols;
  vector<unsigned short> c_sizes;
  vector<string> c_names;
  vector<char> c_types;

public:
  MetaData() : num_cols(0) {}
  
  void addColumn(string name, unsigned short size, char type) {
    this->c_sizes.push_back(size);
    this->c_names.push_back(name);
    this->c_types.push_back(type);
    num_cols++;
  }
  
  unsigned short getSize(unsigned short position) {
    return this->c_sizes.at(position);
  }
  
  string getName(unsigned short position) {
    return this->c_names.at(position);
  }

  unsigned short getNumCols() {
    return this->num_cols;
  }

  char getType(unsigned short position) {
    return this->c_types.at(position);
  }
};

class Record {
private:
  vector<string> data;
  
public:
  void setData(string data, unsigned short size) {
    // data.resize(size);
    this->data.push_back(data);
  }

  string getData(int position) {
    return this->data.at(position);
  }
};

class Relation {

private:
  MetaData column_meta;
  vector<Record> records;
  unsigned int num_records;

public:
  Relation() : num_records(0) {}

  void addRecord(Record r) {
    this->records.push_back(r);
    num_records++;
  }
  Record getRecord(int position) {
    return this->records.at(position);
  }
  int getNumRecords() {
    return num_records;
  }
};

class OASGen {

private:
  string tablename;
  long tuples;
  long prime;
  long generator;
  MetaData meta;
  Relation relation;
  
  long rand(long seed, long limit) {
    do {
      seed = (generator * seed) % prime;
    } while(seed > limit);
    return seed;
  }
  
public:
  MetaData getMeta() {
    return this->meta;
  }
  
  Relation getRelation() {
    return this->relation;
  }
  
  OASGen(string,long);

  void generate() {
    long seed;
    
    meta.addColumn("unique1",10,INT);
    meta.addColumn("unique2",10,INT);
    meta.addColumn("two",10,INT);
    meta.addColumn("four",10,INT);
    meta.addColumn("ten",10,INT);
    meta.addColumn("twenty",10,INT);
    meta.addColumn("onepercent",10,INT);
    meta.addColumn("tenpercent",10,INT);
    meta.addColumn("twentypercent",10,INT);
    meta.addColumn("fiftypercent",10,INT);
    meta.addColumn("unique3",10,INT);
    meta.addColumn("even",10,INT);
    meta.addColumn("odd",10,INT);
    meta.addColumn("stringu1",10,STRING);
    meta.addColumn("stringu2",10,STRING);
    meta.addColumn("stringu4",10,STRING);

    seed = generator;
    
    for (int i=0; i<tuples; i++) {
      int j=0;
      Record r;
      seed = rand(seed, (long) tuples);

      long unique1;
      stringstream unique1_s;
      unique1 = seed - 1;
      unique1_s << unique1;

      long unique2;
      stringstream unique2_s;
      unique2 = i;
      unique2_s << unique2;

      long two;
      stringstream two_s;
      two = (unique1 % 2);
      two_s << two;

      long four;
      stringstream four_s;
      four = unique1 % 4;
      four_s << unique1 % 4;

      long ten;
      stringstream ten_s;
      ten = unique1 % 10; 
      ten_s << unique1 % 10; 

      long twenty;
      stringstream twenty_s;
      twenty = unique1 % 20; 
      twenty_s << unique1 % 20; 

      long onePercent;
      stringstream onePercent_s;
      onePercent = unique1 % 100;
      onePercent_s << unique1 % 100;

      long tenPercent;
      stringstream tenPercent_s;
      tenPercent = unique1 % 10;
      tenPercent_s << unique1 % 10;

      long twentyPercent;
      stringstream twentyPercent_s;
      twentyPercent = unique1 % 5;
      twentyPercent_s << unique1 % 5;

      long fiftyPercent;
      stringstream fiftyPercent_s;
      fiftyPercent = unique1 % 2;
      fiftyPercent_s << unique1 % 2;

      long unique3;
      stringstream unique3_s;
      unique3 = unique1;
      unique3_s << unique1;

      long evenOnePercent ;
      stringstream evenOnePercent_s;
      evenOnePercent = onePercent * 2;
      evenOnePercent_s << onePercent * 2;

      long oddOnePercent;
      stringstream oddOnePercent_s;
      oddOnePercent = (onePercent * 2)+1;
      oddOnePercent_s << (onePercent * 2)+1;

      string stringu1 = cycle((int) unique1);
      string stringu2 = cycle((int) unique2);
      string stringu4 = cycle((int) twenty);

      r.setData(unique1_s.str(),meta.getSize(j++));
      r.setData(unique2_s.str(),meta.getSize(j++));
      r.setData(two_s.str(),meta.getSize(j++));
      r.setData(four_s.str(),meta.getSize(j++));
      r.setData(ten_s.str(),meta.getSize(j++));
      r.setData(twenty_s.str(),meta.getSize(j++));
      r.setData(onePercent_s.str(),meta.getSize(j++));
      r.setData(tenPercent_s.str(),meta.getSize(j++));
      r.setData(twentyPercent_s.str(),meta.getSize(j++));
      r.setData(fiftyPercent_s.str(),meta.getSize(j++));
      r.setData(unique3_s.str(),meta.getSize(j++));
      r.setData(evenOnePercent_s.str(),meta.getSize(j++));
      r.setData(oddOnePercent_s.str(),meta.getSize(j++));
      r.setData(stringu1,meta.getSize(j++));
      r.setData(stringu2,meta.getSize(j++));
      r.setData(stringu4,meta.getSize(j++));

      this->relation.addRecord(r);
    }
  }

  string cycle(int unique) {
    switch (unique % 4) {
      case 0: return "AAAAAAA";
      case 1: return "HHHHHHH";
      case 2: return "VVVVVVV";
      default: return "OOOOOOO";
    }
  }

};

OASGen::OASGen (string tablename, long tuples) {
  this->tablename = tablename;
  this->tuples=tuples;
  if (tuples <= 1000) { generator = 279; prime = 1009; }
  else if (tuples <= 10000) { generator = 2969; prime = 10007; }
  else if (tuples <= 100000) { generator = 21395; prime = 100003; }
  else if (tuples <= 1000000) { generator = 2107; prime = 1000003; }
  else if (tuples <= 10000000) { generator = 211; prime = 10000019; }
  else if (tuples <= 100000000) { generator = 21; prime = 100000007; }
}
int main(int argc, char **argv) {
  string usage = "usage ./a.out <table-name> <number-of-tuple>";

  try {
    long tuples;
    stringstream tuples_s;
    string tablename = argv[1];
    
    // cout << argv[1] << " " << argv[2] << endl;
    tuples_s << argv[2];
    tuples_s >> tuples;

    OASGen oasgen(tablename, tuples);
    oasgen.generate();

    Relation rel = oasgen.getRelation();
    MetaData meta = oasgen.getMeta();
    unsigned int num_rows = rel.getNumRecords();
    unsigned short num_cols = meta.getNumCols();
    
    ofstream file (argv[1], ios::out | ios::binary);
    cout << num_cols << " " << sizeof(num_cols) << endl;

    file.write((char *)&num_cols, sizeof(num_cols));
    file.write((char *)&num_rows, sizeof(num_rows));

    unsigned short size;
    char type;
    string data;
    // write meta data to file
    for (unsigned short i=0; i<num_cols; i++) {
      data = meta.getName(i);
      type = meta.getType(i);
      file.write((char *)&type, sizeof(type));

      // if (type == STRING) {
      //   // column length
      //   size = meta.getSize(i);
      //   file.write((char *)&size, sizeof(size));
        
      // }
      // // length of column name
      size = data.length();
      // file.write((char *)&size, sizeof(size));
      
      // column name
      file.write(data.c_str(), size);
      file.write(EOS.c_str(), 1);
    }

    int data_i;
    for (unsigned int i=0; i<num_rows; i++) {
      for (unsigned short j=0; j<num_cols; j++) {
        type = meta.getType(j);
        data = rel.getRecord(i).getData(j);
	// cout<<data<<"\t";
        switch(type) {
          case INT:
            data_i = atoi(data.c_str());
            file.write(reinterpret_cast<const char *>(&data_i), sizeof(int));
            break;
          case STRING:
            file.write(data.c_str(), data.length());
            file.write(EOS.c_str(), 1);
        }
      }
	// cout<<endl;
    }
    file.close();
  }
  catch(int e) {
      cout << "Error 0 " << e << endl;
  }
  return 0;
}
