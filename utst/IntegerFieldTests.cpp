
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

TEST(IntegerFieldTests, number_of_digits_one_digit){
    IntegerField x(5);

    unsigned int expected_number = 1;

    EXPECT_EQ(expected_number, x.number_of_digits());
}

TEST(IntegerFieldTests, number_of_digits_two_digit){
    IntegerField x(51);

    unsigned int expected_number = 2;

    EXPECT_EQ(expected_number, x.number_of_digits());
}

TEST(IntegerFieldTests, number_of_digits_three_digit){
    IntegerField x(565);

    unsigned int expected_number = 3;

    EXPECT_EQ(expected_number, x.number_of_digits());
}

TEST(IntegerFieldTests, number_of_digits_eight_digit){
    IntegerField x(12345678);

    unsigned int expected_number = 8;

    EXPECT_EQ(expected_number, x.number_of_digits());
}

TEST(IntegerFieldTests, number_of_digits_zero){
    IntegerField x(0);

    unsigned int expected_number = 1;

    EXPECT_EQ(expected_number, x.number_of_digits());
}


