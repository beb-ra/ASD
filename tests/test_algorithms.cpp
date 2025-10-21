#include <gtest/gtest.h>
#include <iostream>
#include "../lib_algorithms/algorithms.h"

TEST(TestAlgorithmsLib, test1) {
    EXPECT_TRUE(check_breckets("()()"));
}

TEST(TestAlgorithmsLib, test2) {
    EXPECT_TRUE(check_breckets("[(()())({})]"));
}

TEST(TestAlgorithmsLib, test3) {
    EXPECT_FALSE(check_breckets("(()()"));
}

TEST(TestAlgorithmsLib, test4) {
    EXPECT_FALSE(check_breckets("())(())"));
}

TEST(TestAlgorithmsLib, test5) {
    EXPECT_FALSE(check_breckets("((()()(())}"));
}

TEST(TestAlgorithmsLib, test6) {
    EXPECT_TRUE(check_breckets("{(()())(())}"));
}