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
	Monom m;
	List<Monom> result;
	result.push_back(m);

	EXPECT_EQ("default", p.name());
	EXPECT_EQ(result, p.monoms());
}

TEST(TestPolynomLib, correct_create_2) {
	int powers[3] = { 1, 2, 3 };
	Monom m(2.7, powers);
	Polynom p(m);
	List<Monom> result;
	result.push_back(m);

	EXPECT_EQ("default", p.name());
	EXPECT_EQ(result, p.monoms());
}

TEST(TestPolynomLib, correct_parsing) {
	int powers[3] = { 1, 1, 1 };
	Monom m(8, powers);
	List<Monom> result;
	result.push_back(m);

	Polynom p("pl", "+8xyz");

	EXPECT_EQ("pl", p.name());
	EXPECT_EQ(result, p.monoms());
}

/*
TEST(TestPolynomLib, correct_parsing_2) {
	int powers[3] = { 1, 1, 1 };
	Monom m(8, powers);
	int powers2[3] = { 2, 0, 5 };
	Monom m2(-3, powers2);
	List<Monom> result;
	result.push_back(m);
	result.push_back(m2);

	Polynom p("pl", "+8xyz - 3x^2*z^5");

	EXPECT_EQ("pl", p.name());
	EXPECT_EQ(result, p.monoms());
}
*/