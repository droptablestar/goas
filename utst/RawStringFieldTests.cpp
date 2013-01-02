#include "RawStringField.hpp"

#include <gtest/gtest.h>

using namespace std;

TEST(RawStringFieldTests, normal_construction){
    const unsigned int size = 5;

    char x_raw[size] = "test";
    RawStringField x(size);

    memcpy(x.raw_ptr(), x_raw, size); 

    EXPECT_EQ(size, x.length());
    EXPECT_STREQ("test", x.raw_ptr());
}

TEST(RawStringFieldTests, copy_construction){
    const unsigned int size = 5;

    char x_raw[size] = "test";
    RawStringField x(size);

    memcpy(x.raw_ptr(), x_raw, size); 

    RawStringField y = x;

    EXPECT_EQ(size, y.length());
    EXPECT_STREQ("test", y.raw_ptr());
    EXPECT_EQ(size, x.length());
    EXPECT_STREQ("test", x.raw_ptr());
    EXPECT_EQ(x, y);
}

TEST(RawStringFieldTests, assignment){
    const unsigned int size = 5;
    char x_raw[size] = "test";
    RawStringField x(size);

    memcpy(x.raw_ptr(), x_raw, size); 

    char y_raw[size] = "tesa";
    RawStringField y(size);

    memcpy(y.raw_ptr(), y_raw, size); 

    x = y;
    
    EXPECT_EQ(size, x.length());
    EXPECT_EQ(size, y.length());
    EXPECT_STREQ("tesa", x.raw_ptr());
    EXPECT_STREQ("tesa", y.raw_ptr());
}

void foo(RawStringField word, const unsigned int expected_size){
    EXPECT_EQ(expected_size, word.length());
    EXPECT_STREQ("test", word.raw_ptr());
}

/*candidate to apply mocking, to know if Im really calling
the move constructor, just to be 100% sure*/
TEST(RawStringFieldTests, move_construction){
    const unsigned int size = 5;
    char x_raw[size] = "test";
    RawStringField x(size);

    memcpy(x.raw_ptr(), x_raw, size); 
    
    foo(move(x), size);
}


TEST(RawStringFieldTests, equality){
    const unsigned int size = 5;

    char x_raw[size] = "test";
    RawStringField x(size);

    memcpy(x.raw_ptr(), x_raw, size); 

    char y_raw[size] = "test";
    RawStringField y(size);

    memcpy(y.raw_ptr(), y_raw, size); 

    EXPECT_EQ(x, y);
}

TEST(RawStringFieldTests, not_equality){
    const unsigned int size_x = 5;
    char x_raw[size_x] = "test";
    RawStringField x(size_x);

    memcpy(x.raw_ptr(), x_raw, size_x); 

    const unsigned int size_y = 6;
    char y_raw[size_y] = "test1";
    RawStringField y(size_y);

    memcpy(y.raw_ptr(), y_raw, size_y); 

    EXPECT_NE(x, y);
}



