#pragma once

#include <iostream>
#include "../lib_stack/stack.h"

bool check_brackets(std::string str);
void read_expression(std::string expression);
bool is_math_operation(char item);
bool is_number(char item);
bool is_variable(char item);