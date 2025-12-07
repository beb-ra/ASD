#include <iostream>
#include <iomanip>
#include "../lib_tvector/tvector.h"
#include "../lib_expression/expression.h"
#include "../lib_parser/parser.h"

#define MENU_SIZE 5
#define EXIT 0
#define ADD_EXP 1
#define DELETE 2
#define SET_VARS 3
#define CALCULATE 4

void print_start() {
    return;
}

std::string get_string() {
    return "b";
}

Expression create_expression(std::string s) {
    try {
        return Expression(s);
    }
    catch (const std::logic_error& e) {
        std::cerr << e.what() << std::endl;
    }
}

void set_variables(Expression ex) {
    return;
}

int calculate_expression(Expression ex) {
    return 0;
}

void print_calculate_result(int result) {
    return;
}

size_t select_index() {
    return 0;
}

size_t select_option(size_t n) {
    return 1;
}

void print_menu() {
    return;
}

int main() {
    /*
    print_start();
    std::string s = get_string();
    Expression expression = create_expression(s);
    TVector<Expression> expressions;
    expressions.push_back(expression);
    size_t ind;
    int result;

    while (true) {
        print_menu();
        size_t selected = select_option(MENU_SIZE);
        switch (selected) {
        case EXIT: return 0;
        case ADD_EXP: 
            s = get_string();
            expression = create_expression(s);
            expressions.push_back(expression);
            break;
        case DELETE: 
            ind = select_index();
            expressions.erase(ind);
            break;
        case SET_VARS: 
            // try catch
            set_variables(expression);
            break;
        case CALCULATE: 
            result = calculate_expression(expression);
            print_calculate_result(result);
            break;
        }
    }
    */
    /*
    std::string s = "   ";
    try {
        Expression e(s);
        e.print();
        double result = e.calculate();
        std::cout << result << std::endl;
    }
    catch (const std::logic_error& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
    */
    
    //std::string s = "21 * (x + 33 * y)";
    //std::string s = "x_1 * sin(y + 7) + y * (-|x_2 - 17| + 23)";
    //std::string s = "||x| - |y||";
}

