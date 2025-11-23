#include <iostream>
#include <iomanip>
#include "../lib_expression/expression.h"
#include "../lib_parser/parser.h"

int main() {
    std::string s = "21 * (x + 33 * y)";
    Expression e(s);
    e.print();

    e.set_variables(1.0, 2.0);
    double result = e.calculate();
    //std::cout << "Result for x=1, y=2: " << result << std::endl;

    /*
    std::string expression;
    std::cin >> expression;
    Expression expr(Parse::parse(expression));
    expr.set_variables("x", 5);  // или expr.set_variables(5, 8); - для x, y
    expr.calculate();  // через стек
    */
    return 0;
}

