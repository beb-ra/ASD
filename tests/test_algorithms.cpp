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
