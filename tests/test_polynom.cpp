#include <gtest/gtest.h>
#include "../lib_polynom/polynom.h"

TEST(TestPolynomLib, try_create) {
	ASSERT_NO_THROW(Polynom p);
}

TEST(TestPolynomLib, try_create_2) {
	int powers[3] = { 1, 2, 3 };
	Monom m(2.7, powers);
	ASSERT_NO_THROW(Polynom p(m));
}

TEST(TestPolynomLib, correct_create) {
	Polynom p;
	//Monom m;
	//List<Monom> expected;
	//expected.push_back(m);

	EXPECT_EQ("default", p.name());
	//EXPECT_EQ(expected, p.monoms());
}

TEST(TestPolynomLib, correct_create_2) {
	int powers[3] = { 1, 2, 3 };
	Monom m(2.7, powers);
	Polynom p(m);
	List<Monom> expected;
	expected.push_back(m);

	EXPECT_EQ("default", p.name());
	EXPECT_EQ(expected, p.monoms());
}

TEST(TestPolynomLib, correct_parsing) {
	int powers[3] = { 1, 1, 1 };
	Monom m(8, powers);
	List<Monom> expected;
	expected.push_back(m);

	Polynom p("pl", "+8xyz");

	EXPECT_EQ("pl", p.name());
	EXPECT_EQ(expected, p.monoms());
}

TEST(TestPolynomLib, correct_parsing_2) {
	int powers[3] = { 2, 0, 5 };
	Monom m(-3, powers);
	int powers2[3] = { 1, 1, 1 };
	Monom m2(8, powers2);
	Monom m3(5.285);
	List<Monom> expected;
	expected.push_back(m);
	expected.push_back(m2);
	expected.push_back(m3);

	Polynom p("pl", "8xyz - 3x^2*z^5 + 5.285");

	EXPECT_EQ(expected, p.monoms());
}

TEST(TestPolynomLib, correct_parsing_3) {
	int powers[3] = { 1, 1, 0 };
	Monom m(1, powers);
	int powers2[3] = { 0, 2, 3 };
	Monom m2(1, powers2);
	int powers3[3] = { 0, 2, 0 };
	Monom m3(2, powers3);
	Monom m4(6);
	List<Monom> expected;
	expected.push_back(m);
	expected.push_back(m2);
	expected.push_back(m3);
	expected.push_back(m4);

	Polynom p("pl", "y^2z^3 + 2y^2 + xy + 6");

	EXPECT_EQ(expected, p.monoms());
}

TEST(TestPolynomLib, correct_monom_order) {
	int powers_x3[3] = { 3, 0, 0 };
	Monom m_x3(1, powers_x3);
	int powers_x2y1[3] = { 2, 1, 0 };
	Monom m_x2y1(1, powers_x2y1);
	int powers_x1y1z1[3] = { 1, 1, 1 };
	Monom m_xyz(1, powers_x1y1z1);
	int powers_y2[3] = { 0, 2, 0 };
	Monom m_y2(2, powers_y2);
	int powers_z3[3] = { 0, 0, 3 }; 
	Monom m_z3(1, powers_z3);
	int powers_0[3] = { 0, 0, 0 };
	Monom m(5, powers_0);

	List<Monom> expected;
	expected.push_back(m_x3);
	expected.push_back(m_x2y1);
	expected.push_back(m_xyz);
	expected.push_back(m_y2);
	expected.push_back(m_z3);
	expected.push_back(m);

	Polynom p("p", "5 + y^2 + xyz + x^3 + z^3 + x^2y");

	/*
	for (auto it = p.monoms().begin(); it != p.monoms().end(); it++) {
		std::cout << (*it) << std::endl;
	}
	std::cout << std::endl;
	for (auto it = expected.begin(); it != expected.end(); it++) {
		std::cout << (*it) << std::endl;
	}
	*/

	EXPECT_EQ(expected, p.monoms());
}

TEST(TestPolynomLib, correct_parse_same_powers) {
	int powers_x2y[3] = { 2, 1, 0 };
	Monom m_result(4, powers_x2y);
	int powers_xy[3] = { 1, 1, 0 };
	Monom m_xy_result(2, powers_xy);
	int powers_0[3] = { 0, 0, 0 };
	Monom m_const(5, powers_0);

	List<Monom> expected;
	expected.push_back(m_result);
	expected.push_back(m_xy_result);
	expected.push_back(m_const);

	Polynom p("p", "2x^2y + 3x^2y - x^2y + 4xy - 2xy + 5");

	EXPECT_EQ(expected, p.monoms());
}

TEST(TestPolynomLib, correct_operator_add) {
	int powers_x3[3] = { 3, 0, 0 };
	Monom m_x3(1, powers_x3);
	int powers_x2y1[3] = { 2, 1, 0 };
	Monom m_x2y1(1, powers_x2y1);
	int powers_x1y1z1[3] = { 1, 1, 1 };
	Monom m_xyz(1, powers_x1y1z1);
	int powers_y2[3] = { 0, 2, 0 };
	Monom m_y2(2, powers_y2);
	int powers_z3[3] = { 0, 0, 3 };
	Monom m_z3(1, powers_z3);
	int powers_0[3] = { 0, 0, 0 };
	Monom m(5, powers_0);

	List<Monom> expected;
	expected.push_back(m_x3);
	expected.push_back(m_x2y1);
	expected.push_back(m_xyz);
	expected.push_back(m_y2);
	expected.push_back(m_z3);
	expected.push_back(m);

	Polynom p1("p", "z^3 + x^2y - xy");
	Polynom p2("p", "5 + y^2 + xyz + x^3 + xy");

	/*
	for (auto it = p.monoms().begin(); it != p.monoms().end(); it++) {
		std::cout << (*it) << std::endl;
	}
	std::cout << std::endl;
	for (auto it = expected.begin(); it != expected.end(); it++) {
		std::cout << (*it) << std::endl;
	}
	*/

	Polynom p3 = p1 + p2;
	EXPECT_EQ(expected, p3.monoms());
	p1 += p2;
	EXPECT_EQ(expected, p1.monoms());
}

TEST(TestPolynomLib, correct_operator_sub) {
	int powers_x3[3] = { 3, 0, 0 };
	Monom m_x3(-1, powers_x3);
	int powers_x2y1[3] = { 2, 1, 0 };
	Monom m_x2y1(1, powers_x2y1);
	int powers_x1y1z1[3] = { 1, 1, 1 };
	Monom m_xyz(-1, powers_x1y1z1);
	int powers_y2[3] = { 0, 2, 0 };
	Monom m_y2(-2, powers_y2);
	int powers_z3[3] = { 0, 0, 3 };
	Monom m_z3(1, powers_z3);
	int powers_0[3] = { 0, 0, 0 };
	Monom m(-5, powers_0);

	List<Monom> expected;
	expected.push_back(m_x3);
	expected.push_back(m_x2y1);
	expected.push_back(m_xyz);
	expected.push_back(m_y2);
	expected.push_back(m_z3);
	expected.push_back(m);

	Polynom p1("p", "z^3 + x^2y + x^5");
	Polynom p2("p", "5 + y^2 + xyz + x^3 + x^5");

	Polynom p3 = p1 - p2;
	EXPECT_EQ(expected, p3.monoms());
	p1 -= p2;
	EXPECT_EQ(expected, p1.monoms());
}

TEST(TestPolynomLib, correct_operator_mult) {
	int powers_x3[3] = { 3, 0, 0 };
	Monom m_x3(1, powers_x3);
	int powers_x2[3] = { 2, 0, 0 };
	Monom m_x2(5, powers_x2);
	int powers_x1[3] = { 1, 0, 0 };
	Monom m_x(7, powers_x1);
	int powers_0[3] = { 0, 0, 0 };
	Monom m_3(3, powers_0);

	List<Monom> expected;
	expected.push_back(m_x3);
	expected.push_back(m_x2);
	expected.push_back(m_x);
	expected.push_back(m_3);

	Polynom p1("p1", "x^2 + 2x + 1");
	Polynom p2("p2", "x + 3");

	Polynom p3 = p1 * p2;
	EXPECT_EQ(expected, p3.monoms());
	p1 *= p2;
	EXPECT_EQ(expected, p1.monoms());
}

TEST(TestPolynomLib, correct_operator_mult_2) {
	int powers_x2[3] = { 2, 0, 0 };
	Monom m_x2(1, powers_x2);
	int powers_0[3] = { 0, 0, 0 };
	Monom m_minus1(-1, powers_0);

	List<Monom> expected;
	expected.push_back(m_x2);
	expected.push_back(m_minus1);

	Polynom p1("p1", "x + 1");
	Polynom p2("p2", "x - 1");

	Polynom p3 = p1 * p2;
	EXPECT_EQ(expected, p3.monoms());
}