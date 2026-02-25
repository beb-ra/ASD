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

TEST(TestPolynomLib, try_create_3) {
	Monom m(2.7, { 1, 2, 3 });
	ASSERT_NO_THROW(Polynom p(m));
}

TEST(TestPolynomLib, correct_create) {
	Polynom p;

	EXPECT_EQ("default", p.name());
	EXPECT_TRUE(p.monoms().is_empty());
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


TEST(TestPolynomLib, correct_create_3) {
	Monom m(2.7, { 1, 2, 3 });
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
	Monom m_const(5);

	List<Monom> expected;
	expected.push_back(m_const);

	Polynom p("p", "2x^2y - 3x^2y + x^2y + 2xy - 2xy + 5");

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

TEST(TestPolynomLib, correct_add_2) {
	Monom m_x3(1, { 3, 0, 0 });
	Monom m_x4(1, { 4, 0, 0 });
	Monom m_x2(1, { 2, 0, 0 });

	// x^4 + x^3 + x^2 + 2x + 8
	List<Monom> expected;
	expected.push_back(m_x4);
	expected.push_back(m_x3);
	expected.push_back(m_x2);
	expected.push_back(Monom(2, { 1, 0, 0 }));
	expected.push_back(Monom(8, { 0, 0, 0 }));

	Polynom p1("p1", "x^3 + x + 5");
	Polynom p2("p2", "x^4 + x^2 + x + 3");

	Polynom p3 = p1 + p2;
	EXPECT_EQ(expected, p3.monoms());
	p1 += p2;
	EXPECT_EQ(expected, p1.monoms());
}

TEST(TestPolynomLib, correct_add_empty_polynom) {
	int powers_x2[3] = { 2, 0, 0 };
	Monom m_x2(3, powers_x2);
	int powers_x[3] = { 1, 0, 0 };
	Monom m_x(2, powers_x);

	List<Monom> expected;
	expected.push_back(m_x2);
	expected.push_back(m_x);

	Polynom p1("p1", "3x^2 + 2x");
	Polynom p2("p2", "");

	Polynom p3 = p1 + p2;
	EXPECT_EQ(expected, p3.monoms());
	p2 += p1;
	EXPECT_EQ(expected, p2.monoms());
}

TEST(TestPolynomLib, correct_add_with_complete_cancel) {
	Monom m_x2(5, { 2, 0, 0 });
	Monom m_y(3, { 0, 1, 0 });

	Polynom p1("p1", "5x^2 + 3y");
	Polynom p2("p2", "-5x^2 - 3y");

	List<Monom> expected;

	Polynom p3 = p1 + p2;
	EXPECT_EQ(expected, p3.monoms());
	p1 += p2;
	EXPECT_EQ(expected, p1.monoms());
	EXPECT_TRUE(p1.monoms().is_empty());
}

TEST(TestPolynomLib, correct_add_itself) {
	Monom m_x2(10, { 2, 0, 0 });
	Monom m_y(6, { 0, 1, 0 });

	Polynom p1("p1", "5x^2 + 3y");

	List<Monom> expected;
	expected.push_back(m_x2);
	expected.push_back(m_y);

	Polynom p3 = p1 + p1;
	EXPECT_EQ(expected, p3.monoms());
	p1 += p1;
	EXPECT_EQ(expected, p1.monoms());
}

TEST(TestPolynomLib, correct_add_by_num) {
	Monom m_x2(5, { 2, 0, 0 });
	Monom m_y(3, { 0, 1, 0 });

	Polynom p1("p1", "5x^2 + 3y - 3.25");

	List<Monom> expected;
	expected.push_back(m_x2);
	expected.push_back(m_y);

	Polynom p3 = p1 + 3.25;
	Polynom p4 = 3.25 + p1;

	EXPECT_EQ(expected, p4.monoms());
	EXPECT_EQ(expected, p3.monoms());
	p1 += 3.25;
	EXPECT_EQ(expected, p1.monoms());
}

TEST(TestPolynomLib, correct_operator_sub) {
	Monom m_x3(-1, { 3, 0, 0 });
	Monom m_x2y1(1, { 2, 1, 0 });
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

TEST(TestPolynomLib, correct_sub_2) {
	Monom m_x2(1, { 2, 0, 0 });
	Monom m_x(1, { 1, 0, 0 });
	Monom m_1(1, { 0, 0, 0 });

	// (x^2 + x + 1) - (2x^2 + 3x + 5) = -x^2 - 2x - 4
	List<Monom> expected;
	expected.push_back(Monom(-1, { 2, 0, 0 }));
	expected.push_back(Monom(-2, { 1, 0, 0 }));
	expected.push_back(Monom(-4, { 0, 0, 0 }));

	Polynom p1("p1", "x^2 + x + 1");
	Polynom p2("p2", "2x^2 + 3x + 5");

	Polynom p3 = p1 - p2;
	EXPECT_EQ(expected, p3.monoms());
	p1 -= p2;
	EXPECT_EQ(expected, p1.monoms());
}

TEST(TestPolynomLib, correct_sub_empty_polynom) {
	int powers_x2[3] = { 2, 0, 0 };
	Monom m_x2(3, powers_x2);
	int powers_x[3] = { 1, 0, 0 };
	Monom m_x(2, powers_x);

	List<Monom> expected;
	expected.push_back(m_x2);
	expected.push_back(m_x);

	Polynom p1("p1", "3x^2 + 2x");
	Polynom p2("p2", "");

	Polynom p3 = p1 - p2;
	EXPECT_EQ(expected, p3.monoms());
	p2 -= p1;
	EXPECT_EQ(expected, p2.monoms());
}

TEST(TestPolynomLib, correct_sub_with_complete_cancel) {
	Monom m_x2(5, { 2, 0, 0 });
	Monom m_y(3, { 0, 1, 0 });

	Polynom p1("p1", "5x^2 + 3y");
	Polynom p2("p2", "5x^2 + 3y");

	List<Monom> expected;

	Polynom p3 = p1 - p2;
	EXPECT_EQ(expected, p3.monoms());
	p1 -= p2;
	EXPECT_EQ(expected, p1.monoms());
	EXPECT_TRUE(p1.monoms().is_empty());
}

TEST(TestPolynomLib, correct_sub_itself) {
	Polynom p1("p1", "5x^2 + 3y");

	List<Monom> expected;

	Polynom p3 = p1 - p1;
	EXPECT_EQ(expected, p3.monoms());
	p1 -= p1;
	EXPECT_EQ(expected, p1.monoms());
	EXPECT_TRUE(p1.monoms().is_empty());
}

TEST(TestPolynomLib, correct_sub_by_num) { ///
	Monom m_x2(5, { 2, 0, 0 });
	Monom m_y(3, { 0, 1, 0 });

	Polynom p1("p1", "5x^2 + 3y + 3.25");

	List<Monom> expected;
	expected.push_back(m_x2);
	expected.push_back(m_y);

	List<Monom> expected2;
	expected2.push_back(-m_x2);
	expected2.push_back(-m_y);

	Polynom p3 = p1 - 3.25;
	Polynom p4 = 3.25 - p1;

	EXPECT_EQ(expected, p3.monoms());
	EXPECT_EQ(expected2, p4.monoms());
	p1 -= 3.25;
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
	p1 *= p2;
	EXPECT_EQ(expected, p1.monoms());
}

TEST(TestPolynomLib, correct_mult_3) {
	// (x^2 + xy + y^2)(x - y) = x^3 - y^3
	int powers_x3[3] = { 3, 0, 0 };
	Monom m_x3(1, powers_x3);
	int powers_y3[3] = { 0, 3, 0 };
	Monom m_y3(-1, powers_y3);

	List<Monom> expected;
	expected.push_back(m_x3);
	expected.push_back(m_y3);

	Polynom p1("p1", "x^2 + xy + y^2");
	Polynom p2("p2", "x - y");

	Polynom p3 = p1 * p2;
	EXPECT_EQ(expected, p3.monoms());
	p1 *= p2;
	EXPECT_EQ(expected, p1.monoms());
}

TEST(TestPolynomLib, correct_mult_by_zero) { 
	List<Monom> expected;

	Polynom p1("p1", "5x + 3");
	Polynom p2("p2", "0");

	Polynom p3 = p1 * p2;
	EXPECT_EQ(expected, p3.monoms());
	p1 *= p2;
	EXPECT_EQ(expected, p1.monoms());
	EXPECT_TRUE(p1.monoms().is_empty());
}

TEST(TestPolynomLib, correct_mult_itself) {
	Polynom p1("p1", "5x + 3y");
	Monom m_x2(25, {2, 0, 0});
	Monom m_xy(30, { 1, 1, 0 });
	Monom m_y2(9, { 0, 2, 0 });

	List<Monom> expected;
	expected.push_back(m_x2);
	expected.push_back(m_xy);
	expected.push_back(m_y2);

	Polynom p3 = p1 * p1;
	EXPECT_EQ(expected, p3.monoms());
	p1 *= p1;
	EXPECT_EQ(expected, p1.monoms());
}

TEST(TestPolynomLib, correct_mult_by_num) {
	Polynom p1("p1", "5x^2 + 3y");

	List<Monom> expected;

	Polynom p3 = p1 * 0;
	Polynom p4 = 0 * p1;

	EXPECT_EQ(expected, p3.monoms());
	EXPECT_EQ(expected, p4.monoms());
	p1 *= 0;
	EXPECT_EQ(expected, p1.monoms());
	EXPECT_TRUE(p1.monoms().is_empty());
}

TEST(TestPolynomLib, correct_operator_add_by_monom) {
	Monom m_x3(1, { 3, 0, 0 });
	Monom m_xyz(1, { 1, 1, 1 });
	Monom m_y2(2, { 0, 2, 0 });
	Monom m_0(5, { 0, 0, 0 });
	Monom m(-1, {1, 1, 0});

	List<Monom> expected;
	expected.push_back(m_x3);
	expected.push_back(m_xyz);
	expected.push_back(m_y2);
	expected.push_back(m_0);

	Polynom p1("p", "5 + y^2 + xyz + x^3 + xy");

	Polynom p3 = m + p1;
	EXPECT_EQ(expected, p3.monoms());
	p1 += m;
	EXPECT_EQ(expected, p1.monoms());
}

TEST(TestPolynomLib, correct_operator_sub_by_monom) {
	Monom m_x3(1, { 3, 0, 0 });
	Monom m_xyz(1, { 1, 1, 1 });
	Monom m_y2(2, { 0, 2, 0 });
	Monom m_0(5, { 0, 0, 0 });
	Monom m(1, { 1, 1, 0 });

	List<Monom> expected;
	expected.push_back(m_x3);
	expected.push_back(m_xyz);
	expected.push_back(m_y2);
	expected.push_back(m_0);

	Polynom p1("p", "-5 - y^2 - xyz - x^3 + xy");

	Polynom p3 = m - p1;
	EXPECT_EQ(expected, p3.monoms());
	p1 -= m;
	EXPECT_EQ(expected, p1.monoms());
}

TEST(TestPolynomLib, correct_operator_mult_by_monom) {
	Monom m_x3(3, { 3, 0, 0 });
	Monom m_x2(6, { 2, 0, 0 });
	Monom m_x(3, { 1, 0, 0 });
	Monom m(3, { 1, 0, 0 });

	List<Monom> expected;
	expected.push_back(m_x3);
	expected.push_back(m_x2);
	expected.push_back(m_x);

	Polynom p1("p1", "x^2 + 2x + 1");

	Polynom p3 = m * p1;
	EXPECT_EQ(expected, p3.monoms());
	p1 *= m;
	EXPECT_EQ(expected, p1.monoms());
}

TEST(TestPolynomLib, correct_operator_div_by_monom) {
	Monom m_x(1, { 1, 0, 0 });
	Monom m_2(2, { 0, 0, 0 });
	Monom m_1(1, { -1, 0, 0 });
	Monom m(1, { 1, 0, 0 });

	List<Monom> expected;
	expected.push_back(m_x);
	expected.push_back(m_2);
	expected.push_back(m_1);

	Polynom p1("p1", "x^2 + 2x + 1");

	Polynom p3 = p1 / m;
	EXPECT_EQ(expected, p3.monoms());
	p1 /= m;
	EXPECT_EQ(expected, p1.monoms());
}

TEST(TestPolynomLib, throw_uncorrect_operator_div_zero) {
	Monom m(0, { 1, 0, 0 });

	Polynom p1("p1", "x^2 + 2x + 1");

	EXPECT_THROW(p1 / m, std::invalid_argument);
}