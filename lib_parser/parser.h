#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <stdexcept>
#include <cstdlib>
#include <sstream>
#include "../lib_list/list.h"
#include "../lib_lexem/lexem.h"
#include "../lib_lstack/lstack.h"

namespace Parser {
    enum State {
        START,
        IN_NUMBER,
        IN_VARIABLE,
        IN_FUNCTION,
        AFTER_OPERATOR,
        AFTER_UN_OPERATOR,
        AFTER_OPEN_BRACKET,
        AFTER_CLOSED_BRACKET,
        AFTER_FUNCTION,
        ERROR
    };

    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
    }
    bool isBracket(char c) {
        return c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}';
    }
    bool isClosedBracket(char c) {
        return c == ')' || c == ']' || c == '}';
    }
    bool isValidVariableChar(char c) {
        return std::isalnum(c) || c == '_';
    }
    bool isFunction(const std::string& str) {
        return str == "sin" || str == "cos" || str == "tg";
    }
    TypeLexem getBracketType(char bracket, bool isOpen) {
        return isOpen ? OpenBracket : ClosedBracket;
    }
    void validateExpression(const std::string& expression) {
        if (expression.empty()) {
            throw std::runtime_error("Empty expression");
        }

        int bracketBalance = 0;
        int absBalance = 0;

        for (size_t i = 0; i < expression.length(); i++) {
            char c = expression[i];

            if (c == '(' || c == '[' || c == '{') {
                bracketBalance++;
            }
            else if (c == ')' || c == ']' || c == '}') {
                bracketBalance--;
                if (bracketBalance < 0) {
                    throw std::runtime_error("Unbalanced brackets at position " + std::to_string(i));
                }
            }
            else if (c == '|') {
                absBalance = 1 - absBalance;
            }

            if (!std::isdigit(c) && !std::isalpha(c) && c != '_' &&
                !isOperator(c) && !isBracket(c) && c != '.' && c != '|' && c != ' ') {
                throw std::runtime_error("Invalid character '" + std::string(1, c) + "' at position " + std::to_string(i));
            }
        }

        if (bracketBalance != 0) {
            throw std::runtime_error("Unbalanced brackets");
        }

        if (absBalance != 0) {
            throw std::runtime_error("Unbalanced absolute value bars");
        }
    }

    List<Lexem> parse(std::string expression) {
        std::string cleaned_expr;
        for (char c : expression) {
            if (!std::isspace(c)) {
                cleaned_expr += c;
            }
        }

        expression = cleaned_expr;

        List<Lexem> lexems;
        State currentState = START;
        std::string currentToken;

        for (size_t i = 0; i < expression.length(); i++) {
            char c = expression[i];

            //std::cout << "\ni: " << i << "  c: " << c << std::endl;
            //lexems.print();

            switch (currentState) {
            case START:
                if (std::isdigit(c)) {
                    currentToken += c;
                    currentState = IN_NUMBER;
                }
                else if (std::isalpha(c) || c == '_') {
                    currentToken += c;
                    currentState = IN_VARIABLE;
                }
                else if (c == '(' || c == '[' || c == '{') {
                    lexems.push_back(Lexem(std::string(1, c), getBracketType(c, true)));
                    currentState = AFTER_OPEN_BRACKET;
                }
                else if (c == '|') {
                    lexems.push_back(Lexem("|", Abs));
                    currentState = AFTER_OPEN_BRACKET;
                }
                else if (isOperator(c)) {
                    if (c == '-' && lexems.is_empty()) {
                        lexems.push_back(Lexem("-", UnOperator));
                        currentState = AFTER_UN_OPERATOR;
                    }
                    else {
                        throw std::runtime_error("Unexpected operator at position " + std::to_string(i));
                    }
                }
                else if (c != ' ') {
                    throw std::runtime_error("Unexpected character at position " + std::to_string(i));
                }
                break;

            case IN_NUMBER:
                if (std::isdigit(c) || c == '.') {
                    currentToken += c;
                }
                else {
                    lexems.push_back(Lexem(currentToken, Constant, std::stod(currentToken)));
                    currentToken.clear();

                    if (c == ')' || c == ']' || c == '}') {
                        lexems.push_back(Lexem(std::string(1, c), getBracketType(c, false)));
                        currentState = AFTER_CLOSED_BRACKET;
                    }
                    else if (c == '|') {
                        lexems.push_back(Lexem("|", Abs));
                        currentState = AFTER_CLOSED_BRACKET;
                    }
                    else if (isOperator(c)) {
                        lexems.push_back(Lexem(std::string(1, c), Operator));
                        currentState = AFTER_OPERATOR;
                    }
                    else if (c != ' ') {
                        throw std::runtime_error("Unexpected character after number at position " + std::to_string(i));
                    }
                    else {
                        currentState = AFTER_CLOSED_BRACKET;
                    }
                }
                break;

            case IN_VARIABLE:
                if (isFunction(currentToken)) {
                    lexems.push_back(Lexem(currentToken, Function));
                    currentState = AFTER_FUNCTION;
                    currentToken.clear();
                    i--;
                    break;
                }
                if (isValidVariableChar(c)) {
                    currentToken += c;
                    break;
                }
                else {
                    lexems.push_back(Lexem(currentToken, Variable));
                    if (isOperator(c)) {
                        currentState = AFTER_OPERATOR;
                        lexems.push_back(Lexem(std::string(1, c), Operator));
                    }
                    else if (isClosedBracket(c)) {
                        currentState = AFTER_CLOSED_BRACKET;
                        // проверка на нужную скобку через стек
                        lexems.push_back(Lexem(std::string(1, c), Operator));
                    }
                    currentToken.clear();
                }
                break;

            case AFTER_OPERATOR:
                if (std::isdigit(c)) {
                    currentToken += c;
                    currentState = IN_NUMBER;
                }
                else if (std::isalpha(c) || c == '_') {
                    currentToken += c;
                    currentState = IN_VARIABLE;
                }
                else if (c == '(' || c == '[' || c == '{') {
                    lexems.push_back(Lexem(std::string(1, c), getBracketType(c, true)));
                    currentState = AFTER_OPEN_BRACKET;
                }
                else if (c == '|') {
                    lexems.push_back(Lexem("|", Abs));
                    currentState = AFTER_OPEN_BRACKET;
                }
                else if (c == '-' && expression[i - 1] != ' ') {
                    lexems.push_back(Lexem("-", UnOperator));
                    currentState = AFTER_UN_OPERATOR;
                }
                else if (c != ' ') {
                    throw std::runtime_error("Unexpected character after operator at position " + std::to_string(i));
                }
                break;

            case AFTER_UN_OPERATOR:
                if (std::isdigit(c)) {
                    currentToken += c;
                    currentState = IN_NUMBER;
                }
                else if (std::isalpha(c) || c == '_') {
                    currentToken += c;
                    currentState = IN_VARIABLE;
                }
                else if (c == '(' || c == '[' || c == '{') {
                    lexems.push_back(Lexem(std::string(1, c), getBracketType(c, true)));
                    currentState = AFTER_OPEN_BRACKET;
                }
                else if (c == '|') {
                    lexems.push_back(Lexem("|", Abs));
                    currentState = AFTER_OPEN_BRACKET;
                }
                else if (c != ' ') {
                    throw std::runtime_error("Unexpected character after unary operator at position " + std::to_string(i));
                }
                break;

            case AFTER_OPEN_BRACKET:
                if (std::isdigit(c)) {
                    currentToken += c;
                    currentState = IN_NUMBER;
                }
                else if (std::isalpha(c) || c == '_') {
                    currentToken += c;
                    currentState = IN_VARIABLE;
                }
                else if (c == '(' || c == '[' || c == '{') {
                    lexems.push_back(Lexem(std::string(1, c), getBracketType(c, true)));
                }
                else if (c == '|') {
                    lexems.push_back(Lexem("|", Abs));
                }
                else if (c == '-') {
                    lexems.push_back(Lexem("-", UnOperator));
                    currentState = AFTER_UN_OPERATOR;
                }
                else if (c != ' ') {
                    throw std::runtime_error("Unexpected character after opening bracket at position " + std::to_string(i));
                }
                break;

            case AFTER_CLOSED_BRACKET:
                if (c == ')' || c == ']' || c == '}') {
                    lexems.push_back(Lexem(std::string(1, c), getBracketType(c, false)));
                }
                else if (c == '|') {
                    lexems.push_back(Lexem("|", Abs));
                }
                else if (isOperator(c)) {
                    lexems.push_back(Lexem(std::string(1, c), Operator));
                    currentState = AFTER_OPERATOR;
                }
                else if (c != ' ') {
                    throw std::runtime_error("Unexpected character after closing bracket at position " + std::to_string(i));
                }
                break;

            case AFTER_FUNCTION:
                if (c == '(' || c == '[' || c == '{') {
                    lexems.push_back(Lexem(std::string(1, c), OpenBracket));
                    currentState = AFTER_OPEN_BRACKET;
                }
                else if (c != ' ') {
                    throw std::runtime_error("Expected opening bracket after function at position " + std::to_string(i));
                }
                break;

            case ERROR:
                throw std::runtime_error("Parser error at position " + std::to_string(i));
            }
        }

        if (!currentToken.empty()) {
            if (currentState == IN_NUMBER) {
                lexems.push_back(Lexem(currentToken, Constant, std::stod(currentToken)));
            }
            else if (currentState == IN_VARIABLE) {
                if (isFunction(currentToken)) {
                    lexems.push_back(Lexem(currentToken, Function));
                }
                else {
                    lexems.push_back(Lexem(currentToken, Variable));
                }
            }
        }
        return lexems;
    }
}

double my_sin(double x) { return sin(x); }
double my_cos(double x) { return cos(x); }
double my_tan(double x) { return tan(x); }

