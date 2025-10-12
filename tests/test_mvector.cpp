#include <gtest/gtest.h>
#include "../lib_mvector/mvector.h"


TEST(TestMVectorLib, try_create_object) {
    ASSERT_NO_THROW(MVector<int> object);
}

TEST(TestMVectorLib, try_create_object_2) {
    ASSERT_NO_THROW(MVector<int> object(10, 2));
}

TEST(TestMVectorLib, try_create_object3) {
    int size = 2;
    int* mass = new int[size];
    mass[0] = 1; mass[1] = 2;
    size_t index = 0;

    ASSERT_NO_THROW(MVector<int> object(size, mass, index));
}

TEST(TestMVectorLib, try_create_object_4) {
    size_t size = 3, index = 0;

    ASSERT_NO_THROW(MVector<int> object(size, { 1, 2, 3 }, index));
}

TEST(TestMVectorLib, try_create_object_with_copy) {
    size_t size = 3, index = 0;
    MVector<int> object1(size, { 1, 2, 3 }, index);

    ASSERT_NO_THROW(MVector<int> object2(object1));
}

TEST(TestMVectorLib, correct_create_object) {
    MVector<int> object;

    EXPECT_EQ(static_cast <size_t>(0), object.start_index());
    EXPECT_EQ(static_cast <size_t>(0), object.size());
}

TEST(TestMVectorLib, correct_create_object_2) {
    size_t start_index = 2, size = 10;

    MVector<int> object(size, start_index);

    EXPECT_EQ(start_index, object.start_index());
    EXPECT_EQ(size, object.size());
}

TEST(TestMVectorLib, correct_create_object3) {
    int size = 2;
    int* mass = new int[size];
    mass[0] = 1; mass[1] = 2;
    size_t start_index = 0;

    MVector<int> object(size, mass, start_index);
    
    EXPECT_EQ(start_index, object.start_index());
    EXPECT_EQ(size, object.size());
}

TEST(TestMVectorLib, correct_create_object_4) {
    size_t size = 3, start_index = 1;

    MVector<int> object(size, { 1, 2, 3 }, start_index);

    EXPECT_EQ(start_index, object.start_index());
    EXPECT_EQ(size, object.size());
}

TEST(TestMVectorLib, correct_create_object_with_copy) {
    size_t size = 3, start_index = 2;
    MVector<int> object1(size, { 1, 2, 3 }, start_index);

    MVector<int> object2(object1);

    EXPECT_EQ(start_index, object2.start_index());
    EXPECT_EQ(size, object2.size());
}

TEST(TestMVectorLib, try_compare) {
    bool actual_result = true;

    MVector<int> object1(3, { 1, 2, 3 }, 0);
    MVector<int> object2(object1);

    try {
        object1 == object2;
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what();
        actual_result = false;
    }

    EXPECT_TRUE(actual_result);
}

TEST(TestMVectorLib, try_compare_2) {
    bool actual_result = true;

    MVector<int> object1(3, { 1, 2, 3 }, 0);
    MVector<int> object2(object1);

    try {
        object1 != object2;
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what();
        actual_result = false;
    }

    EXPECT_TRUE(actual_result);
}

TEST(TestMVectorLib, correct_compare) {
    MVector<int> object1(3, { 1, 2, 3 }, 0);
    MVector<int> object2(3, { 1, 2, 3 }, 0);

    EXPECT_TRUE(object1 == object2);
}

TEST(TestMVectorLib, correct_compare2) {
    MVector<int> object1(3, { 1, 2, 3 }, 0);
    MVector<int> object2(object1);

    EXPECT_TRUE(object1 == object2);
}

TEST(TestMVectorLib, correct_compare3) {
    MVector<int> object1(3, { 1, 2, 3 }, 2);
    MVector<int> object2(3, { 1, 2, 3 }, 0);

    EXPECT_FALSE(object1 == object2);
}

TEST(TestMVectorLib, correct_compare4) {
    MVector<int> object1(2, { 1, 2 }, 0);
    MVector<int> object2(3, { 1, 2, 3 }, 0);

    EXPECT_FALSE(object1 == object2);
}

TEST(TestMVectorLib, correct_compare5) {
    MVector<int> object1(3, { 1, 2, 3 }, 0);
    MVector<int> object2(3, { 1, 2, 3 }, 0);

    EXPECT_FALSE(object1 != object2);
}

TEST(TestMVectorLib, correct_compare6) {
    MVector<int> object1(3, { 1, 2, 3 }, 0);
    MVector<int> object2(object1);

    EXPECT_FALSE(object1 != object2);
}

TEST(TestMVectorLib, correct_compare7) {
    MVector<int> object1(3, { 1, 2, 3 }, 2);
    MVector<int> object2(3, { 1, 2, 3 }, 0);

    EXPECT_TRUE(object1 != object2);
}

TEST(TestMVectorLib, correct_compare8) {
    MVector<int> object1(2, { 1, 2 }, 0);
    MVector<int> object2(3, { 1, 2, 3 }, 0);

    EXPECT_TRUE(object1 != object2);
}

TEST(TestMVectorLib, try_assignment) {
    bool actual_result = true;

    MVector<int> object1(3, { 1, 2, 3 }, 0);
    MVector<int> object2;

    try {
        object2 = object1;
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what();
        actual_result = false;
    }

    EXPECT_TRUE(actual_result);
}

TEST(TestMVectorLib, correct_assignment) {
    MVector<int> object1(3, { 1, 2, 3 }, 0);
    MVector<int> object2;

    object2 = object1;

    EXPECT_TRUE(object1 == object2);
}

TEST(TestMVectorLib, try_mult) {
    bool actual_result = true;

    MVector<int> object(3, { 1, 2, 3 }, 0);
    int value = 5;

    try {
        object * value;
        value * object;
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what();
        actual_result = false;
    }

    EXPECT_TRUE(actual_result);
}

TEST(TestMVectorLib, correct_mult) {
    size_t size = 3, start_index = 0;
    MVector<int> object(size, { 1, -2, 3 }, start_index);
    int value = 3;

    MVector<int> object2;
    object2 = object * value;

    MVector<int> result(size, { 3, -6, 9 }, start_index);

    EXPECT_EQ(result, object2);
}

TEST(TestMVectorLib, correct_mult_2) {
    size_t size = 3, start_index = 0;
    MVector<int> object(size, { -1, 2, 3 }, start_index);
    int value = 3;

    MVector<int> object2;
    object2 = value * object;

    MVector<int> result(size, { -3, 6, 9 }, start_index);

    EXPECT_EQ(result, object2);
}

TEST(TestMVectorLib, correct_mult_3) {
    size_t size = 3, start_index = 0;
    MVector<int> object1(size, { 2, 2, 2 }, start_index);
    int value = 3;

    MVector<int> object2(size, { 3, 3, 3 }, start_index);

    EXPECT_EQ(18, object1 * object2);
}

TEST(TestMVectorLib, correct_mult_with_different_start_index) {
    MVector<int> object1(2, { 2, -1 }, 1);
    MVector<int> object2(1, { 3 }, 2);
    int result = -3;

    EXPECT_EQ(result, object1 * object2);
    EXPECT_EQ(result, object2 * object1);
}

TEST(TestMVectorLib, throw_uncorrect_mult) {
    size_t start_index = 0;
    MVector<int> object1(2, { 2, 2}, start_index);

    MVector<int> object2(3, { 3, 3, 3 }, start_index);

    ASSERT_THROW(object1 * object2, std::invalid_argument);
}

TEST(TestMVectorLib, throw_uncorrect_mult_2) {
    size_t start_index = 0;
    MVector<int> object1;

    MVector<int> object2(3, { 3, 3, 3 }, start_index);

    ASSERT_THROW(object1 * object2, std::invalid_argument);
}

TEST(TestMVectorLib, throw_uncorrect_mult_3) {
    size_t start_index = 0;
    MVector<int> object;
    int value = 5;

    ASSERT_THROW(object * value, std::invalid_argument);
}

TEST(TestMVectorLib, throw_uncorrect_mult_4) {
    size_t start_index = 0;
    MVector<int> object;
    int value = 5;

    ASSERT_THROW(value * object, std::invalid_argument);
}

TEST(TestMVectorLib, correct_add) {
    size_t size = 3, start_index = 0;
    MVector<int> object1(size, { 1, 2, 3 }, start_index);
    MVector<int> object2(size, { 2, 3, -3 }, start_index);
    MVector<int> result(size, { 3, 5, 0 }, start_index);

    EXPECT_EQ(result, object1 + object2);
}

TEST(TestMVectorLib, correct_add_with_different_start_index) {
    MVector<int> object1(2, { 2, 3 }, 1);
    MVector<int> object2(1, { -1 }, 2);
    MVector<int> result(2, { 2, 2 }, 1);

    EXPECT_EQ(result, object1 + object2);
    object1 += object2;
    EXPECT_EQ(result, object1);
}

TEST(TestMVectorLib, correct_add_with_different_start_index_2) {
    MVector<int> object1(2, { 2, 3 }, 1);
    MVector<int> object2(1, { -1 }, 2);
    MVector<int> result(2, { 2, 2 }, 1);

    EXPECT_EQ(result, object2 + object1);
    object2 += object1;
    EXPECT_EQ(result, object2);
}

TEST(TestMVectorLib, correct_sub) {
    size_t size = 3, start_index = 0;
    MVector<int> object1(size, { 1, 2, 3 }, start_index);
    MVector<int> object2(size, { 2, 3, -3 }, start_index);
    MVector<int> result(size, { -1, -1, 6 }, start_index);

    EXPECT_EQ(result, object1 - object2);
}

TEST(TestMVectorLib, correct_sub_with_different_start_index) {
    MVector<int> object1(2, { 2, 3 }, 1);
    MVector<int> object2(1, { -1 }, 2);
    MVector<int> result(2, { 2, 4 }, 1);

    EXPECT_EQ(result, object1 - object2);
    object1 -= object2;
    EXPECT_EQ(result, object1);
}

TEST(TestMVectorLib, correct_sub_with_different_start_index_2) {
    MVector<int> object1(2, { 2, 3 }, 1);
    MVector<int> object2(1, { -1 }, 2);
    MVector<int> result(2, { -2, -4 }, 1);

    EXPECT_EQ(result, object2 - object1);
    object2 -= object1;
    EXPECT_EQ(result, object2);
}

TEST(TestMVectorLib, throw_uncorrect_add) {
    size_t start_index = 0;
    MVector<int> object1(2, { 2, 2 }, start_index);

    MVector<int> object2(3, { 3, 3, 3 }, start_index);

    ASSERT_THROW(object1 + object2, std::invalid_argument);
}

TEST(TestMVectorLib, throw_uncorrect_add_2) {
    size_t start_index = 0;
    MVector<int> object1;

    MVector<int> object2(3, { 3, 3, 3 }, start_index);

    ASSERT_THROW(object1 + object2, std::invalid_argument);
}

TEST(TestMVectorLib, throw_uncorrect_sub) {
    size_t start_index = 0;
    MVector<int> object1(2, { 2, 2 }, start_index);

    MVector<int> object2(3, { 3, 3, 3 }, start_index);

    ASSERT_THROW(object1 - object2, std::invalid_argument);
}

TEST(TestMVectorLib, throw_uncorrect_sub_2) {
    size_t start_index = 0;
    MVector<int> object1;

    MVector<int> object2(3, { 3, 3, 3 }, start_index);

    ASSERT_THROW(object1 - object2, std::invalid_argument);
}

TEST(TestMVectorLib, correct_add_with_assignment) {
    size_t size = 3, start_index = 0;
    MVector<int> object1(size, { 1, 2, 3 }, start_index);
    MVector<int> object2(size, { 2, 3, -3 }, start_index);
    MVector<int> result(size, { 3, 5, 0 }, start_index);
    object1 += object2;

    EXPECT_EQ(result, object1);
}

TEST(TestMVectorLib, correct_sub_with_assignment) {
    size_t size = 3, start_index = 0;
    MVector<int> object1(size, { 1, 2, 3 }, start_index);
    MVector<int> object2(size, { 2, 3, -3 }, start_index);
    MVector<int> result(size, { -1, -1, 6 }, start_index);
    object1 -= object2;

    EXPECT_EQ(result, object1);
}

TEST(TestMVectorLib, correct_mult_with_assignment) {
    size_t size = 3, start_index = 0;
    MVector<int> object1(size, { 1, 2, 3 }, start_index);
    int value = 3;

    MVector<int> result(size, { 3, 6, 9 }, start_index);
    object1 *= value;

    EXPECT_EQ(result, object1);
}

TEST(TestMVectorLib, throw_uncorrect_add_with_assignment) {
    size_t size = 3, start_index = 0;
    MVector<int> object1;
    MVector<int> object2(size, { 2, 3, -3 }, start_index);

    ASSERT_THROW(object1 += object2, std::invalid_argument);
}

TEST(TestMVectorLib, throw_uncorrect_add_with_assignment_2) {
    size_t size = 3, start_index = 0;
    MVector<int> object1(size - 1, { 2, 3 }, start_index);
    MVector<int> object2(size, { 2, 3, -3 }, start_index);

    ASSERT_THROW(object1 += object2, std::invalid_argument);
}

TEST(TestMVectorLib, throw_uncorrect_sub_with_assignment) {
    size_t size = 3, start_index = 0;
    MVector<int> object1;
    MVector<int> object2(size, { 2, 3, -3 }, start_index);

    ASSERT_THROW(object1 -= object2, std::invalid_argument);
}

TEST(TestMVectorLib, throw_uncorrect_sub_with_assignment_2) {
    size_t size = 3, start_index = 0;
    MVector<int> object1(size - 1, { 2, 3 }, start_index);
    MVector<int> object2(size, { 2, 3, -3 }, start_index);

    ASSERT_THROW(object1 -= object2, std::invalid_argument);
}

TEST(TestMVectorLib, check_index_conversion_operator) {
    MVector<int> vec(4, { 1, 2, 3, 4 }, 0);
    vec[2] = 6;
    EXPECT_EQ(6, vec[2]);
    EXPECT_EQ(2, vec[1]);
    EXPECT_EQ(4, vec[3]);
}