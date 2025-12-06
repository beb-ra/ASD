#include <gtest/gtest.h>
#include "../lib_expression/expression.h"

TEST(TestParserLib, correct_parsing) {
	std::string s = "21 * (x + 33 * y)";

	ASSERT_NO_THROW(Parser::parse(s));
	List<Lexem> list = Parser::parse(s);

	List<Lexem> result = { Lexem("21", Constant), Lexem("*", Operator), Lexem("(", OpenBracket),
		Lexem("x", Variable), Lexem("+", Operator), Lexem("33", Constant, 33.0), Lexem("*", Operator),
		Lexem("y", Variable), Lexem(")", ClosedBracket) };
	ASSERT_EQ(list, result);
}

TEST(TestParserLib, correct_parsing_2) {
	std::string s = "x_1 * sin(y + 7) + y * (-|x_2 - 17| + 23)";

	ASSERT_NO_THROW(Parser::parse(s));
	List<Lexem> list = Parser::parse(s);

	List<Lexem> result = { Lexem("x_1", Variable), Lexem("*", Operator), Lexem("sin", Function), 
		Lexem("(", OpenBracket), Lexem("y", Variable), Lexem("+", Operator), Lexem("7", Constant, 7), 
		Lexem(")", ClosedBracket), Lexem("+", Operator), Lexem("y", Variable), Lexem("*", Operator), 
		Lexem("(", OpenBracket), Lexem("~", UnOperator), Lexem("abs", Function), Lexem("(", OpenBracket),
		Lexem("x_2", Variable), Lexem("-", Operator), Lexem("17", Constant, 17), Lexem(")", ClosedBracket),
		Lexem("+", Operator), Lexem("23", Constant, 23), Lexem(")", ClosedBracket) };
	ASSERT_EQ(list, result);
}

TEST(TestParserLib, correct_parsing_3) {
	std::string s = "||x| - |y||";

	ASSERT_NO_THROW(Parser::parse(s));
	List<Lexem> list = Parser::parse(s);

	List<Lexem> result = { Lexem("abs", Function), Lexem("(", OpenBracket), Lexem("abs", Function),
	 Lexem("(", OpenBracket), Lexem("x", Variable), Lexem(")", ClosedBracket), Lexem("-", Operator),
		Lexem("abs", Function), Lexem("(", OpenBracket), Lexem("y", Variable), Lexem(")", ClosedBracket),
		Lexem(")", ClosedBracket) };
	ASSERT_EQ(list, result);
}

TEST(TestParserLib, throw_uncorrect_parsing_missing_operator) {
	std::string s = "21 (x + 33 * y)";
	std::string s2 = "x (x + 33 * y)";
	std::string s3 = "x * (cos(x) 33 * y)";

	ASSERT_THROW(Parser::parse(s), std::logic_error);
	ASSERT_THROW(Parser::parse(s2), std::logic_error);
	ASSERT_THROW(Parser::parse(s3), std::logic_error);
}

TEST(TestParserLib, throw_uncorrect_parsing_missing_operand) {
	std::string s = "* 21 + x";
	std::string s2 = "x + (+ 33 * y)";
	std::string s3 = "x * (33 + y) -";
	std::string s4 = "3 * (15 + (x + y) * (2 * x - 7 * y^))";

	ASSERT_THROW(Parser::parse(s), std::logic_error);
	ASSERT_THROW(Parser::parse(s2), std::logic_error);
	ASSERT_THROW(Parser::parse(s3), std::logic_error);
	ASSERT_THROW(Parser::parse(s4), std::logic_error);
}

TEST(TestParserLib, throw_uncorrect_parsing) {
	std::string s = "  ";
	std::string s2 = "3 + $5";

	ASSERT_THROW(Parser::parse(s), std::logic_error);
	ASSERT_THROW(Parser::parse(s2), std::logic_error);
}

TEST(TestParserLib, throw_uncorrect_parsing_2) {
	std::string s = "--x";
	std::string s2 = "x ++ y";

	ASSERT_THROW(Parser::parse(s), std::logic_error);
	ASSERT_THROW(Parser::parse(s2), std::logic_error);
}

TEST(TestParserLib, correct_parsing_un_operator) {
	std::string s = "x * -y + 5";
	std::string s2 = "x * (-y) + 5";

	ASSERT_THROW(Parser::parse(s), std::logic_error);
	ASSERT_NO_THROW(Parser::parse(s2));
}

TEST(TestParserLib, throw_uncorrect_parsing_brackets) {
	std::string s = "((x + y)*(x - y)]";
	std::string s2 = "(13 + 52";
	std::string s3 = "13 + )52";

	ASSERT_THROW(Parser::parse(s), std::logic_error);
	ASSERT_THROW(Parser::parse(s2), std::logic_error);
	ASSERT_THROW(Parser::parse(s3), std::logic_error);
}

TEST(TestParserLib, correct_parsing_brackets) {
	std::string s = "[{(x + y) * (x - y)} - | x + z_2 |]";

	ASSERT_NO_THROW(Parser::parse(s));
	List<Lexem> list = Parser::parse(s);

	List<Lexem> result = { Lexem("[", OpenBracket), Lexem("{", OpenBracket), Lexem("(", OpenBracket),
		Lexem("x", Variable), Lexem("+", Operator), Lexem("y", Variable), Lexem(")", ClosedBracket),
		Lexem("*", Operator), Lexem("(", OpenBracket), Lexem("x", Variable), Lexem("-", Operator),
		Lexem("y", Variable), Lexem(")", ClosedBracket), Lexem("}", ClosedBracket), Lexem("-", Operator),
		Lexem("abs", Function), Lexem("(", OpenBracket), Lexem("x", Variable), Lexem("+", Operator),
		Lexem("z_2", Variable), Lexem(")", ClosedBracket), Lexem("]", ClosedBracket)
	};
	ASSERT_EQ(list, result);
}

TEST(TestParserLib, function_with_abs) {
	std::string s = "sin(|x|)";

	ASSERT_NO_THROW(Parser::parse(s));
	List<Lexem> list = Parser::parse(s);

	List<Lexem> result = {
		Lexem("sin", Function),
		Lexem("(", OpenBracket),
		Lexem("abs", Function),
		Lexem("(", OpenBracket),
		Lexem("x", Variable),
		Lexem(")", ClosedBracket),
		Lexem(")", ClosedBracket)
	};
	ASSERT_EQ(list, result);
}

TEST(TestExpressionLib, try_create) {
	std::string s = "21 * (x + 33 * y)";
	ASSERT_NO_THROW(Expression e(s));
}

TEST(TestExpressionLib, correct_create) {
	std::string s = "21 * (x + 33 * y)";
	Expression e(s);
}
