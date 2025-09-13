#include <gtest/gtest.h>
#include "../lib_point/point.h"

#define EPSILON 0.000001

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

TEST(TestPointLib, test_getter) {
	// Arrange
	double x = 10;
	double y = 2;

	Point p(x, y);
	// Act & Assert
	EXPECT_EQ(x, p.get_x());
}