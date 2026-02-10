#include <gtest/gtest.h>
#include <iostream>
#include "../lib_algorithms/algorithms.h"

TEST(TestAlgorithmsLib, test_island_counting) {
    Matrix<int> matrix(2, 2, { 0, 0, 0, 0 });
    int count = 0;

    EXPECT_EQ(island_counting(matrix), count);
}

TEST(TestAlgorithmsLib, test_island_counting_2) {
    Matrix<int> matrix(3, 3, { 1, 0, 0, 
                               0, 1, 0, 
                               0, 0, 1 });
    int count = 3;

    EXPECT_EQ(island_counting(matrix), count);
}

TEST(TestAlgorithmsLib, test_island_counting_3) {
    Matrix<int> matrix(3, 3, { 1, 0, 1,
                               0, 1, 0, 
                               0, 0, 1 });
    int count = 4;

    EXPECT_EQ(island_counting(matrix), count);
}

TEST(TestAlgorithmsLib, test_island_counting_4) {
    Matrix<int> matrix(3, 3, { 1, 1, 1, 
                               0, 1, 0, 
                               0, 0, 1 });
    int count = 2;

    EXPECT_EQ(island_counting(matrix), count);
}

TEST(TestAlgorithmsLib, test_island_counting_5) {
    Matrix<int> matrix(2, 2, { 1, 1, 1, 1 });
    int count = 1;

    EXPECT_EQ(island_counting(matrix), count);
}

TEST(TestAlgorithmsLib, test_island_counting_6) {
    Matrix<int> matrix(1, 1, { 1 });
    int count = 1;

    EXPECT_EQ(island_counting(matrix), count);
}

TEST(TestAlgorithmsLib, test_island_counting_7) {
    Matrix<int> matrix(3, 3, {
        0, 1, 0,
        1, 1, 1,
        0, 1, 0
        });
    int count = 1;

    EXPECT_EQ(island_counting(matrix), count);
}

TEST(TestAlgorithmsLib, test_island_counting_8) {
    Matrix<int> matrix(5, 5, {
        0, 1, 0, 0, 1,
        0, 1, 1, 0, 1,
        1, 1, 0, 1, 1,
        0, 0, 0, 0, 1,
        1, 0, 1, 1, 1
        });
    int count = 3;

    EXPECT_EQ(island_counting(matrix), count);
}


