#pragma once
#include <iostream>
#include <map>
#include "../lib_list/list.h"
#include "../lib_lexem/lexem.h"
#include "../lib_parser/parser.h"
//#include "../lib_algorithms/algorithms.h"

class Expression {
    List<Lexem> _lexems;
    List<Lexem> _polish_record;
    std::map<std::string, double> variables;

public:
    Expression(std::string expression) {
        _lexems = Parser::parse(expression);
        convert_to_postfix();
    }

    Expression(List<Lexem>& lexems) : _lexems(lexems) {
        convert_to_postfix();
    }

    void set_variables(const std::string& name, double value) {
        variables[name] = value;
    }

    double calculate() {
        if (_polish_record.is_empty()) {
            convert_to_postfix();
        }

        LStack<double> stack;

        for (const auto& lexem : _polish_record) {
            TypeLexem type = lexem.type;
            std::string name = lexem.name;

            switch (type) {
            case Constant:
                stack.push(lexem.value);
                break;

            case Variable:
                if (variables.find(name) == variables.end()) {
                    throw std::runtime_error("Undefined variable: " + name);
                }
                stack.push(variables[name]);
                break;

            case Operator: {
                if (stack.size() < 2) {
                    throw std::runtime_error("Not enough operands for operator: " + name);
                }
                double right = stack.top(); stack.pop();
                double left = stack.top(); stack.pop();

                if (name == "+") stack.push(left + right);
                else if (name == "-") stack.push(left - right);
                else if (name == "*") stack.push(left * right);
                else if (name == "/") {
                    if (right == 0) throw std::runtime_error("Division by zero");
                    stack.push(left / right);
                }
                else if (name == "^") stack.push(std::pow(left, right));
                break;
            }

            case UnOperator:
                if (stack.is_empty()) {
                    throw std::runtime_error("Not enough operands for unary operator: " + name);
                }
                if (name == "~") {
                    double val = stack.top(); stack.pop();
                    stack.push(-val);
                }
                break;

            case Function: {
                if (stack.is_empty()) {
                    throw std::runtime_error("Not enough operands for function: " + name);
                }
                double val = stack.top(); stack.pop();

                if (name == "sin") stack.push(std::sin(val));
                else if (name == "cos") stack.push(std::cos(val));
                else if (name == "tg") stack.push(std::tan(val));
                else if (name == "abs") stack.push(std::abs(val));
                break;
            }

            default:
                break;
            }
        }

        if (stack.size() != 1) {
            throw std::runtime_error("Invalid expression");
        }

        return stack.top();
    }

    void print() {
        std::cout << "lexems: ";

        auto* node = _lexems.head();
        for (size_t i = 0; i < _lexems.size(); i++) {
            std::cout << node->value.name << " ";
            node = node->next;
        }
        std::cout << std::endl;

        std::cout << "polish record: ";
        node = _polish_record.head();
        for (size_t i = 0; i < _polish_record.size(); i++) {
            std::cout << node->value.name << " ";
            node = node->next;
        }
        std::cout << std::endl;
    }
private:
    void convert_to_postfix() {
        _polish_record = List<Lexem>();
        LStack<Lexem> stack;

        for (const auto& lexem : _lexems) {
            TypeLexem type = lexem.type;

            switch (type) {
            case Constant:
            case Variable:
                _polish_record.push_back(lexem);
                break;

            case OpenBracket:
                stack.push(lexem);
                break;

            case ClosedBracket:
                while (!stack.is_empty() && stack.top().type != OpenBracket) {
                    _polish_record.push_back(stack.top());
                    stack.pop();
                }
                if (stack.is_empty()) {
                    throw std::runtime_error("Unbalanced brackets");
                }
                stack.pop();
                if (!stack.is_empty() && stack.top().type == Function) {
                    _polish_record.push_back(stack.top());
                    stack.pop();
                }
                break;

            case Function:
                stack.push(lexem);
                break;

            case UnOperator:
                while (!stack.is_empty() &&
                    (stack.top().type == UnOperator ||
                        stack.top().type == Function ||
                        (stack.top().type == Operator && get_precedence(stack.top()) > get_precedence(lexem)))) {
                    _polish_record.push_back(stack.top());
                    stack.pop();
                }
                stack.push(lexem);
                break;

            case Operator:
                while (!stack.is_empty() &&
                    (stack.top().type == UnOperator ||
                        stack.top().type == Function ||
                        (stack.top().type == Operator && get_precedence(stack.top()) >= get_precedence(lexem)))) {
                    _polish_record.push_back(stack.top());
                    stack.pop();
                }
                stack.push(lexem);
                break;
            }
        }
        while (!stack.is_empty()) {
            if (stack.top().type == OpenBracket) {
                throw std::runtime_error("Unbalanced brackets");
            }
            _polish_record.push_back(stack.top());
            stack.pop();
        }
    }

    bool brackets_match(const Lexem& open, const Lexem& close) const {
        std::string open_val = open.name;
        std::string close_val = close.name;
        return (open_val == "(" && close_val == ")") ||
            (open_val == "{" && close_val == "}") ||
            (open_val == "[" && close_val == "]");
    }

    int get_precedence(const Lexem& lexem) const {
        TypeLexem type = lexem.type;
        std::string name = lexem.name;

        if (type == Function) return 4;
        if (type == UnOperator) return 3;

        if (name == "^") return 3;
        if (name == "*" || name == "/") return 2;
        if (name == "+" || name == "-") return 1;

        return 0;
    }

    bool is_opening_bracket(Lexem lexem) const {
        return lexem.type == OpenBracket;
    }

    bool is_closing_bracket(Lexem lexem) const {
        return lexem.type == ClosedBracket;
    }
};