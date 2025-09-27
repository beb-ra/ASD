#include <gtest/gtest.h>
#include "../lib_point3D/point3d.h"

TEST(TestPoint3DLib, create_without_pr) {
	// Arrange

	// Act & Assert
	ASSERT_NO_THROW(Point3D());  //ф-ция не вызывает исключение
}

TEST(TestPoint3DLib, create_with_pr) {
	// Arrange
	double x = 10;
	double y = 2;
	double z = 5;

	// Act & Assert
	ASSERT_NO_THROW(Point3D(x, y, z));  //ф-ция не вызывает исключение
}

TEST(TestPoint3DLib, create_with_copy) {
	double x = 10;
	double y = 2;
	double z = 5;

	Point3D p(x, y, z);

	ASSERT_NO_THROW(Point3D(p));
}

TEST(TestPoint3DLib, create_with_copy2) {
	double x = 10;
	double y = 2;
	double z = 5;

	Point p(x, y);

	ASSERT_NO_THROW(Point3D(p, z));
}

TEST(TestPoint3DLib, correct_create_without_pr) {
	Point3D p;

	EXPECT_EQ(0, p.get_x());
	EXPECT_EQ(0, p.get_y());
	EXPECT_EQ(0, p.get_z());
}

TEST(TestPoint3DLib, correct_create_with_pr) {
	double x = 10;
	double y = 2;
	double z = 5;
	Point3D p(x, y, z);

	EXPECT_EQ(x, p.get_x());
	EXPECT_EQ(y, p.get_y());
	EXPECT_EQ(z, p.get_z());
}

TEST(TestPoint3DLib, correct_create_with_copy) {
	double x = 10;
	double y = 2;
	double z = 5;

	Point3D p(x, y, z);
	Point3D p2(p);

	EXPECT_EQ(x, p2.get_x());
	EXPECT_EQ(y, p2.get_y());
	EXPECT_EQ(z, p2.get_z());
}

TEST(TestPoint3DLib, correct_create_with_copy2) {
	double x = 10;
	double y = 2;
	double z = 5;

	Point p(x, y);
	Point3D p2(p, z);

	EXPECT_EQ(x, p2.get_x());
	EXPECT_EQ(y, p2.get_y());
	EXPECT_EQ(z, p2.get_z());
}

TEST(TestPoint3DLib, correct_setters) {
	double x1 = 10, x2 = 2.5;
	double y1 = 2, y2 = 5.5;
	double z1 = 5, z2 = 10.5;
	Point3D p(x1, y1, z1);
	p.set_x(x2);
	p.set_y(y2);
	p.set_z(z2);

	EXPECT_EQ(x2, p.get_x());
	EXPECT_EQ(y2, p.get_y());
	EXPECT_EQ(z2, p.get_z());
}