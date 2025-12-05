#include <iostream>
#include <iomanip>
#include "../lib_expression/expression.h"
#include "../lib_parser/parser.h"

int main() {
    //std::string s = "21 * (x + 33 * y)";
    //std::string s = "x_1 * sin(y + 7) + y * (-|x_2 - 17| + 23)";
    //std::string s = "(-|x_2 - 17| + 23)";
    std::string s = "||x| - |y||";
    List<Lexem> _lexems = Parser::parse(s);
    Expression e(s);
    e.print();

    e.set_variables("x", -2);
    e.set_variables("y", -3);
    double result = e.calculate();
    std::cout << result << std::endl;
    /*
    e.set_variables("x_1", 1.0);
    e.set_variables("y", -7);
    e.set_variables("x_2", 16);
    double result = e.calculate();
    std::cout << result << std::endl;
    */

    /*
    std::string expression;
    std::cin >> expression;
    Expression expr(Parse::parse(expression));
    expr.set_variables("x", 5);  // или expr.set_variables(5, 8); - для x, y
    expr.calculate();  // через стек
    */
    return 0;
}

