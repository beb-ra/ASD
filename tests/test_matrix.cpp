#include <gtest/gtest.h>
#include <iostream>
#include "../lib_matrix/matrix.h"

TEST(TestMatrixLib, try_create_object) {
    ASSERT_NO_THROW(Matrix<int> object);
}

TEST(TestMatrixLib, try_create_object_2) {
    ASSERT_NO_THROW(Matrix<int> object(2, 2));
}

TEST(TestMatrixLib, try_create_object_3) {
    ASSERT_NO_THROW(Matrix<int> object(2, 2, {1, 2, 3, 4}));
}

TEST(TestMatrixLib, try_create_object_4) {
    int size = 4;
    int* mass = new int[size];

    ASSERT_NO_THROW(Matrix<int> object(2, 2, mass));
}

TEST(TestMatrixLib, try_create_object_with_copy) {
    Matrix<int> object1(3, 3);
    ASSERT_NO_THROW(Matrix<int> object2(object1));
}

TEST(TestMatrixLib, try_create_object_with_copy_2) {
    MVector<MVector<int>> object(2);
    object[0] = MVector<int>(3);
    object[1] = MVector<int>(3);

    ASSERT_NO_THROW(Matrix<int> matrix(object));
}

TEST(TestMatrixLib, correct_create_object) {
    Matrix<int> object;

    EXPECT_EQ(static_cast <size_t>(0), object.start_index());
    EXPECT_EQ(static_cast <size_t>(2), object.get_n());
    EXPECT_EQ(static_cast <size_t>(2), object.get_m());
}

TEST(TestMatrixLib, correct_create_object_2) {
    Matrix<int> object(3, 3);

    EXPECT_EQ(static_cast <size_t>(0), object.start_index());
    EXPECT_EQ(static_cast <size_t>(3), object.get_n());
    EXPECT_EQ(static_cast <size_t>(3), object.get_m());
}

TEST(TestMatrixLib, check_initializer_constructor) {
    Matrix<int> m(2, 3, { 1, 2, 3, 4, 5, 6 });

    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][1], 2);
    EXPECT_EQ(m[0][2], 3);
    EXPECT_EQ(m[1][0], 4);
    EXPECT_EQ(m[1][1], 5);
    EXPECT_EQ(m[1][2], 6);
}

TEST(TestMatrixLib, check_initializer_constructor_2) {
    int size = 6;
    int* mass = new int[size];
    for (int i = 0; i < size; i++) {
        mass[i] = i + 1;
    }
    Matrix<int> m(2, 3, mass);

    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][1], 2);
    EXPECT_EQ(m[0][2], 3);
    EXPECT_EQ(m[1][0], 4);
    EXPECT_EQ(m[1][1], 5);
    EXPECT_EQ(m[1][2], 6);
}

TEST(TestMatrixLib, correct_create_with_copy) {
    Matrix<int> object1(3, 3);
    Matrix<int> object2(object1);

    EXPECT_EQ(static_cast <size_t>(0), object2.start_index());
    EXPECT_EQ(static_cast <size_t>(3), object2.get_n());
    EXPECT_EQ(static_cast <size_t>(3), object2.get_m());
    EXPECT_EQ(object1, object2);
}

TEST(TestMatrixLib, correct_create_with_copy_2) {
    MVector<MVector<int>> object(2);
    object[0] = MVector<int>(3);
    object[1] = MVector<int>(3);
    Matrix<int> matrix(object);

    EXPECT_EQ(static_cast <size_t>(0), matrix.start_index());
    EXPECT_EQ(static_cast <size_t>(2), matrix.get_n());
    EXPECT_EQ(static_cast <size_t>(3), matrix.get_m());
}

TEST(TestMatrixLib, correct_create_with_copy_3) {
    Matrix<int> object1(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    Matrix<int> object2(object1);

    EXPECT_EQ(static_cast <size_t>(0), object2.start_index());
    EXPECT_EQ(static_cast <size_t>(3), object2.get_n());
    EXPECT_EQ(static_cast <size_t>(3), object2.get_m());
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_EQ(object1[i][j], object2[i][j]);
        }
    }
    EXPECT_TRUE(object1 == object2);
}

TEST(TestMatrixLib, correct_compare) {
    Matrix<int> matrix(3, 2, { 1, 2, 3, 4, 5, 6 });
    Matrix<int> result(3, 2, { 1, 2, 3, 4, 5, 6 });

    EXPECT_TRUE(matrix == result);
}

TEST(TestMatrixLib, correct_compare_2) {
    Matrix<int> matrix(3, 3, { 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    Matrix<int> result(3, 2, { 1, 2, 3, 4, 5, 6 });

    EXPECT_TRUE(matrix != result);
}

TEST(TestMatrixLib, correct_compare_3) {
    Matrix<int> matrix(3, 2, { 1, 2, 11, 4, 5, 6 });
    Matrix<int> result(3, 2, { 1, 2, 3, 4, 5, 6 });

    EXPECT_TRUE(matrix != result);
}

TEST(TestMatrixLib, correct_compare_4) {
    Matrix<int> matrix(3, 2, { 1, 2, 3, 4, 5, 6 });
    Matrix<int> result(3, 2, { 1, 2, 3, 4, 5, 6 });

    EXPECT_FALSE(matrix != result);
}

TEST(TestMatrixLib, correct_compare_5) {
    Matrix<int> matrix(3, 3, { 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    Matrix<int> result(3, 2, { 1, 2, 3, 4, 5, 6 });

    EXPECT_FALSE(matrix == result);
}

TEST(TestMatrixLib, correct_compare_6) {
    Matrix<int> matrix(3, 2, { 1, 2, 11, 4, 5, 6 });
    Matrix<int> result(3, 2, { 1, 2, 3, 4, 5, 6 });

    EXPECT_FALSE(matrix == result);
}

TEST(TestMatrixLib, correct_transpose) {
    Matrix<int> matrix(3, 2, { 1, 2, 3, 4, 5, 6 });
    Matrix<int> result(2, 3, { 1, 3, 5, 2, 4, 6 });
    matrix = matrix.transpose();

    EXPECT_EQ(matrix, result);
}

TEST(TestMatrixLib, correct_add) {
    Matrix<int> matrix1(3, 2, { 1, 2, 3, 4, 5, 6 });
    Matrix<int> matrix2(3, 2, { 1, 3, 5, 2, 4, 6 });
    Matrix<int> result(3, 2, { 2, 5, 8, 6, 9, 12 });

    EXPECT_EQ(result, matrix1 + matrix2);
}

TEST(TestMatrixLib, correct_add_with_assignment) {
    Matrix<int> matrix1(3, 2, { 1, 2, 3, 4, 5, 6 });
    Matrix<int> matrix2(3, 2, { 1, 3, 5, 2, 4, 6 });
    Matrix<int> result(3, 2, { 2, 5, 8, 6, 9, 12 });
    matrix1 += matrix2;

    EXPECT_EQ(result, matrix1);
}

TEST(TestMatrixLib, correct_sub) {
    Matrix<int> matrix1(3, 2, { 1, 2, 3, 4, 5, 6 });
    Matrix<int> matrix2(3, 2, { 1, 3, 5, 2, 4, 6 });
    Matrix<int> result(3, 2, { 0, -1, -2, 2, 1, 0 });

    EXPECT_EQ(result, matrix1 - matrix2);
}

TEST(TestMatrixLib, correct_sub_with_assignment) {
    Matrix<int> matrix1(3, 2, { 1, 2, 3, 4, 5, 6 });
    Matrix<int> matrix2(3, 2, { 1, 3, 5, 2, 4, 6 });
    Matrix<int> result(3, 2, { 0, -1, -2, 2, 1, 0 });
    matrix1 -= matrix2;

    EXPECT_EQ(result, matrix1);
}

TEST(TestMatrixLib, throw_uncorrect_add) {
    Matrix<int> matrix1(3, 2, { 1, 2, 3, 4, 5, 6 });
    Matrix<int> matrix2(3, 3, { 1, 3, 5, 2, 4, 6, 7, 8, 9 });

    ASSERT_THROW(matrix1 + matrix2, std::invalid_argument);
    ASSERT_THROW(matrix2 + matrix1, std::invalid_argument);
}

TEST(TestMatrixLib, throw_uncorrect_add_with_assignment) {
    Matrix<int> matrix1(2, 3, { 1, 2, 3, 4, 5, 6 });
    Matrix<int> matrix2(3, 3, { 1, 3, 5, 2, 4, 6, 7, 8, 9 });

    ASSERT_THROW(matrix1 += matrix2, std::invalid_argument);
    ASSERT_THROW(matrix2 += matrix1, std::invalid_argument);
}

TEST(TestMatrixLib, throw_uncorrect_sub) {
    Matrix<int> matrix1(3, 2, { 1, 2, 3, 4, 5, 6 });
    Matrix<int> matrix2(3, 3, { 1, 3, 5, 2, 4, 6, 7, 8, 9 });

    ASSERT_THROW(matrix1 - matrix2, std::invalid_argument);
    ASSERT_THROW(matrix2 - matrix1, std::invalid_argument);
}

TEST(TestMatrixLib, throw_uncorrect_sub_with_assignment) {
    Matrix<int> matrix1(2, 3, { 1, 2, 3, 4, 5, 6 });
    Matrix<int> matrix2(3, 3, { 1, 3, 5, 2, 4, 6, 7, 8, 9 });

    ASSERT_THROW(matrix1 -= matrix2, std::invalid_argument);
    ASSERT_THROW(matrix2 -= matrix1, std::invalid_argument);
}

TEST(TestMatrixLib, correct_mult) {
    Matrix<int> matrix1(2, 2, { 1, 2, 3, 4 });
    Matrix<int> matrix2(2, 2, { 2, 0, 0, 1 });
    Matrix<int> result(2, 2, { 2, 2, 6, 4 });

    EXPECT_EQ(result, matrix1 * matrix2);
}

TEST(TestMatrixLib, correct_mult_on_scalar) {
    int scalar = 2;
    Matrix<int> matrix1(3, 2, { 1, 2, 3, 4, 5, 6 });
    Matrix<int> result(3, 2, { 2, 4, 6, 8, 10, 12 });

    EXPECT_EQ(result, matrix1 * scalar);
    EXPECT_EQ(result, scalar * matrix1);
}

TEST(TestMatrixLib, correct_mult_on_scalar_with_assignment) {
    int scalar = 2;
    Matrix<int> matrix1(3, 2, { 1, 2, 3, 4, 5, 6 });
    Matrix<int> result(3, 2, { 2, 4, 6, 8, 10, 12 });
    matrix1 *= scalar;

    EXPECT_EQ(result, matrix1);
}

TEST(TestMatrixLib, throw_uncorrect_mult) {
    Matrix<int> matrix1(2, 3, { 1, 2, 3, 4, 5, 6 });
    Matrix<int> matrix2(2, 2, { 2, 0, 0, 1 });

    ASSERT_THROW(matrix1 * matrix2, std::invalid_argument);
}

TEST(TestMatrixLib, correct_mult_2) {
    Matrix<int> matrix1(3, 2, { 1, 0, 0, 1, 0, 1 });
    Matrix<int> matrix2(2, 3, { 1, 0, 0, 0, 1, 0 });
    Matrix<int> result(3, 3, { 1, 0, 0, 0, 1, 0, 0, 1, 0 });

    EXPECT_EQ(result, matrix1 * matrix2);
}

TEST(TestMatrixLib, correct_mult_on_vector) {
    Matrix<int> matrix1(3, 2, { 1, 0, 0, 1, 0, 1 });
    MVector<int> vector(2, { 1, 0 }, 0);
    MVector<int> result(3, { 1, 0, 0 }, 0);

    EXPECT_EQ(result, matrix1 * vector);
}

TEST(TestMatrixLib, correct_mult_on_vector_2) {
    Matrix<int> matrix1(3, 2, { 1, 0, 0, 1, 0, 1 });
    MVector<int> vector(3, { 1, 0, 0 }, 0);
    MVector<int> result(2, { 1, 0 }, 0);

    EXPECT_EQ(result, vector * matrix1);
}

TEST(TestMatrixLib, throw_uncorrect_mult_on_vector) {
    Matrix<int> matrix1(3, 2, { 1, 0, 0, 1, 0, 1 });
    MVector<int> vector(4, { 1, 0, 0, 0 }, 0);

    ASSERT_THROW(matrix1 * vector, std::invalid_argument);
    ASSERT_THROW(vector * matrix1, std::invalid_argument);
}

TEST(TestMatrixLib, check_at) {
    Matrix<int> m(2, 3, { 1, 2, 3, 4, 5, 6 });

    EXPECT_EQ(m.at(0, 0), 1);
    EXPECT_EQ(m.at(0, 1), 2);
    EXPECT_EQ(m.at(0, 2), 3);
    EXPECT_EQ(m.at(1, 0), 4);
    EXPECT_EQ(m.at(1, 1), 5);
    EXPECT_EQ(m.at(1, 2), 6);
    ASSERT_THROW(m.at(0, -1), std::invalid_argument);
    ASSERT_THROW(m.at(3, 2), std::invalid_argument);
    ASSERT_THROW(m.at(5, 5), std::invalid_argument);
}