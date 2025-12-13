#include <gtest/gtest.h>
#include "../lib_algorithms/algorithms.h"

#define EPSILON 0.1
#define PI 3.14

TEST(TestAlgorithmsLib, correct_abs) {
    EXPECT_EQ(123, my_abs(123));
    EXPECT_EQ(123, my_abs(-123));
    EXPECT_NEAR(1.23, my_abs(-1.23), EPSILON);
}

TEST(TestAlgorithmsLib, correct_convert_to_radians) {
    EXPECT_NEAR(0.0, convert_to_radians(0), EPSILON);
    EXPECT_NEAR(PI, convert_to_radians(180), EPSILON);
    EXPECT_NEAR(2 * PI, convert_to_radians(360), EPSILON);
    EXPECT_NEAR(PI / 2, convert_to_radians(90), EPSILON);
    EXPECT_NEAR(-PI, convert_to_radians(-180), EPSILON);
    EXPECT_NEAR(PI / 4, convert_to_radians(45), EPSILON);
    EXPECT_NEAR(-PI / 4, convert_to_radians(-45), EPSILON);
}

TEST(TestAlgorithmsLib, correct_sin) {
    EXPECT_NEAR(0.0, my_sin(0), EPSILON);
    EXPECT_NEAR(0.5, my_sin(30), EPSILON);
    EXPECT_NEAR(1.0, my_sin(90), EPSILON);
    EXPECT_NEAR(0.0, my_sin(180), EPSILON);
    EXPECT_NEAR(-1.0, my_sin(270), EPSILON);
    EXPECT_NEAR(0.0, my_sin(360), EPSILON);
    EXPECT_NEAR(-0.5, my_sin(-30), EPSILON);
    EXPECT_NEAR(-1.0, my_sin(-90), EPSILON);
    EXPECT_NEAR(1.0, my_sin(450), EPSILON);
    EXPECT_NEAR(0.0, my_sin(720), EPSILON);
}

TEST(TestAlgorithmsLib, correct_cos) {
    EXPECT_NEAR(1.0, my_cos(0), EPSILON);
    EXPECT_NEAR(0.5, my_cos(60), EPSILON);
    EXPECT_NEAR(0.0, my_cos(90), EPSILON);
    EXPECT_NEAR(-1.0, my_cos(180), EPSILON);
    EXPECT_NEAR(0.0, my_cos(270), EPSILON);
    EXPECT_NEAR(1.0, my_cos(360), EPSILON);
    EXPECT_NEAR(0.5, my_cos(-60), EPSILON);
    EXPECT_NEAR(0.0, my_cos(-90), EPSILON);
    EXPECT_NEAR(-1.0, my_cos(-180), EPSILON);
    EXPECT_NEAR(0.5, my_cos(420), EPSILON);
    EXPECT_NEAR(0.5, my_cos(-300), EPSILON);
}

TEST(TestAlgorithmsLib, correct_tg) {
    EXPECT_NEAR(0.0, my_tg(0), EPSILON);
    EXPECT_NEAR(1.0, my_tg(45), EPSILON);
    EXPECT_NEAR(-1.0, my_tg(-45), EPSILON);
    EXPECT_NEAR(0.0, my_tg(180), EPSILON);
    EXPECT_NEAR(0.0, my_tg(360), EPSILON);
}

TEST(TestAlgorithmsLib, correct_throw_tg) {
    EXPECT_THROW(my_tg(90), std::invalid_argument);
    EXPECT_THROW(my_tg(270), std::invalid_argument);
    EXPECT_THROW(my_tg(-90), std::invalid_argument);
    EXPECT_THROW(my_tg(90 + 360), std::invalid_argument);
    EXPECT_NO_THROW(my_tg(89.9));
    EXPECT_NO_THROW(my_tg(90.1));
}
