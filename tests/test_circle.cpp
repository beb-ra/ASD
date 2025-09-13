#include <gtest/gtest.h>
#include "../lib_circle/circle.h"

#define EPSILON 0.000001

TEST(TestCircleLib, create_without_pr) {
	// Arrange

	// Act & Assert
	ASSERT_NO_THROW(Circle c());  //ф-ция не вызывает исключение
}

TEST(TestCircleLib, create_with_pr) {
	// Arrange
	double x = 10;
	double y = 2;
	double rad = 5;

	// Act & Assert
	ASSERT_NO_THROW(Circle c(x, y, rad));  //ф-ция не вызывает исключение
}