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

	List<Lexem> result = { Lexem("x_1", Variable), Lexem("*", Operator), Lexem("sin", Function, DBL_MAX, -1, my_sin),
		Lexem("(", OpenBracket), Lexem("y", Variable), Lexem("+", Operator), Lexem("7", Constant, 7), 
		Lexem(")", ClosedBracket), Lexem("+", Operator), Lexem("y", Variable), Lexem("*", Operator), 
		Lexem("(", OpenBracket), Lexem("~", UnOperator), Lexem("abs", Function, DBL_MAX, -1, my_abs), Lexem("(", OpenBracket),
		Lexem("x_2", Variable), Lexem("-", Operator), Lexem("17", Constant, 17), Lexem(")", ClosedBracket),
		Lexem("+", Operator), Lexem("23", Constant, 23), Lexem(")", ClosedBracket) };
	ASSERT_EQ(list, result);
}

TEST(TestParserLib, correct_parsing_3) {
	std::string s = "||x| - |y||";

	ASSERT_NO_THROW(Parser::parse(s));
	List<Lexem> list = Parser::parse(s);

	List<Lexem> result = { Lexem("abs", Function, DBL_MAX, -1, my_abs), Lexem("(", OpenBracket), 
		Lexem("abs", Function, DBL_MAX, -1, my_abs), Lexem("(", OpenBracket), Lexem("x", Variable), 
		Lexem(")", ClosedBracket), Lexem("-", Operator), Lexem("abs", Function, DBL_MAX, -1, my_abs), 
		Lexem("(", OpenBracket), Lexem("y", Variable), Lexem(")", ClosedBracket), Lexem(")", ClosedBracket) };
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
	std::string s3 = "sin()";

	ASSERT_THROW(Parser::parse(s), std::logic_error);
	ASSERT_THROW(Parser::parse(s2), std::logic_error);
	ASSERT_THROW(Parser::parse(s3), std::logic_error);
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
		Lexem("abs", Function, DBL_MAX, -1, my_abs), Lexem("(", OpenBracket), Lexem("x", Variable), 
		Lexem("+", Operator), Lexem("z_2", Variable), Lexem(")", ClosedBracket), Lexem("]", ClosedBracket)
	};
	ASSERT_EQ(list, result);
}

TEST(TestParserLib, function_with_abs) {
	std::string s = "sin(|x|)";

	ASSERT_NO_THROW(Parser::parse(s));
	List<Lexem> list = Parser::parse(s);

	List<Lexem> result = {
		Lexem("sin", Function, DBL_MAX, -1, my_sin), Lexem("(", OpenBracket), 
		Lexem("abs", Function, DBL_MAX, -1, my_abs), Lexem("(", OpenBracket),
		Lexem("x", Variable), Lexem(")", ClosedBracket), Lexem(")", ClosedBracket)
	};
	ASSERT_EQ(list, result);
}

TEST(TestExpressionLib, try_create) {
	std::string s = "21 * (x + 33 * y)";
	ASSERT_NO_THROW(Expression e(s));
}

TEST(TestExpressionLib, correct_calculate_expressions) {
	Expression e("2 * (3 + 4) - 5 / 2");
	ASSERT_DOUBLE_EQ(e.calculate(), 11.5);

	Expression e2("sin(0) + cos(0) * 2");
	ASSERT_DOUBLE_EQ(e2.calculate(), 2.0);

	Expression e3("|x| + |y|");
	e3.set_variables("x", -5);
	e3.set_variables("y", -3);
	ASSERT_DOUBLE_EQ(e3.calculate(), 8.0);

	Expression e4("||x_1| - |x_2||");
	e4.set_variables("x_1", -7);
	e4.set_variables("x_2", -10);
	ASSERT_DOUBLE_EQ(e4.calculate(), 3.0);
}

TEST(TestExpressionLib, correct_calculate_float) {
	Expression e("3.14 * x");
	e.set_variables("x", 2.0);
	ASSERT_DOUBLE_EQ(e.calculate(), 6.28);

	Expression e2("x_1 / 0.5");
	e2.set_variables("x_1", 1.5);
	ASSERT_DOUBLE_EQ(e2.calculate(), 3.0);
}

TEST(TestExpressionLib, correct_different_brackets) {
	Expression e("( [ { x + y } * 2 ] - z )");
	e.set_variables("x", 3);
	e.set_variables("y", 4);
	e.set_variables("z", 5);
	ASSERT_DOUBLE_EQ(e.calculate(), 9.0);
}

TEST(TestExpressionLib, throw_uncorrect_calculate) {
	Expression e1("5 / 0");
	ASSERT_THROW(e1.calculate(), std::logic_error);

	Expression e2("x + 5");
	ASSERT_THROW(e2.calculate(), std::logic_error);

	e2.set_variables("x", 3);
	ASSERT_DOUBLE_EQ(e2.calculate(), 8.0);
}

TEST(TestExpressionLib, correct_calculate) {
	Expression e("a * b + c");
	e.set_variables("a", 2);
	e.set_variables("b", 3);
	e.set_variables("c", 4);
	ASSERT_DOUBLE_EQ(e.calculate(), 10.0);

	e.set_variables("a", 5);
	e.set_variables("b", 6);
	e.set_variables("c", 7);
	ASSERT_DOUBLE_EQ(e.calculate(), 37.0);
}

TEST(TestExpressionLib, correct_calculate_2) {
	Expression e("2 ^ 3 + 3 ^ 2 - 4 * 5 / 2");
	ASSERT_DOUBLE_EQ(e.calculate(), 7);

	Expression e2("|x - y| * (a + b) / c");
	e2.set_variables("x", 10);
	e2.set_variables("y", 7);
	e2.set_variables("a", 3);
	e2.set_variables("b", 2);
	e2.set_variables("c", 5);
	ASSERT_DOUBLE_EQ(e2.calculate(), 3);
}

TEST(TestExpressionLib, correct_calculate_unary_minus) {
	Expression e("-(-x)");
	e.set_variables("x", 5);
	ASSERT_DOUBLE_EQ(e.calculate(), 5.0);

	Expression e2("(-x) * (-y)");
	e2.set_variables("x", 3);
	e2.set_variables("y", 4);
	ASSERT_DOUBLE_EQ(e2.calculate(), 12.0);

	Expression e3("-x * (-y)");
	e3.set_variables("x", 3);
	e3.set_variables("y", 4);
	ASSERT_DOUBLE_EQ(e3.calculate(), 12.0);

	Expression e4("-(x + y) * (-z)");
	e4.set_variables("x", 2);
	e4.set_variables("y", 3);
	e4.set_variables("z", 4);
	ASSERT_DOUBLE_EQ(e4.calculate(), 20.0);

	Expression e5("x^(-y)");
	e5.set_variables("x", 2);
	e5.set_variables("y", 2);
	ASSERT_DOUBLE_EQ(e5.calculate(), 0.25);
}

TEST(TestExpressionLib, correct_calculate_absolute_value) {
	Expression e("||x| - |-y||");
	e.set_variables("x", -3);
	e.set_variables("y", 5);
	ASSERT_DOUBLE_EQ(e.calculate(), 2);

	Expression e2("|x - y| - |y - x|");
	e2.set_variables("x", -10);
	e2.set_variables("y", 7);
	ASSERT_DOUBLE_EQ(e2.calculate(), 0.0);
}

TEST(TestExpressionLib, correct_calculate_operator_precedence) {
	Expression e("x + y * z ^ w");
	e.set_variables("x", 1);
	e.set_variables("y", 2);
	e.set_variables("z", 3);
	e.set_variables("w", 2);
	ASSERT_DOUBLE_EQ(e.calculate(), 19.0);

	Expression e2("x * y + z / w - t");
	e2.set_variables("x", 3);
	e2.set_variables("y", 4);
	e2.set_variables("z", 10);
	e2.set_variables("w", 2);
	e2.set_variables("t", 5);
	ASSERT_DOUBLE_EQ(e2.calculate(), 12.0);
}

TEST(TestExpressionLib, correct_calculate_same_precedence) {
	Expression e("10 - 3 - 2");
	ASSERT_DOUBLE_EQ(e.calculate(), 5.0);

	Expression e2("12 / 3 / 2");
	ASSERT_DOUBLE_EQ(e2.calculate(), 2.0);
}

TEST(TestExpressionLib, correct_calculate_power_precedence) {
	Expression e1("-2^2");
	ASSERT_DOUBLE_EQ(e1.calculate(), -4.0);
}
