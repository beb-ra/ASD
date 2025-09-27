#include <gtest/gtest.h>
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