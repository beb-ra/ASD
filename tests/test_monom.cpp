#include <gtest/gtest.h>
#include "../lib_polynom/monom.h"

TEST(TestMonomLib, try_create) {
	ASSERT_NO_THROW(Monom m);
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

TEST(TestMonomLib, correct_operator_equality) {
	int m_powers1[3] = { 1, 3, 4 };
	int m_powers2[3] = { 1, 2, 4 };
	Monom m1(5.1, m_powers1);
	Monom m2(10, m_powers2);

	EXPECT_TRUE(m1 > m2);
	EXPECT_TRUE(m2 < m1);

	EXPECT_FALSE(m1 < m2);
	EXPECT_FALSE(m2 > m1);

	EXPECT_TRUE(m1 != m2);
	EXPECT_FALSE(m1 == m2);
}

TEST(TestMonomLib, correct_operator_equality_2) {
	int m_powers1[3] = { 1, 3, 4 };
	int m_powers2[3] = { 3, 2, 4 };
	Monom m1(5.1, m_powers1);
	Monom m2(10, m_powers2);

	EXPECT_TRUE(m1 < m2);
	EXPECT_TRUE(m2 > m1);

	EXPECT_FALSE(m1 > m2);
	EXPECT_FALSE(m2 < m1);

	EXPECT_TRUE(m1 != m2);
	EXPECT_FALSE(m1 == m2);
}

TEST(TestMonomLib, correct_operator_equality_3) {
	int m_powers1[3] = { 1, 3, 4 };
	Monom m1(5.1, m_powers1);
	Monom m2(10, m_powers1);

	EXPECT_FALSE(m1 < m2);
	EXPECT_FALSE(m2 > m1);

	EXPECT_FALSE(m1 > m2);
	EXPECT_FALSE(m2 < m1);

	EXPECT_TRUE(m1 == m2);
	EXPECT_FALSE(m1 != m2);
}

TEST(TestMonomLib, throw_operator_add) {
	int m_powers1[3] = { 1, 3, 4 };
	int m_powers2[3] = { 3, 2, 4 };
	Monom m1(5.1, m_powers1);
	Monom m2(10, m_powers2);

	EXPECT_THROW(m1 + m2, std::invalid_argument);
	EXPECT_THROW(m1 += m2, std::invalid_argument);
}

TEST(TestMonomLib, throw_operator_sub) {
	int m_powers1[3] = { 1, 3, 4 };
	int m_powers2[3] = { 3, 2, 4 };
	Monom m1(5.1, m_powers1);
	Monom m2(10, m_powers2);

	EXPECT_THROW(m1 - m2, std::invalid_argument);
	EXPECT_THROW(m1 -= m2, std::invalid_argument);
}

TEST(TestMonomLib, correct_operator_add) {
	int m_powers[3] = { 1, 3, 4 };
	Monom m1(5.1, m_powers);
	Monom m2(10, m_powers);
	Monom m3(15.1, m_powers);

	EXPECT_EQ(m1 + m2, m3);
	m1 += m2;
	EXPECT_EQ(m1, m3);
}

TEST(TestMonomLib, correct_operator_sub) {
	int m_powers[3] = { 1, 3, 4 };
	Monom m1(15.1, m_powers);
	Monom m2(10, m_powers);
	Monom m3(5.1, m_powers);

	EXPECT_EQ(m1 - m2, m3);
	m1 -= m2;
	EXPECT_EQ(m1, m3);
}

TEST(TestMonomLib, correct_operator_mult) {
	int m_powers1[3] = { 1, 3, 4 };
	int m_powers2[3] = { 3, 2, 4 };
	int m_powers3[3] = { 4, 5, 8 };
	Monom m1(5.1, m_powers1);
	Monom m2(10, m_powers2);
	Monom m3(51, m_powers3);

	EXPECT_EQ(m1 * m2, m3);
	m1 *= m2;
	EXPECT_EQ(m1, m3);
}

TEST(TestMonomLib, throw_operator_div) {
	int m_powers1[3] = { 1, 3, 4 };
	int m_powers2[3] = { 3, 2, 4 };
	Monom m1(5.1, m_powers1);
	Monom m2(0, m_powers2);

	EXPECT_THROW(m1 / m2, std::invalid_argument);
	EXPECT_THROW(m1 /= m2, std::invalid_argument);
}

TEST(TestMonomLib, correct_operator_div) {
	int m_powers1[3] = { 1, 3, 4 };
	int m_powers2[3] = { 3, 2, 4 };
	int m_powers3[3] = { -2, 1, 0 };
	Monom m1(2, m_powers1);
	Monom m2(10, m_powers2);
	Monom m3(0.2, m_powers3);

	EXPECT_EQ(m1 / m2, m3);
	m1 /= m2;
	EXPECT_EQ(m1, m3);
}

TEST(TestMonomLib, correct_mult_on_number) {
	int m_powers1[3] = { 1, 3, 4 };
	Monom m1(2, m_powers1);
	Monom m2(6, m_powers1);

	EXPECT_EQ(m1 * 3, m2);
	EXPECT_EQ(3 * m1, m2);
	m1 *= 3;
	EXPECT_EQ(m1, m2);
}

TEST(TestMonomLib, correct_div_on_number) {
	int m_powers1[3] = { 1, 3, 4 };
	Monom m1(8, m_powers1);
	Monom m2(2, m_powers1);

	EXPECT_EQ(m1 / 4, m2);
	EXPECT_EQ(16 / m1, m2);
	m1 /= 4;
	EXPECT_EQ(m1, m2);
}

TEST(TestMonomLib, throw_add_on_number) {
	int m_powers1[3] = { 1, 3, 4 };
	Monom m1(8, m_powers1);

	EXPECT_THROW(m1 + 4, std::invalid_argument);
}

TEST(TestMonomLib, throw_sub_on_number) {
	int m_powers1[3] = { 1, 3, 4 };
	Monom m1(8, m_powers1);

	EXPECT_THROW(m1 - 4, std::invalid_argument);
}

TEST(TestMonomLib, correct_unary_minus) {
	int m_powers1[3] = { 1, 3, 4 };
	Monom m1(8.2, m_powers1);
	Monom m2(-8.2, m_powers1);

	EXPECT_EQ(-m1, m2);
}

TEST(TestMonomLib, correct_calculate) {
	int m_powers1[3] = { 1, 3, 4 };
	int m_powers2[3] = { -1, -2, 0 };
	Monom m1(8.2, m_powers1);
	Monom m2(5.5, m_powers2);

	EXPECT_DOUBLE_EQ(m1.calculate(4, 3, 2), 14169.6);
	EXPECT_DOUBLE_EQ(m1.calculate(2, -2, 2), -2099.2);
	EXPECT_DOUBLE_EQ(m2.calculate(1, 2, 2), 1.375);
}

TEST(TestMonomLib, correct_parse) {
	size_t pos = 0;
	Monom m = MonomParser::parse("+8xyz", pos);

	EXPECT_EQ(8, m.coeff());
	EXPECT_EQ(1, m.power_x());
	EXPECT_EQ(1, m.power_y());
	EXPECT_EQ(1, m.power_z());
}

TEST(TestMonomLib, correct_parse_1) {
	size_t pos = 0;
	Monom m = MonomParser::parse("-8x^2 y * z^3", pos);

	EXPECT_EQ(-8, m.coeff());
	EXPECT_EQ(2, m.power_x());
	EXPECT_EQ(1, m.power_y());
	EXPECT_EQ(3, m.power_z());
}

TEST(TestMonomLib, correct_parse_2) {
	size_t pos = 0;
	Monom m = MonomParser::parse("-8 x  ^  2  y  *  z ^  3", pos);

	EXPECT_EQ(-8, m.coeff());
	EXPECT_EQ(2, m.power_x());
	EXPECT_EQ(1, m.power_y());
	EXPECT_EQ(3, m.power_z());
}

TEST(TestMonomLib, correct_parse_3) {
	size_t pos = 0;
	Monom m = MonomParser::parse("+6.376*x^231*y^888z^0", pos);

	EXPECT_EQ(6.376, m.coeff());
	EXPECT_EQ(231, m.power_x());
	EXPECT_EQ(888, m.power_y());
	EXPECT_EQ(0, m.power_z());
}

TEST(TestMonomLib, correct_parse_4) {
	size_t pos = 0;
	Monom m = MonomParser::parse("-6.376*z^231", pos);

	EXPECT_EQ(-6.376, m.coeff());
	EXPECT_EQ(0, m.power_x());
	EXPECT_EQ(0, m.power_y());
	EXPECT_EQ(231, m.power_z());
}

TEST(TestMonomLib, correct_parse_5) {
	size_t pos = 0;
	Monom m = MonomParser::parse("-6.376", pos);

	EXPECT_EQ(-6.376, m.coeff());
	EXPECT_EQ(0, m.power_x());
	EXPECT_EQ(0, m.power_y());
	EXPECT_EQ(0, m.power_z());
}

TEST(TestMonomLib, throw_uncorrect_parse) {
	size_t pos = 0;

	EXPECT_THROW(MonomParser::parse("+ ", pos); , std::invalid_argument);
	EXPECT_THROW(MonomParser::parse("- +", pos);, std::invalid_argument);
	EXPECT_THROW(MonomParser::parse("-8x & y", pos); , std::invalid_argument);
	EXPECT_THROW(MonomParser::parse("- * 8", pos);, std::invalid_argument);
	EXPECT_THROW(MonomParser::parse("* 8xy", pos); , std::invalid_argument);
}