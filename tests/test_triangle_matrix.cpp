#include <gtest/gtest.h>
#include <iostream>
#include "../lib_triangle_matrix/triangle_matrix.h"


TEST(TestTriangleMatrixLib, try_create_object) {
    ASSERT_NO_THROW(TriangleMatrix<int> object);
}

TEST(TestTriangleMatrixLib, try_create_object_2) {
    ASSERT_NO_THROW(TriangleMatrix<int> object(3));
}

TEST(TestTriangleMatrixLib, try_create_object_3) {
    ASSERT_NO_THROW(TriangleMatrix<int> object(2, { 1, 2, 3 }));
    ASSERT_NO_THROW(TriangleMatrix<int> object(3, { 1, 2, 3, 4, 5, 6 }));
}

TEST(TestTriangleMatrixLib, try_create_object_5) {
    ASSERT_NO_THROW(TriangleMatrix<int> object(3, { 1, 2, 3, 4, 5, 6 }));
    ASSERT_NO_THROW(TriangleMatrix<int> object(4, { 1, 2 }));
}

TEST(TestTriangleMatrixLib, try_create_object_4) {
    int size = 3;
    int* mass = new int[size];

    ASSERT_NO_THROW(TriangleMatrix<int> object(2, mass));
}

TEST(TestTriangleMatrixLib, try_create_object_with_copy) {
    TriangleMatrix<int> object1(3);
    ASSERT_NO_THROW(TriangleMatrix<int> object2(object1));
}

TEST(TestTriangleMatrixLib, try_create_object_with_copy_2) {
    MVector<MVector<int>> object(2);
    object[0] = MVector<int>(3);
    object[1] = MVector<int>(3);

    ASSERT_NO_THROW(TriangleMatrix<int> matrix(object));
}

TEST(TestTriangleMatrixLib, correct_create_object) {
    TriangleMatrix<int> object;

    EXPECT_EQ(static_cast <size_t>(0), object.start_index());
    EXPECT_EQ(static_cast <size_t>(2), object.get_n());
}

TEST(TestTriangleMatrixLib, correct_create_object_2) {
    TriangleMatrix<int> object(3);

    EXPECT_EQ(static_cast <size_t>(0), object.start_index());
    EXPECT_EQ(static_cast <size_t>(3), object.get_n());
}

TEST(TestTriangleMatrixLib, check_initializer_constructor) {
    TriangleMatrix<int> m(3, { 1, 2, 3, 4, 5, 6 });


    EXPECT_EQ(static_cast <size_t>(0), m.start_index());
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][1], 2);
    EXPECT_EQ(m[0][2], 3);
    EXPECT_EQ(m[1][0], 0);
    EXPECT_EQ(m[1][1], 4);
    EXPECT_EQ(m[1][2], 5);
    EXPECT_EQ(m[2][0], 0);
    EXPECT_EQ(m[2][1], 0);
    EXPECT_EQ(m[2][2], 6);
}