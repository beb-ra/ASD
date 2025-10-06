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

TEST(TestTriangleMatrixLib, check_initializer_constructor_2) {
    int size = 6;
    int* mass = new int[size];
    for (int i = 0; i < size; i++) {
        mass[i] = i + 1;
    }
    TriangleMatrix<int> m(3, mass);

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

TEST(TestTriangleMatrixLib, correct_create_with_copy) {
    TriangleMatrix<int> object1(3);
    TriangleMatrix<int> object2(object1);

    EXPECT_EQ(static_cast <size_t>(0), object2.start_index());
    EXPECT_EQ(static_cast <size_t>(3), object2.get_n());
    EXPECT_EQ(object1, object2);
}

TEST(TestTriangleMatrixLib, correct_create_with_copy_2) {
    MVector<MVector<int>> object(2);
    object[0] = MVector<int>(3);
    object[1] = MVector<int>(3);
    TriangleMatrix<int> matrix(object);

    EXPECT_EQ(static_cast <size_t>(0), matrix.start_index());
    EXPECT_EQ(static_cast <size_t>(2), matrix.get_n());
}

TEST(TestTriangleMatrixLib, correct_create_with_copy_3) {
    TriangleMatrix<int> object1(3, { 1, 2, 3, 4, 5, 6 });
    TriangleMatrix<int> object2(object1);

    EXPECT_EQ(static_cast <size_t>(0), object2.start_index());
    EXPECT_EQ(static_cast <size_t>(3), object2.get_n());
    EXPECT_EQ(object1[0][0], object2[0][0]);
    EXPECT_EQ(object1, object2);
}

TEST(TestTriangleMatrixLib, correct_compare) {
    TriangleMatrix<int> matrix(3, { 1, 2, 3, 4, 5, 6 });
    TriangleMatrix<int> result(3, { 1, 2, 3, 4, 5, 6 });

    EXPECT_TRUE(matrix == result);
}

TEST(TestTriangleMatrixLib, correct_compare_2) {
    TriangleMatrix<int> matrix(2, { 1, 2, 3 });
    TriangleMatrix<int> result(3, { 1, 2, 3, 4, 5, 6 });

    EXPECT_TRUE(matrix != result);
}

TEST(TestTriangleMatrixLib, correct_compare_3) {
    TriangleMatrix<int> matrix(3, { 1, 2, 11, 4, 5, 6 });
    TriangleMatrix<int> result(3, { 1, 2, 3, 4, 5, 6 });

    EXPECT_TRUE(matrix != result);
}

TEST(TestTriangleMatrixLib, correct_compare_4) {
    TriangleMatrix<int> matrix(3, { 1, 2, 3, 4, 5, 6 });
    TriangleMatrix<int> result(3, { 1, 2, 3, 4, 5, 6 });

    EXPECT_FALSE(matrix != result);
}

TEST(TestTriangleMatrixLib, correct_compare_5) {
    TriangleMatrix<int> matrix(2, { 1, 2, 3 });
    TriangleMatrix<int> result(3, { 1, 2, 3, 4, 5, 6 });

    EXPECT_FALSE(matrix == result);
}

TEST(TestTriangleMatrixLib, correct_compare_6) {
    TriangleMatrix<int> matrix(3, { 1, 2, 11, 4, 5, 6 });
    TriangleMatrix<int> result(3, { 1, 2, 3, 4, 5, 6 });

    EXPECT_FALSE(matrix == result);
}

TEST(TestTriangleMatrixLib, correct_add) {
    TriangleMatrix<int> matrix1(3, { 1, 2, 3, 4, 5, 6 });
    TriangleMatrix<int> matrix2(3, { 1, 3, 5, 2, 4, 6 });
    TriangleMatrix<int> result(3, { 2, 5, 8, 6, 9, 12 });

    EXPECT_EQ(result, matrix1 + matrix2);
}

TEST(TestTriangleMatrixLib, correct_add_with_assignment) {
    TriangleMatrix<int> matrix1(3, { 1, 2, 3, 4, 5, 6 });
    TriangleMatrix<int> matrix2(3, { 1, 3, 5, 2, 4, 6 });
    TriangleMatrix<int> result(3, { 2, 5, 8, 6, 9, 12 });
    matrix1 += matrix2;

    EXPECT_EQ(result, matrix1);
}

TEST(TestTriangleMatrixLib, throw_uncorrect_add) {
    TriangleMatrix<int> matrix1(3, { 1, 2, 3, 4, 5, 6 });
    TriangleMatrix<int> matrix2(2, { 2, 1, 1 });

    ASSERT_THROW(matrix1 + matrix2, std::invalid_argument);
}

TEST(TestTriangleMatrixLib, throw_uncorrect_add_with_assignment) {
    TriangleMatrix<int> matrix1(3, { 1, 2, 3, 4, 5, 6 });
    TriangleMatrix<int> matrix2(2, { 2, 1, 1 });

    ASSERT_THROW(matrix1 += matrix2, std::invalid_argument);
}

TEST(TestTriangleMatrixLib, correct_sub) {
    TriangleMatrix<int> matrix1(3, { 1, 2, 3, 4, 5, 6 });
    TriangleMatrix<int> matrix2(3, { 1, 3, 5, 2, 4, 6 });
    TriangleMatrix<int> result(3, { 0, -1, -2, 2, 1, 0 });

    EXPECT_EQ(result, matrix1 - matrix2);
}

TEST(TestTriangleMatrixLib, correct_sub_with_assignment) {
    TriangleMatrix<int> matrix1(3, { 1, 2, 3, 4, 5, 6 });
    TriangleMatrix<int> matrix2(3, { 1, 3, 5, 2, 4, 6 });
    TriangleMatrix<int> result(3, { 0, -1, -2, 2, 1, 0 });
    matrix1 -= matrix2;

    EXPECT_EQ(result, matrix1);
}

TEST(TestTriangleMatrixLib, throw_uncorrect_sub) {
    TriangleMatrix<int> matrix1(3, { 1, 2, 3, 4, 5, 6 });
    TriangleMatrix<int> matrix2(2, { 2, 1, 1 });

    ASSERT_THROW(matrix1 - matrix2, std::invalid_argument);
}

TEST(TestTriangleMatrixLib, throw_uncorrect_sub_with_assignment) {
    TriangleMatrix<int> matrix1(3, { 1, 2, 3, 4, 5, 6 });
    TriangleMatrix<int> matrix2(2, { 2, 1, 1 });

    ASSERT_THROW(matrix1 -= matrix2, std::invalid_argument);
}

TEST(TestTriangleMatrixLib, correct_mult) {
    TriangleMatrix<int> matrix1(2, { 3, 2, 1 });
    TriangleMatrix<int> matrix2(2, { 1, 1, 1 });
    TriangleMatrix<int> result(2, { 3, 5, 1 });

    EXPECT_EQ(result, matrix1 * matrix2);
}

TEST(TestTriangleMatrixLib, throw_uncorrect_mult) {
    TriangleMatrix<int> matrix1(3, { 1, 2, 3, 4, 5, 6 });
    TriangleMatrix<int> matrix2(2, { 2, 1, 1 });

    ASSERT_THROW(matrix1 * matrix2, std::invalid_argument);
}

TEST(TestTriangleMatrixLib, correct_mult_2) {
    TriangleMatrix<int> matrix1(3, { 1, 2, 3, 4, 5, 6 });
    TriangleMatrix<int> matrix2(3, { 1, 0, 2, 1, 1, 2 });
    TriangleMatrix<int> result(3, { 1, 2, 10, 4, 14, 12 });

    EXPECT_EQ(result, matrix1 * matrix2);
}

TEST(TestTriangleMatrixLib, correct_mult_with_assignment) {
    TriangleMatrix<int> matrix1(2, { 3, 2, 1 });
    TriangleMatrix<int> matrix2(2, { 1, 1, 1 });
    TriangleMatrix<int> result(2, { 3, 5, 1 });
    matrix1 *= matrix2;

    EXPECT_EQ(result, matrix1);
}

TEST(TestTriangleMatrixLib, correct_mult_with_assignment_2) {
    TriangleMatrix<int> matrix1(3, { 1, 2, 3, 4, 5, 6 });
    TriangleMatrix<int> matrix2(3, { 1, 0, 2, 1, 1, 2 });
    TriangleMatrix<int> result(3, { 1, 2, 10, 4, 14, 12 });
    matrix1 *= matrix2;

    EXPECT_EQ(result, matrix1);
}

TEST(TestTriangleMatrixLib, throw_uncorrect_mult_with_assignment) {
    TriangleMatrix<int> matrix1(3, { 1, 2, 3, 4, 5, 6 });
    TriangleMatrix<int> matrix2(2, { 2, 1, 1 });

    ASSERT_THROW(matrix1 *= matrix2, std::invalid_argument);
}

TEST(TestTriangleMatrixLib, correct_mult_on_scalar) {
    int scalar = 2;
    TriangleMatrix<int> matrix1(3, { 1, 2, 3, 4, 5, 6 });
    TriangleMatrix<int> result(3, { 2, 4, 6, 8, 10, 12 });

    EXPECT_EQ(result, matrix1 * scalar);
    EXPECT_EQ(result, scalar * matrix1);
}

TEST(TestTriangleMatrixLib, correct_mult_on_scalar_with_assignment) {
    int scalar = 2;
    TriangleMatrix<int> matrix1(3, { 1, 2, 3, 4, 5, 6 });
    TriangleMatrix<int> result(3, { 2, 4, 6, 8, 10, 12 });
    matrix1 *= scalar;

    EXPECT_EQ(result, matrix1);
}

TEST(TestTriangleMatrixLib, correct_mult_on_vector) {
    TriangleMatrix<int> matrix1(3, { 1, 1, 1, 2, 1, 4 });
    MVector<int> vector(3, { 3, 1, 1 }, 0);
    MVector<int> result(3, { 5, 3, 4 }, 0);

    EXPECT_EQ(result, matrix1 * vector);
}

TEST(TestTriangleMatrixLib, correct_mult_on_vector_2) {
    TriangleMatrix<int> matrix1(3, { 1, 1, 1, 2, 1, 4 });
    MVector<int> vector(3, { 3, 1, 1 }, 0);
    MVector<int> result(3, { 3, 5, 8 }, 0);

    EXPECT_EQ(result, vector * matrix1);
}

TEST(TestTriangleMatrixLib, throw_uncorrect_mult_on_vector) {
    TriangleMatrix<int> matrix1(3, { 1, 1, 1, 2, 1, 4 });
    MVector<int> vector(4, { 3, 1, 1, 1 }, 0);

    ASSERT_THROW(matrix1 * vector, std::invalid_argument);
    ASSERT_THROW(vector * matrix1, std::invalid_argument);
}