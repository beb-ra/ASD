#include <gtest/gtest.h>
#include "../lib_sphere/sphere.h"

TEST(TestSphereLib, try_create_without_pr) {
	ASSERT_NO_THROW(Sphere s());
}

TEST(TestSphereLib, try_create_with_pr) {
	double x = 10;
	double y = 2;
	double z = 7;
	double rad = 5;

	ASSERT_NO_THROW(Sphere s(x, y, z, rad));
}

TEST(TestSphereLib, uncorrect_create_with_pr) {
	double x = 10;
	double y = 2;
	double z = 7;
	double rad = -10;

	ASSERT_THROW(Sphere s(x, y, z, rad), std::invalid_argument);
}

TEST(TestSphereLib, uncorrect_create_with_copy) {
	double x = 10;
	double y = 2;
	double z = 7;
	double rad = -10;

	Point3D p(x, y, z);
	ASSERT_THROW(Sphere s(p, rad), std::invalid_argument);
}

TEST(TestSphereLib, try_create_with_copy) {
	double x = 10;
	double y = 2;
	double z = 7;
	double rad = 5;

	Sphere s(x, y, z, rad);
	ASSERT_NO_THROW(Sphere s2(s));
}

TEST(TestSphereLib, try_create_with_copy2) {
	double x = 10;
	double y = 2;
	double z = 7;
	double rad = 5;

	Point3D p(x, y, z);
	ASSERT_NO_THROW(Sphere c(p, rad));
}

TEST(TestSphereLib, correct_create_without_pr) {
	Sphere s;

	EXPECT_EQ(0, s.get_center().get_x());
	EXPECT_EQ(0, s.get_center().get_y());
	EXPECT_EQ(0, s.get_center().get_z());
	EXPECT_EQ(0, s.get_radius());
}

TEST(TestSphereLib, correct_create_with_pr) {
	double x = 10;
	double y = 2;
	double z = 7;
	double rad = 5;
	Sphere s(x, y, z, rad);

	EXPECT_EQ(x, s.get_center().get_x());
	EXPECT_EQ(y, s.get_center().get_y());
	EXPECT_EQ(z, s.get_center().get_z());
	EXPECT_EQ(rad, s.get_radius());
}

TEST(TestSphereLib, correct_create_with_copy) {
	double x = 10;
	double y = 2;
	double z = 7;
	double rad = 5;

	Sphere s(x, y, z, rad);
	Sphere s2(s);

	EXPECT_EQ(x, s2.get_center().get_x());
	EXPECT_EQ(y, s2.get_center().get_y());
	EXPECT_EQ(z, s2.get_center().get_z());
	EXPECT_EQ(rad, s2.get_radius());
}

TEST(TestSphereLib, correct_create_with_copy2) {
	double x = 10;
	double y = 2;
	double z = 7;
	double rad = 5;

	Point3D p(x, y, z);
	Sphere s(p, rad);

	EXPECT_EQ(x, s.get_center().get_x());
	EXPECT_EQ(y, s.get_center().get_y());
	EXPECT_EQ(z, s.get_center().get_z());
	EXPECT_EQ(rad, s.get_radius());
}

TEST(TestSphereLib, calculate_distance1) {
	double x = 10;
	double y = -2;
	double z = 7;
	double rad = 5;
	Sphere s(x, y, z, rad);

	Point3D p(x, y, z);

	EXPECT_EQ(0, s.calculate_distance(p));
}

TEST(TestSphereLib, calculate_distance2) {
	double x1 = 0, x2 = 0;
	double y1 = 0, y2 = -10;
	double z1 = 0, z2 = 0;
	double rad = 5;
	Sphere s(x1, y1, z1, rad);

	Point3D p(x2, y2, z2);

	EXPECT_EQ(10, s.calculate_distance(p));
}

TEST(TestSphereLib, calculate_distance3) {
	double x1 = 0, x2 = 2;
	double y1 = 0, y2 = 3;
	double z1 = 0, z2 = 6;
	double rad = 5;
	Sphere s(x1, y1, z1, rad);

	Point3D p(x2, y2, z2);

	EXPECT_EQ(7, s.calculate_distance(p));
}

TEST(TestSphereLib, calculate_distance4) {
	double x1 = 1, x2 = 2;
	double y1 = 1, y2 = 5;
	double z1 = 1, z2 = 9;
	double rad = 5;
	Sphere s(x1, y1, z1, rad);

	Point3D p(x2, y2, z2);

	EXPECT_EQ(9, s.calculate_distance(p));
}

TEST(TestSphereLib, calculate_distance5) {
	double x1 = -1, x2 = -2;
	double y1 = -1, y2 = -5;
	double z1 = -1, z2 = -9;
	double rad = 5;
	Sphere s(x1, y1, z1, rad);

	Point3D p(x2, y2, z2);

	EXPECT_EQ(9, s.calculate_distance(p));
}

TEST(TestSphereLib, correct_setters) {
	double x1 = 1, x2 = 7;
	double y1 = 1, y2 = 9;
	double z1 = -1, z2 = -9;
	double rad1 = 5, rad2 = 10;

	Sphere s(x1, y1, z1, rad1);
	Point3D center(x2, y2, z2);

	s.set_center(center);
	s.set_radius(rad2);

	EXPECT_EQ(x2, s.get_center().get_x());
	EXPECT_EQ(y2, s.get_center().get_y());
	EXPECT_EQ(z2, s.get_center().get_z());
	EXPECT_EQ(rad2, s.get_radius());
}