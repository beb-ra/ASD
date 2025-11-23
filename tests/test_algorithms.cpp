#include <gtest/gtest.h>
#include <iostream>
#include "../lib_algorithms/algorithms.h"

TEST(TestAlgorithmsLib, test_check_brackets_1) {
    EXPECT_TRUE(check_brackets("()()"));
}

TEST(TestAlgorithmsLib, test_check_brackets_2) {
    EXPECT_TRUE(check_brackets("[(()())({})]"));
}

TEST(TestAlgorithmsLib, test_check_brackets_3) {
    EXPECT_FALSE(check_brackets("(()()"));
}

TEST(TestAlgorithmsLib, test_check_brackets_4) {
    EXPECT_FALSE(check_brackets("())(())"));
}

TEST(TestAlgorithmsLib, test_check_brackets_5) {
    EXPECT_FALSE(check_brackets("((()()(())}"));
}

TEST(TestAlgorithmsLib, test_check_brackets_6) {
    EXPECT_TRUE(check_brackets("{(()())(())}"));
}

TEST(TestAlgorithmsLib, test_read_expression_1) {
    EXPECT_NO_THROW(read_expression("3 *(15 + (x + y)*(2*x - 7*y^2))"));
}

TEST(TestAlgorithmsLib, test_read_expression_2) {
    EXPECT_THROW(read_expression("3 *(15 + (x y)*(2x - 7*y^2))"), std::logic_error);
}

TEST(TestAlgorithmsLib, test_read_expression_3) {
    EXPECT_THROW(read_expression("3 *(15 + (x + y)*(2*x - 7*y^))"), std::logic_error);
}

TEST(TestAlgorithmsLib, test_read_expression_4) {
    EXPECT_THROW(read_expression("((x + y)*(x - y)"), std::logic_error);
    EXPECT_THROW(read_expression("(13 + 52"), std::logic_error);
    EXPECT_THROW(read_expression("13 + )52"), std::logic_error);
}

TEST(TestAlgorithmsLib, test_read_expression_5) {
    EXPECT_NO_THROW(read_expression("-y * {[342 * (x + 16)] - 27}"));
    EXPECT_NO_THROW(read_expression("-x + 543 * y - (100 + 200)"));
}

TEST(TestAlgorithmsLib, test_read_expression_6) {
    EXPECT_THROW(read_expression("3 + $5"), std::logic_error);
}

TEST(TestAlgorithmsLib, test_read_expression_7) {
    EXPECT_THROW(read_expression(""), std::logic_error);
}

TEST(TestAlgorithmsLib, test_read_expression_8) {
    EXPECT_NO_THROW(read_expression("42"));
    EXPECT_NO_THROW(read_expression("x"));
}

TEST(TestAlgorithmsLib, test_read_expression_9) {
    EXPECT_THROW(read_expression("--x"), std::logic_error);
    EXPECT_THROW(read_expression("x ++ y"), std::logic_error);
}

TEST(TestAlgorithmsLib, test_read_expression_10) {
    EXPECT_THROW(read_expression("x * -y + 5"), std::logic_error);
}

TEST(TestAlgorithmsLib, test_read_expression_11) {
    EXPECT_NO_THROW(read_expression("x * (-y) + 5"));
}

TEST(TestAlgorithmsLib, test_read_expression_12) {
    EXPECT_THROW(read_expression("* 3 + 5"), std::logic_error);
}

TEST(TestAlgorithmsLib, test_read_expression_13) {
    EXPECT_NO_THROW(read_expression("  -  y   +  58   *   x  -  ( 200  /  3  ) "));
}

TEST(TestAlgorithmsLib, test_read_expression_14) {
    EXPECT_THROW(read_expression("3x + 5"), std::logic_error);
}
