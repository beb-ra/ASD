#include <gtest/gtest.h>
#include <iostream>
#include "../lib_algorithms/algorithms.h"

TEST(TestAlgorithmsLib, test1) {
    Matrix<int> matrix(3, 3, { 3, 1, 2, 5, 8, 4, 7, 6, 9 });
    int min1 = 1, min2 = 6;

    EXPECT_TRUE(local_min(matrix, 0, 0) == min1 || local_min(matrix, 0, 0) == min2);
}

TEST(TestAlgorithmsLib, test2) {
    Matrix<int> matrix(3, 3, { 3, 1, 2, 5, 8, 4, 7, 6, 9 });
    int min1 = 1, min2 = 6;

    EXPECT_TRUE(local_min(matrix, 2, 2) == min1 || local_min(matrix, 2, 2) == min2);
}

TEST(TestAlgorithmsLib, test3) {
    Matrix<int> matrix(3, 3, { 3, 1, 2, 5, 8, 4, 7, 6, 9 });
    int min1 = 1, min2 = 6;

    EXPECT_TRUE(local_min(matrix, 2, 0) == min1 || local_min(matrix, 2, 0) == min2);
}

TEST(TestAlgorithmsLib, test4) {
    Matrix<int> matrix(3, 3, { 3, 1, 2, 5, 8, 4, 7, 6, 9 });
    int min1 = 1, min2 = 6;

    EXPECT_TRUE(local_min(matrix, 0, 1) == min1 && local_min(matrix, 2, 1) == min2);
}

TEST(TestAlgorithmsLib, test5) {
    Matrix<int> matrix(4, 4, { 1, 3, 0, 2,   -2, 6, 1, 11,   9, -3, 4, 8,   -1, -4, 5, 7 });
    int min1 = 0, min2 = -2, min3 = -4;

    EXPECT_TRUE(local_min(matrix, 0, 0) == min1 || local_min(matrix, 0, 0) == min2 ||
        local_min(matrix, 0, 0) == min3);
}

TEST(TestAlgorithmsLib, test6) {
    Matrix<int> matrix(4, 4, { 0, 11, 22, 33,   23, 55, 87, 66,   25, 54, 88, 77,   -1, 22, 100, 99 });
    int min1 = 0, min2 = -1;

    std::cout << local_min(matrix, 3, 3) << std::endl;
    std::cout << local_min(matrix, 3, 2) << std::endl;

    EXPECT_TRUE(local_min(matrix, 3, 3) == min1 || local_min(matrix, 3, 3) == min2);
}