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
    char getMatchingBracket(char bracket) {
        switch (bracket) {
        case ')': return '(';
        case ']': return '[';
        case '}': return '{';
        }
    }

    List<Lexem> parse(std::string expression) {
        List<Lexem> lexems;
        State currentState = START;
        std::string currentToken;
        LStack<char> brackets;

        // добавить состояние AFTER_OPERAND

        for (size_t i = 0; i < expression.length(); i++) {
            char c = expression[i];
            if (c == ' ') continue;

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
                    brackets.push(c);
                    lexems.push_back(Lexem(std::string(1, c), getBracketType(c, true)));
                    currentState = AFTER_OPEN_BRACKET;
                }
                else if (c == '|') {
                    brackets.push(c);
                    lexems.push_back(Lexem("abs", Function));
                    lexems.push_back(Lexem("(", OpenBracket));
                    currentState = AFTER_OPEN_BRACKET;
                }
                else if (isOperator(c)) {
                    if (c == '-' && lexems.is_empty()) {
                        lexems.push_back(Lexem("~", UnOperator));
                        currentState = AFTER_UN_OPERATOR;
                    }
                    else {
                        throw std::logic_error("Unexpected operator at position " + std::to_string(i));
                    }
                }
                else {
                    throw std::logic_error("Unknown symbol at position " + std::to_string(i));
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
                        if (brackets.is_empty() || brackets.top() == getMatchingBracket(c)) {
                            brackets.pop();
                        }
                        else {
                            throw std::logic_error("Wrong type of bracket " + std::to_string(i));
                        }
                        lexems.push_back(Lexem(std::string(1, c), getBracketType(c, false)));
                        currentState = AFTER_CLOSED_BRACKET;
                    }
                    else if (c == '|') {
                        if (brackets.is_empty() || brackets.top() == '|') {
                            brackets.pop();
                        }
                        else {
                            throw std::logic_error("Wrong type of bracket " + std::to_string(i));
                        }
                        lexems.push_back(Lexem(")", ClosedBracket));
                        currentState = AFTER_CLOSED_BRACKET;
                    }
                    else if (isOperator(c)) {
                        lexems.push_back(Lexem(std::string(1, c), Operator));
                        currentState = AFTER_OPERATOR;
                    }
                    else {
                        //currentState = AFTER_CLOSED_BRACKET;
                        throw std::logic_error("There is no operator after the operand: " + std::to_string(i));
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
                    else if (c == ')' || c == ']' || c == '}') {
                        if (brackets.is_empty() || brackets.top() == getMatchingBracket(c)) {
                            brackets.pop();
                        }
                        else {
                            throw std::logic_error("Wrong type of bracket " + std::to_string(i));
                        }
                        currentState = AFTER_CLOSED_BRACKET;
                        lexems.push_back(Lexem(std::string(1, c), ClosedBracket));
                    }
                    else if (c == '|') {
                        if (brackets.is_empty() || brackets.top() == '|') {
                            brackets.pop();
                        }
                        else {
                            throw std::logic_error("Wrong type of bracket " + std::to_string(i));
                        }
                        lexems.push_back(Lexem(")", ClosedBracket));
                        currentState = AFTER_CLOSED_BRACKET;
                    }
                    else {
                        throw std::logic_error("There is no operator after the operand: " + std::to_string(i));
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
                    brackets.push(c);
                    lexems.push_back(Lexem(std::string(1, c), getBracketType(c, true)));
                    currentState = AFTER_OPEN_BRACKET;
                }
                else if (c == '|') {
                    brackets.push(c);
                    lexems.push_back(Lexem("abs", Function));
                    lexems.push_back(Lexem("(", OpenBracket));
                    currentState = AFTER_OPEN_BRACKET;
                }
                else if (c == '-' && expression[i - 1] != ' ') {
                    //lexems.push_back(Lexem("~", UnOperator));
                    //currentState = AFTER_UN_OPERATOR;
                    throw std::logic_error("Unexpected unary minus after the operator: " + std::to_string(i));
                }
                else {
                    throw std::logic_error("There is no operand after the operator: " + std::to_string(i));
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
                    brackets.push(c);
                    lexems.push_back(Lexem(std::string(1, c), getBracketType(c, true)));
                    currentState = AFTER_OPEN_BRACKET;
                }
                else if (c == '|') {
                    brackets.push(c);
                    lexems.push_back(Lexem("abs", Function));
                    lexems.push_back(Lexem("(", OpenBracket));
                    currentState = AFTER_OPEN_BRACKET;
                }
                else {
                    throw std::logic_error("There is no operand after the unary operator: " + std::to_string(i));
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
                    brackets.push(c);
                    lexems.push_back(Lexem(std::string(1, c), getBracketType(c, true)));
                }
                else if (c == '|') {
                    brackets.push(c);
                    lexems.push_back(Lexem("abs", Function));
                    lexems.push_back(Lexem("(", OpenBracket));
                    currentState = AFTER_OPEN_BRACKET;
                }
                else if (c == '-') {
                    lexems.push_back(Lexem("~", UnOperator));
                    currentState = AFTER_UN_OPERATOR;
                }
                else {
                    throw std::logic_error("There is no operand after the open bracket: " + std::to_string(i));
                }
                break;

            case AFTER_CLOSED_BRACKET:
                if (c == ')' || c == ']' || c == '}') {
                    if (brackets.is_empty() || brackets.top() == getMatchingBracket(c)) {
                        brackets.pop();
                    }
                    else {
                        throw std::logic_error("Wrong type of bracket " + std::to_string(i));
                    }
                    lexems.push_back(Lexem(std::string(1, c), getBracketType(c, false)));
                }
                else if (c == '|') {
                    if (brackets.is_empty() || brackets.top() == '|') {
                        brackets.pop();
                    }
                    else {
                        throw std::logic_error("Wrong type of bracket " + std::to_string(i));
                    }
                    lexems.push_back(Lexem(")", ClosedBracket));
                    currentState = AFTER_CLOSED_BRACKET;
                }
                else if (isOperator(c)) {
                    lexems.push_back(Lexem(std::string(1, c), Operator));
                    currentState = AFTER_OPERATOR;
                }
                else {
                    throw std::logic_error("There is no operator after the closed bracket: " + std::to_string(i));
                }
                break;

            case AFTER_FUNCTION:
                if (c == '(' || c == '[' || c == '{') {
                    brackets.push(c);
                    lexems.push_back(Lexem(std::string(1, c), OpenBracket));
                    currentState = AFTER_OPEN_BRACKET;
                }
                else if (c == '|') {
                    brackets.push(c);
                    lexems.push_back(Lexem("abs", Function));
                    lexems.push_back(Lexem("(", OpenBracket));
                    currentState = AFTER_OPEN_BRACKET;
                }
                else {
                    throw std::logic_error("There is no open bracket after the function: " + std::to_string(i));
                }
                break;

            case ERROR:
                throw std::logic_error("Parser error at position " + std::to_string(i));
            }
        }

        if (!brackets.is_empty()) {
            throw std::logic_error("Missing closing bracket in the end");
        }

        if (!currentToken.empty()) {
            if (currentState == IN_NUMBER) {
                lexems.push_back(Lexem(currentToken, Constant, std::stod(currentToken)));
            }
            else if (currentState == IN_VARIABLE) {
                if (isFunction(currentToken)) {
                    lexems.push_back(Lexem(currentToken, Function));
                    currentState = AFTER_FUNCTION;
                }
                else {
                    lexems.push_back(Lexem(currentToken, Variable));
                }
            }
        }

        if (currentState == AFTER_OPERATOR) {
            throw std::logic_error("Expression ends with operator");
        }
        else if (currentState == AFTER_UN_OPERATOR) {
            throw std::logic_error("Expression ends with unary operator");
        }
        else if (currentState == AFTER_OPEN_BRACKET || currentState == AFTER_FUNCTION) {
            throw std::logic_error("Expression ends with unclosed bracket or function");
        }
        else if (currentState == START) {
            throw std::logic_error("Expression is empty");
        }

        return lexems;
    }
}

