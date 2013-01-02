
#include "IntegerField.hpp"

#include <gtest/gtest.h>

using namespace std;

TEST(IntegerFieldTests, not_equality){
    IntegerField x(5);
    IntegerField y(6);

    EXPECT_NE(x, y);
}

TEST(IntegerFieldTests, equality){
    IntegerField x(5);
    IntegerField y(5);

    EXPECT_EQ(x, y);
}

TEST(IntegerFieldTests, copy_constructor){
    IntegerField x(5);
    IntegerField y = x;

    EXPECT_EQ(x, y);
}

TEST(IntegerFieldTests, assignment){
    IntegerField x(5);
    IntegerField y(3);

    y = x;

    EXPECT_EQ(x, y);
}
