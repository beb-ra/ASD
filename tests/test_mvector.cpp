#include <gtest/gtest.h>
#include "../lib_mvector/mvector.h"

TEST(TestMVectorLib, try_create_object) {
    bool expected_result = true;
    bool actual_result = true;

    int size = 2;
    int* mass = new int[size];
    mass[0] = 1; mass[1] = 2;
    size_t index = 0;

    try {
        MVector<int> object(size, mass, index);
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what();
        actual_result = false;
    }

    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestMVectorLib, try_create_object_2) {
    bool expected_result = true;
    bool actual_result = true;

    size_t size = 3, index = 0;

    try {
        MVector<int> object(size, { 1, 2, 3 }, index);
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what();
        actual_result = false;
    }

    EXPECT_EQ(expected_result, actual_result);
}