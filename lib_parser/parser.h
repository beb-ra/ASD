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
#include "../lib_algorithms/algorithms.h"

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
        AFTER_OPERAND
    };

    bool is_operator(char c);
    bool is_bracket(char c);
    bool is_closed_bracket(char c);
    bool is_valid_variable_char(char c);
    bool is_function(const std::string& str);
    TypeLexem get_bracket_type(char bracket, bool isOpen);
    char get_matching_bracket(char bracket);
    void print_error(const std::string& expression, std::string message, size_t pos);

    void handle_start(List<Lexem>& lexems, State& currentState, std::string& currentToken,
        LStack<char>& brackets, const std::string& expression, size_t i, char c);
    void handle_in_number(List<Lexem>& lexems, State& currentState, std::string& currentToken,
        LStack<char>& brackets, const std::string& expression, size_t& i, char c);
    void handle_in_variable(List<Lexem>& lexems, State& currentState, std::string& currentToken,
        LStack<char>& brackets, const std::string& expression, size_t& i, char c);
    void handle_after_operator(List<Lexem>& lexems, State& currentState, std::string& currentToken,
        LStack<char>& brackets, const std::string& expression, size_t i, char c);
    void handle_after_un_operator(List<Lexem>& lexems, State& currentState, std::string& currentToken,
        LStack<char>& brackets, const std::string& expression, size_t i, char c);
    void handle_after_open_bracket(List<Lexem>& lexems, State& currentState, std::string& currentToken,
        LStack<char>& brackets, const std::string& expression, size_t i, char c);
    void handle_after_closed_bracket(List<Lexem>& lexems, State& currentState, std::string& currentToken,
        LStack<char>& brackets, const std::string& expression, size_t i, char c);
    void handle_after_function(List<Lexem>& lexems, State& currentState, std::string& currentToken,
        LStack<char>& brackets, const std::string& expression, size_t i, char c);
    void handle_after_operand(List<Lexem>& lexems, State& currentState, std::string& currentToken,
        LStack<char>& brackets, const std::string& expression, size_t i, char c);
    void handle_remaining_token(List<Lexem>& lexems, State& currentState,
        std::string& currentToken);
    void validate_final_state(State currentState, const std::string& expression);
    List<Lexem> parse(std::string expression);
}

