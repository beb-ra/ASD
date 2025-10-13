#include <gtest/gtest.h>
#include "../lib_circle/circle.h"

#define EPSILON 0.000001

TEST(TestCircleLib, try_create_without_pr) {
	ASSERT_NO_THROW(Circle c());
}

TEST(TestCircleLib, try_create_with_pr) {
	double x = 10;
	double y = 2;
	double rad = 5;

	ASSERT_NO_THROW(Circle c(x, y, rad));
}

TEST(TestCircleLib, uncorrect_create_with_pr) {
	double x = 10;
	double y = 2;
	double rad = -10;

	ASSERT_THROW(Circle c(x, y, rad), std::invalid_argument);
}

TEST(TestCircleLib, uncorrect_create_with_copy) {
	double x = 10;
	double y = 2;
	double rad = -10;

	Point p(x, y);
	ASSERT_THROW(Circle c(p, rad), std::invalid_argument);
}

TEST(TestCircleLib, try_create_with_copy) {
	double x = 10;
	double y = 2;
	double rad = 5;

	Circle c(x, y, rad);
	ASSERT_NO_THROW(Circle c2(c));
}

TEST(TestCircleLib, try_create_with_copy2) {
	double x = 10;
	double y = 2;
	double rad = 5;

	Point p(x, y);
	ASSERT_NO_THROW(Circle c(p, rad));
}

TEST(TestCircleLib, correct_create_without_pr) {
	Circle c;

	EXPECT_EQ(0, c.get_center().get_x());
	EXPECT_EQ(0, c.get_center().get_y());
	EXPECT_EQ(0, c.get_radius());
}

TEST(TestCircleLib, correct_create_with_pr) {
	double x = 10;
	double y = 2;
	double rad = 5;
	Circle c(x, y, rad);

	EXPECT_EQ(x, c.get_center().get_x());
	EXPECT_EQ(y, c.get_center().get_y());
	EXPECT_EQ(rad, c.get_radius());
}

TEST(TestCircleLib, correct_create_with_copy) {
	double x = 10;
	double y = 2;
	double rad = 5;

	Circle c(x, y, rad);
	Circle c2(c);

	EXPECT_EQ(x, c2.get_center().get_x());
	EXPECT_EQ(y, c2.get_center().get_y());
	EXPECT_EQ(rad, c2.get_radius());
}

TEST(TestCircleLib, correct_create_with_copy2) {
	double x = 10;
	double y = 2;
	double rad = 5;

	Point p(x, y);
	Circle c(p, rad);

	EXPECT_EQ(x, c.get_center().get_x());
	EXPECT_EQ(y, c.get_center().get_y());
	EXPECT_EQ(rad, c.get_radius());
}

TEST(TestCircleLib, calculate_distance1) {
	double x = 10;
	double y = -2;
	double rad = 5;
	Circle c(x, y, rad);

	Point p(x, y);

	EXPECT_EQ(0, c.calculate_distance(p));
}

TEST(TestCircleLib, calculate_distance2) {
	double x1 = 10, x2 = 0;
	double y1 = 0, y2 = 0;
	double rad = 5;
	Circle c(x1, y1, rad);

	Point p(x2, y2);

	EXPECT_EQ(10, c.calculate_distance(p));
}

TEST(TestCircleLib, calculate_distance3) {
	double x1 = 0, x2 = 0;
	double y1 = 0, y2 = -10;
	double rad = 5;
	Circle c(x1, y1, rad);

	Point p(x2, y2);

	EXPECT_EQ(10, c.calculate_distance(p));
}

TEST(TestCircleLib, calculate_distance4) {
	double x1 = 4, x2 = 4;
	double y1 = -1, y2 = -6;
	double rad = 5;
	Circle c(x1, y1, rad);

	Point p(x2, y2);

	EXPECT_EQ(5, c.calculate_distance(p));
}

TEST(TestCircleLib, calculate_distance5) {
	double x1 = 1, x2 = 7;
	double y1 = 1, y2 = 9;
	double rad = 5;
	Circle c(x1, y1, rad);

	Point p(x2, y2);

	EXPECT_EQ(10, c.calculate_distance(p));
}

TEST(TestCircleLib, correct_setters) {
	double x1 = 1, x2 = 7;
	double y1 = 1, y2 = 9;
	double rad1 = 5, rad2 = 10;

	Circle c(x1, y1, rad1);
	Point center(x2, y2);

	c.set_center(center);
	c.set_radius(rad2);

	EXPECT_EQ(x2, c.get_center().get_x());
	EXPECT_EQ(y2, c.get_center().get_y());
	EXPECT_EQ(rad2, c.get_radius());
}