#include <gtest/gtest.h>
#include "../lib_expression/expression.h"

TEST(TestExpressionLib, try_create) {
	std::string s = "21 * (x + 33 * y)";
	ASSERT_NO_THROW(Expression e(s));
}

TEST(TestExpressionLib, correct_create) {
	std::string s = "21 * (x + 33 * y)";
	Expression e(s);
	e.print();
}
