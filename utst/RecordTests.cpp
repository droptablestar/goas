
#include "Record.hpp"
#include "Meta.hpp"
#include "MetaBasicPopulator.hpp"
#include "RecordBasicPopulator.hpp"
#include "IntegerField.hpp"
#include "RawStringField.hpp"


#include <gtest/gtest.h>

#include <string>

#include <cstring>
#include <memory.h>

using namespace std;

class RecordBasicPopulator{
    public:
        RecordBasicPopulator(Record& record, string field):record(record),
                                                        string_field(field){}

        void operator()(){
            for(unsigned short i = 0; i<8; ++i){
                IntegerField field(i);
                record.add(field);
            }

            for(unsigned short i = 8; i<16; ++i){
                const char* field_raw = string_field.c_str();
                RawStringField field(strlen(field_raw));    
                memcpy(field.raw_ptr(), field_raw, strlen(field_raw));
                record.add(field);
            }
        }
    private:
        Record& record;
        string string_field;
        
};

TEST(RecordTests, record_creation){
    const unsigned int rows = 1;
    const unsigned short columns = 16;

    Meta meta;
    MetaBasicPopulator meta_populator(meta);

    meta_populator.rows(rows);
    meta_populator.columns(columns);
    meta_populator.colum_names();
    meta_populator.column_types();

    Record record(meta.columns(), &meta);
    RecordBasicPopulator record_populator(record, "test");
    record_populator();

    EXPECT_EQ(columns, record.size());
}

TEST(RecordTests, copy_constructor){
    const unsigned int rows = 1;
    const unsigned short columns = 16;

    Meta meta;
    MetaBasicPopulator meta_populator(meta);

    meta_populator.rows(rows);
    meta_populator.columns(columns);
    meta_populator.colum_names();
    meta_populator.column_types();
    
    Record record(meta.columns(), &meta);
    RecordBasicPopulator record_populator(record, "test");
    record_populator();

    Record new_record(record);

    EXPECT_EQ(new_record, record);
}

TEST(RecordTests, assignment){
    const unsigned int rows = 1;
    const unsigned short columns = 16;

    Meta meta;
    MetaBasicPopulator meta_populator(meta);

    meta_populator.rows(rows);
    meta_populator.columns(columns);
    meta_populator.colum_names();
    meta_populator.column_types();
    
    Record record(meta.columns(), &meta);
    RecordBasicPopulator record_populator(record, "test");
    record_populator();

    Record new_record(meta.columns(), &meta);
    RecordBasicPopulator new_record_populator(new_record, "test1");
    new_record_populator();

    record = new_record;

    EXPECT_EQ(new_record, record);
}

TEST(RecordTests, less_than){
    const unsigned int rows = 1;
    const unsigned short columns = 5;

    Meta meta;
    meta.set_columns(columns);

    meta.add_column_type(TYPE_INTEGER);
    meta.add_column_type(TYPE_INTEGER);
    meta.add_column_type(TYPE_INTEGER);
    meta.add_column_type(TYPE_INTEGER);
    meta.add_column_type(TYPE_INTEGER);

    meta.add_column_name("name1");
    meta.add_column_name("name2");
    meta.add_column_name("name3");
    meta.add_column_name("name4");
    meta.add_column_name("name5");

    Record a(meta.columns(), &meta);
    
    IntegerField a0(5);
    IntegerField a1(5);
    IntegerField a2(4);
    IntegerField a3(5);
    IntegerField a4(5);
    
    a.add(a0);
    a.add(a1);
    a.add(a2);
    a.add(a3);
    a.add(a4);

    Record b(meta.columns(), &meta);
    
    IntegerField b0(5);
    IntegerField b1(5);
    IntegerField b2(5);
    IntegerField b3(5);
    IntegerField b4(5);
    
    b.add(b0);
    b.add(b1);
    b.add(b2);
    b.add(b3);
    b.add(b4);

    vector<unsigned int> indexes;
    indexes.push_back(1);
    indexes.push_back(2);
    indexes.push_back(3);

    EXPECT_TRUE(a.less_than(b, indexes));
}





