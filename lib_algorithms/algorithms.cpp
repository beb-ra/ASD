#include "algorithms.h"

bool check_breckets(std::string str) {
	Stack<char> stack(30);
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '(' || str[i] == '[' || str[i] == '{') {
			stack.push(str[i]);
		}
		else if (str[i] == ')') {
			if (stack.is_empty()) return false;
			if (stack.top() == '(') {
				stack.pop();
			}
			else return false;
		}
		else if (str[i] == ']') {
			if (stack.is_empty()) return false;
			if (stack.top() == '[') {
				stack.pop();
			}
			else return false;
		}
		else if (str[i] == '}') {
			if (stack.is_empty()) return false;
			if (stack.top() == '{') {
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
	return item >= 'a' && item <= 'z';
}

void read_expression(std::string str) {
	if (!check_breckets(str)) 
		throw std::invalid_argument("Missing opened brecket");

	Stack<std::string> stack_nums(50);
	Stack<std::string> stack_operations(50);

	/*
	for (int i = 0; i < str.length(); i++) {
		if (is_number(str[i])) {
			if (!stack_operations.is_empty()) {
				stack_operations.pop();
				if (stack_nums.is_empty())
					throw std::logic_error("Missing first operand");
				else
					stack_nums.pop();
			}
		}
	}
	*/

	int i = 0;
	std::string num;
	while(i != str.length() - 1) {
		if (is_number(str[i]) || is_variable(str[i])) {
			if (!stack_operations.is_empty()) {
				stack_operations.pop();
				if (stack_nums.is_empty())
					throw std::logic_error("Missing first operand");
				else {
					stack_nums.pop();
					continue;
				}
			}
			if (is_number(str[i])) {
				num = "";
				while (is_number(str[i])) {
					num += str[i];
				}
				stack_nums.push(num);
			}
			if (is_variable(str[i])) {
				stack_nums.push(str[i] + "");
			}
		}
		
	}
}