#include <gtest/gtest.h>
#include <iostream>
#include "../lib_algorithms/algorithms.h"
#include "../lib_circle/circle.h"
#include "../lib_sphere/sphere.h"

TEST(TestAlgorithmsLib, circle_not_intersect1) {
    Circle first(0, 0, 2);
    Circle second(5, 0, 2);

    EXPECT_EQ(figures_comparison(first, second), LocationTypes::not_intersect);
}

TEST(TestAlgorithmsLib, circle_not_intersect_small_size) {
    Circle first(0, 0, 1.0);
    Circle second(2, 0, 0.1);

    EXPECT_EQ(figures_comparison(first, second), LocationTypes::not_intersect);
}

TEST(TestAlgorithmsLib, circle_not_intersect3) {
    Circle first(0, 0, 1);
    Circle second(3, 4, 1);

    EXPECT_EQ(figures_comparison(first, second), LocationTypes::not_intersect);
}

TEST(TestAlgorithmsLib, sphere_not_intersect1) {
    Sphere first(0, 0, 0, 2.0);
    Sphere second(6, 0, 0, 2.0);

    EXPECT_EQ(figures_comparison(first, second), LocationTypes::not_intersect);
}

TEST(TestAlgorithmsLib, sphere_not_intersect2) {
    Sphere first(0, 0, 0, 1.0);
    Sphere second(3, 4, 5, 1.0);

    EXPECT_EQ(figures_comparison(first, second), LocationTypes::not_intersect);
}

TEST(TestAlgorithmsLib, circle_touch1) {
    Circle first(0, 0, 2);
    Circle second(4, 0, 2);

    EXPECT_EQ(figures_comparison(first, second), LocationTypes::touch);
}

TEST(TestAlgorithmsLib, circle_touch2) {
    Circle first(0, 0, 5);
    Circle second(3, 0, 2);

    EXPECT_EQ(figures_comparison(first, second), LocationTypes::touch);
}

TEST(TestAlgorithmsLib, circle_touch3) {
    Circle first(0, 0, 5);
    Circle second(0, 0, 5);

    EXPECT_EQ(figures_comparison(first, second), LocationTypes::touch);
}

TEST(TestAlgorithmsLib, sphere_touch1) {
    Sphere first(0, 0, 0, 2.0);
    Sphere second(4, 0, 0, 2.0);

    EXPECT_EQ(figures_comparison(first, second), LocationTypes::touch);
}

TEST(TestAlgorithmsLib, sphere_touch2) {
    Sphere first(0, 0, 0, 5.0);
    Sphere second(3, 0, 0, 2.0);

    EXPECT_EQ(figures_comparison(first, second), LocationTypes::touch);
}

TEST(TestAlgorithmsLib, circle_inside1) {
    Circle first(0, 0, 5);
    Circle second(1, 0, 1);

    EXPECT_EQ(figures_comparison(first, second), LocationTypes::inside);
}

TEST(TestAlgorithmsLib, circle_inside2) {
    Circle first(0, 0, 4);
    Circle second(0, 0, 2);

    EXPECT_EQ(figures_comparison(first, second), LocationTypes::inside);
}

TEST(TestAlgorithmsLib, circle_inside3) {
    Circle first(0, 0, 3);
    Circle second(2, 0, 0.5);

    EXPECT_EQ(figures_comparison(first, second), LocationTypes::inside);
}

TEST(TestAlgorithmsLib, sphere_inside1) {
    Sphere first(0, 0, 0, 5.0);
    Sphere second(1, 1, 1, 1.0);

    EXPECT_EQ(figures_comparison(first, second), LocationTypes::inside);
}

TEST(TestAlgorithmsLib, sphere_inside2) {
    Sphere first(0, 0, 0, 4.0);
    Sphere second(0, 0, 0, 2.0);

    EXPECT_EQ(figures_comparison(first, second), LocationTypes::inside);
}

TEST(TestAlgorithmsLib, circle_intersect1) {
    Circle first(0, 0, 3);
    Circle second(4, 0, 2);

    EXPECT_EQ(figures_comparison(first, second), LocationTypes::intersect);
}

TEST(TestAlgorithmsLib, circle_intersect2) {
    Circle first(0, 0, 3);
    Circle second(1, 0, 3);

    EXPECT_EQ(figures_comparison(first, second), LocationTypes::intersect);
}

TEST(TestAlgorithmsLib, circle_intersect3) {
    Circle first(0, 0, 2);
    Circle second(2, 2, 2);

    EXPECT_EQ(figures_comparison(first, second), LocationTypes::intersect);
}

TEST(TestAlgorithmsLib, sphere_intersect1) {
    Sphere first(0, 0, 0, 3.0);
    Sphere second(4, 0, 0, 2.0);

    EXPECT_EQ(figures_comparison(first, second), LocationTypes::intersect);
}

TEST(TestAlgorithmsLib, sphere_intersect2) {
    Sphere first(0, 0, 0, 3.0);
    Sphere second(2, 2, 2, 2.0);

    EXPECT_EQ(figures_comparison(first, second), LocationTypes::intersect);
}

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

TEST(TestAlgorithmsLib, local_min_test1) {
    Matrix<int> matrix(3, 3, { 3, 1, 2, 5, 8, 4, 7, 6, 9 });
    int min1 = 1, min2 = 6;

    EXPECT_TRUE(local_min(matrix, 0, 0) == min1 || local_min(matrix, 0, 0) == min2);
}

TEST(TestAlgorithmsLib, local_min_test2) {
    Matrix<int> matrix(3, 3, { 3, 1, 2, 5, 8, 4, 7, 6, 9 });
    int min1 = 1, min2 = 6;

    EXPECT_TRUE(local_min(matrix, 2, 2) == min1 || local_min(matrix, 2, 2) == min2);
}

TEST(TestAlgorithmsLib, local_min_test3) {
    Matrix<int> matrix(3, 3, { 3, 1, 2, 5, 8, 4, 7, 6, 9 });
    int min1 = 1, min2 = 6;

    EXPECT_TRUE(local_min(matrix, 2, 0) == min1 || local_min(matrix, 2, 0) == min2);
}

TEST(TestAlgorithmsLib, local_min_test4) {
    Matrix<int> matrix(3, 3, { 3, 1, 2, 5, 8, 4, 7, 6, 9 });
    int min1 = 1, min2 = 6;

    EXPECT_TRUE(local_min(matrix, 0, 1) == min1 && local_min(matrix, 2, 1) == min2);
}

TEST(TestAlgorithmsLib, local_min_test5) {
    Matrix<int> matrix(4, 4, { 1, 3, 0, 2,   -2, 6, 1, 11,   9, -3, 4, 8,   -1, -4, 5, 7 });
    int min1 = 0, min2 = -2, min3 = -4;

    EXPECT_TRUE(local_min(matrix, 0, 0) == min1 || local_min(matrix, 0, 0) == min2 ||
        local_min(matrix, 0, 0) == min3);
}

TEST(TestAlgorithmsLib, local_min_test6) {
    Matrix<int> matrix(4, 4, { 0, 11, 22, 33,   23, 55, 87, 66,   25, 54, 88, 77,   -1, 22, 100, 99 });
    int min1 = 0, min2 = -1;

    std::cout << local_min(matrix, 3, 3) << std::endl;
    std::cout << local_min(matrix, 3, 2) << std::endl;

    EXPECT_TRUE(local_min(matrix, 3, 3) == min1 || local_min(matrix, 3, 3) == min2);
}

TEST(TestAlgorithmsLib, correct_not_loop_1) {
	List<int> l;
	l.push_front(22);
	l.push_front(11);
	l.push_front(7);

	EXPECT_FALSE(is_looped_1(l));
}

TEST(TestAlgorithmsLib, correct_loop_1) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.tail()->next = l.head()->next;
	
	EXPECT_TRUE(is_looped_1(l));

	l.tail()->next = nullptr;
}

TEST(TestAlgorithmsLib, correct_loop_1_2) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.tail()->next = l.head();

	EXPECT_TRUE(is_looped_1(l));

	l.tail()->next = nullptr;
}

TEST(TestAlgorithmsLib, correct_not_loop_2) {
	List<int> l;
	l.push_front(22);
	l.push_front(11);
	l.push_front(7);

	EXPECT_FALSE(is_looped_2(l));
}

TEST(TestAlgorithmsLib, correct_loop_2) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.tail()->next = l.head()->next;

	EXPECT_TRUE(is_looped_2(l));

	l.tail()->next = nullptr;
}

TEST(TestAlgorithmsLib, correct_loop_2_2) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.tail()->next = l.head();

	EXPECT_TRUE(is_looped_2(l));

	l.tail()->next = nullptr;
}

TEST(TestAlgorithmsLib, correct_find_loop) {
	List<int> list;

	for (int i = 0; i < 5; i++) {
		list.push_back(i);
	}

	EXPECT_EQ(nullptr, find_loop(list));
}

TEST(TestAlgorithmsLib, correct_find_loop_2) {
	List<int> list;

	for (int i = 0; i < 5; i++) {
		list.push_back(i);
	}

	list.tail()->next = list.head()->next->next;

	EXPECT_EQ(list.head()->next->next, find_loop(list));

	list.tail()->next = nullptr;
}

TEST(TestAlgorithmsLib, correct_find_loop_3) {
	List<int> list;

	for (int i = 0; i < 5; i++) {
		list.push_back(i);
	}

	list.tail()->next = list.head();

	EXPECT_EQ(list.head(), find_loop(list));

	list.tail()->next = nullptr;
}
