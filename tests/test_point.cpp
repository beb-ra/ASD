#include <gtest/gtest.h>
#include "../lib_point/point.h"

//#define EPSILON 0.000001

TEST(TestPointLib, create_without_pr) {
	// Arrange

	// Act & Assert
	ASSERT_NO_THROW(Point());  //ф-ция не вызывает исключение
}

TEST(TestPointLib, create_with_pr) {
	// Arrange
	double x = 10;
	double y = 2;

	// Act & Assert
	ASSERT_NO_THROW(Point(x, y));  //ф-ция не вызывает исключение
}

TEST(TestPointLib, create_with_copy) {
	double x = 10;
	double y = 2;

	Point p(x, y);
	ASSERT_NO_THROW(Point(p));
}

TEST(TestPointLib, correct_create_without_pr) {
	Point p;

	EXPECT_EQ(0, p.get_x());
	EXPECT_EQ(0, p.get_y());
}

TEST(TestPointLib, correct_create_with_pr) {
	double x = 10;
	double y = 2;
	Point p(x, y);

	EXPECT_EQ(x, p.get_x());
	EXPECT_EQ(y, p.get_y());
}

TEST(TestPointLib, correct_create_with_copy) {
	double x = 10;
	double y = 2;
	Point p(x, y);
	Point p2(p);

	EXPECT_EQ(x, p2.get_x());
	EXPECT_EQ(y, p2.get_y());
}

TEST(TestPointLib, correct_setters) {
	double x1 = 10, x2 = 2.5;
	double y1 = 2, y2 = 5.5;
	Point p(x1, y1);
	p.set_x(x2);
	p.set_y(y2);

	EXPECT_EQ(x2, p.get_x());
	EXPECT_EQ(y2, p.get_y());
}