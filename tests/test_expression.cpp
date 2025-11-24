#include <gtest/gtest.h>
#include "../lib_expression/expression.h"

TEST(TestParserLib, correct_parsing) {
	std::string s = "21 * (x + 33 * y)";

	ASSERT_NO_THROW(Parser::parse(s));
	List<Lexem> list = Parser::parse(s);
	List<Lexem> result = { Lexem("21", Constant, 21), Lexem("*", Operator), Lexem("(", OpenBracket),
		Lexem("x", Variable), Lexem("+", Operator), Lexem("33", Constant, 33), Lexem("*", Operator),
		Lexem("y", Variable), Lexem(")", ClosedBracket) };
	ASSERT_EQ(list, result);
}

TEST(TestParserLib, correct_parsing_2) {
	std::string s = "x_1 * sin(y + 7) + y * (-|x_2 - 17| + 23)";

	ASSERT_NO_THROW(Parser::parse(s));
	List<Lexem> list = Parser::parse(s);
	
	//List<Lexem> result = { Lexem("x_1", Variable), Lexem()};
	//ASSERT_EQ(list, result);
}

TEST(TestExpressionLib, try_create) {
	std::string s = "21 * (x + 33 * y)";
	ASSERT_NO_THROW(Expression e(s));
}

TEST(TestExpressionLib, correct_create) {
	std::string s = "21 * (x + 33 * y)";
	Expression e(s);
	e.print();
}
