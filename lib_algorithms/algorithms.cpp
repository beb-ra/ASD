#include <cmath>
#include "algorithms.h"

bool check_brackets(std::string str) {
    Stack<char> stack(30);
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '(' || str[i] == '[' || str[i] == '{') {
            stack.push(str[i]);
        }

        else if (str[i] == ')' || str[i] == ']' || str[i] == '}') {
            if (stack.is_empty()) return false;

            char expected_bracket;
            switch (str[i]) {
            case ')': expected_bracket = '('; break;
            case ']': expected_bracket = '['; break;
            case '}': expected_bracket = '{'; break;
            }

            if (stack.top() == expected_bracket) {
                stack.pop();
            }
            else return false;
        }
    }
    return stack.is_empty();
}

bool is_math_operation(char item) {
    return item == '+' || item == '-' || item == '*' || item == '/' || item == '^';
}

bool is_number(char item) {
    return item >= '0' && item <= '9';
}

bool is_variable(char item) {
    return (item >= 'a' && item <= 'z') || (item >= 'A' && item <= 'Z');
}

bool is_open_bracket(char item) {
    return item == '(' || item == '[' || item == '{';
}

bool is_close_bracket(char item) {
    return item == ')' || item == ']' || item == '}';
}

bool is_unary_minus(const std::string& str, int pos) {
    if (str[pos] != '-') return false;
    if (pos == 0) return true;

    int prev = pos - 1;
    while (prev >= 0 && str[prev] == ' ') prev--;

    return prev < 0 || is_open_bracket(str[prev]);
}

void read_expression(std::string str) {
    Stack<char> brackets_stack(50);

    int i = 0;
    bool expecting_value = true;

    while (i < str.length()) {
        if (str[i] == ' ') {
            i++;
            continue;
        }

        if (is_open_bracket(str[i])) {
            if (!expecting_value) {
                throw std::logic_error("Missing operation before opening bracket");
            }
            brackets_stack.push(str[i]);
            expecting_value = true;
            i++;
            continue;
        }

        if (is_close_bracket(str[i])) {
            if (expecting_value) {
                throw std::logic_error("Missing operand before closing bracket");
            }
            if (brackets_stack.is_empty()) {
                throw std::logic_error("Unexpected closing bracket");
            }

            char expected_bracket;
            switch (str[i]) {
            case ')': expected_bracket = '('; break;
            case ']': expected_bracket = '['; break;
            case '}': expected_bracket = '{'; break;
            }

            if (brackets_stack.top() != expected_bracket) {
                throw std::logic_error("Mismatched brackets");
            }
            brackets_stack.pop();
            expecting_value = false;
            i++;
            continue;
        }

        if (is_number(str[i])) {
            if (!expecting_value) {
                throw std::logic_error("Missing operation between values");
            }
            while (i < str.length() && is_number(str[i])) {
                i++;
            }
            expecting_value = false;
            continue;
        }

        if (is_variable(str[i])) {
            if (!expecting_value) {
                throw std::logic_error("Missing operation between values");
            }
            while (i < str.length() && is_variable(str[i])) {
                i++;
            }
            expecting_value = false;
            continue;
        }

        if (is_math_operation(str[i])) {
            if (is_unary_minus(str, i) && expecting_value) {
                i++;
                continue;
            }
            else if (expecting_value) {
                throw std::logic_error("Missing value before operation");
            }
            expecting_value = true;
            i++;
            continue;
        }
        throw std::logic_error("Invalid character in expression");
    }

    if (!brackets_stack.is_empty()) {
        throw std::logic_error("Missing closed bracket");
    }
    if (expecting_value) {
        throw std::logic_error("Missing value");
    }
}

#define EPSILON 0.00000001
#define PI 3.14

double my_sin(double x) {
    double rad = convert_to_radians(x);
    rad = fmod(rad, 2 * PI);
    if (rad > PI) rad -= 2 * PI;
    else if (rad < -PI) rad += 2 * PI;

    double res = rad;
    double term = rad;
    int n = 1;
    for (; abs(term) > EPSILON; n++) {
        term = -term * rad * rad / ((2 * n + 1) * (2 * n));
        res += term;
    }
    return res;
}

double my_cos(double x) {
    double rad = convert_to_radians(x);
    rad = fmod(rad, 2 * PI);
    if (rad > PI) rad -= 2 * PI;
    else if (rad < -PI) rad += 2 * PI;

    double res = 1.0;
    double term = 1.0;
    int n = 1;
    for (; abs(term) > EPSILON; n++) {
        term = -term * rad * rad / ((2 * n) * (2 * n - 1));
        res += term;
    }
    return res;
}

double my_tg(double x) {
    x = fmod(x, 360.0);
    if (x < 0) x += 360.0;

    if (my_abs(x - 90.0) < 1e-4 || my_abs(x - 270.0) < 1e-4)
        throw std::invalid_argument("Division by zero");
    return my_sin(x) / my_cos(x);
}

double my_abs(double x) {
	return x < 0 ? -x : x;
}

double convert_to_radians(double x) {
    return (x * PI) / 180;
}
