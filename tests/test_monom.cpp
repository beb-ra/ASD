#include <gtest/gtest.h>
#include "../lib_polynom/monom.h"

TEST(TestMonomLib, try_create) {
	ASSERT_NO_THROW(Monom m());
}

TEST(TestMonomLib, try_create_2) {
	int powers[3] = { 1, 2, 3 };
	ASSERT_NO_THROW(Monom m(2.7, powers));
}

TEST(TestMonomLib, correct_create) {
	Monom m;

	EXPECT_EQ(0.0, m.coeff());
}

TEST(TestMonomLib, correct_create_2) {
	int m_powers[3] = { 1, 3, 4 };
	Monom m(5.17, m_powers);

	EXPECT_EQ(5.17, m.coeff());
	EXPECT_EQ(m_powers[0], m.power_x());
	EXPECT_EQ(m_powers[1], m.power_y());
	EXPECT_EQ(m_powers[2], m.power_z());
}