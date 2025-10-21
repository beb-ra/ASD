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
	if (stack.is_empty()) return true;
	return false;
}