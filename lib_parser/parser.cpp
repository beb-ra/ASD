#include "parser.h"

bool Parser::is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}
bool Parser::is_bracket(char c) {
    return c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}';
}
bool Parser::is_closed_bracket(char c) {
    return c == ')' || c == ']' || c == '}';
}
bool Parser::is_valid_variable_char(char c) {
    return std::isalnum(c) || c == '_';
}
bool Parser::is_function(const std::string& str) {
    return str == "sin" || str == "cos" || str == "tg";
}
TypeLexem Parser::get_bracket_type(char bracket, bool isOpen) {
    return isOpen ? OpenBracket : ClosedBracket;
}
char Parser::get_matching_bracket(char bracket) {
    switch (bracket) {
    case ')': return '(';
    case ']': return '[';
    case '}': return '{';
    }
}
void Parser::print_error(const std::string& expression, std::string message, size_t pos) {
    std::string s = "Input expression: " + expression + "\n";
    s += std::string(18 + pos, ' ') + "^\n";
    s += "Error in function 'Parser::parse()' at position " + std::to_string(pos + 1) + ": " + message;

    throw std::logic_error(s);
}

void Parser::handle_start(List<Lexem>& lexems, State& currentState, std::string& currentToken,
    LStack<char>& brackets, const std::string& expression, size_t i, char c) {
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
        lexems.push_back(Lexem(std::string(1, c), get_bracket_type(c, true)));
        currentState = AFTER_OPEN_BRACKET;
    }
    else if (c == '|') {
        brackets.push(c);
        lexems.push_back(Lexem("abs", Function, DBL_MAX, -1, my_abs));
        lexems.push_back(Lexem("(", OpenBracket));
        currentState = AFTER_OPEN_BRACKET;
    }
    else if (is_operator(c)) {
        if (c == '-' && lexems.is_empty()) {
            lexems.push_back(Lexem("~", UnOperator));
            currentState = AFTER_UN_OPERATOR;
        }
        else {
            print_error(expression, "Unexpected operator", i);
        }
    }
    else {
        print_error(expression, "Unknown symbol", i);
    }
}

void Parser::handle_in_number(List<Lexem>& lexems, State& currentState, std::string& currentToken,
    LStack<char>& brackets, const std::string& expression, size_t& i, char c) {
    if (std::isdigit(c) || c == '.') {
        currentToken += c;
    }
    else {
        lexems.push_back(Lexem(currentToken, Constant, std::stod(currentToken)));
        currentToken.clear();
        currentState = AFTER_OPERAND;
        i--;
    }
}

void Parser::handle_in_variable(List<Lexem>& lexems, State& currentState, std::string& currentToken,
    LStack<char>& brackets, const std::string& expression, size_t& i, char c) {
    if (is_function(currentToken)) {
        if (currentToken == "sin") {
            Lexem lex("sin", Function, DBL_MAX, -1, my_sin);
            lexems.push_back(lex);
        }
        else if (currentToken == "cos") {
            Lexem lex("cos", Function, DBL_MAX, -1, my_cos);
            lexems.push_back(lex);
        }
        else if (currentToken == "tg") {
            Lexem lex("tg", Function, DBL_MAX, -1, my_tg);
            lexems.push_back(lex);
        }
        currentState = AFTER_FUNCTION;
        currentToken.clear();
        i--;
        return;
    }

    if (is_valid_variable_char(c)) {
        currentToken += c;
    }
    else {
        lexems.push_back(Lexem(currentToken, Variable));
        currentToken.clear();
        currentState = AFTER_OPERAND;
        i--;
    }
}

void Parser::handle_after_operator(List<Lexem>& lexems, State& currentState, std::string& currentToken,
    LStack<char>& brackets, const std::string& expression, size_t i, char c) {
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
        lexems.push_back(Lexem(std::string(1, c), get_bracket_type(c, true)));
        currentState = AFTER_OPEN_BRACKET;
    }
    else if (c == '|') {
        brackets.push(c);
        lexems.push_back(Lexem("abs", Function, DBL_MAX, -1, my_abs));
        lexems.push_back(Lexem("(", OpenBracket));
        currentState = AFTER_OPEN_BRACKET;
    }
    else if (c == '-') {
        print_error(expression, "Unexpected unary minus after the operator", i);
    }
    else if (is_closed_bracket(c)) {
        print_error(expression, "Unexcepted closed bracket", i);
    }
    else if (is_operator(c)) {
        print_error(expression, "Unexcepted operator", i);
    }
    else {
        print_error(expression, "Unexcepted symbol", i);
    }
}

void Parser::handle_after_un_operator(List<Lexem>& lexems, State& currentState, std::string& currentToken,
    LStack<char>& brackets, const std::string& expression, size_t i, char c) {
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
        lexems.push_back(Lexem(std::string(1, c), get_bracket_type(c, true)));
        currentState = AFTER_OPEN_BRACKET;
    }
    else if (c == '|') {
        brackets.push(c);
        lexems.push_back(Lexem("abs", Function, DBL_MAX, -1, my_abs));
        lexems.push_back(Lexem("(", OpenBracket));
        currentState = AFTER_OPEN_BRACKET;
    }
    else if (is_closed_bracket(c)) {
        print_error(expression, "Unexcepted closed bracket", i);
    }
    else if (is_operator(c)) {
        print_error(expression, "Unexcepted operator", i);
    }
    else {
        print_error(expression, "Unexpected symbol", i);
    }
}

void Parser::handle_after_open_bracket(List<Lexem>& lexems, State& currentState, std::string& currentToken,
    LStack<char>& brackets, const std::string& expression, size_t i, char c) {
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
        lexems.push_back(Lexem(std::string(1, c), get_bracket_type(c, true)));
    }
    else if (c == '|') {
        brackets.push(c);
        lexems.push_back(Lexem("abs", Function, DBL_MAX, -1, my_abs));
        lexems.push_back(Lexem("(", OpenBracket));
        currentState = AFTER_OPEN_BRACKET;
    }
    else if (c == '-') {
        lexems.push_back(Lexem("~", UnOperator));
        currentState = AFTER_UN_OPERATOR;
    }
    else if (is_closed_bracket(c)) {
        print_error(expression, "Unexcepted closed bracket", i);
    }
    else if (is_operator(c) && c != '-') {
        print_error(expression, "Unexcepted operator", i);
    }
    else {
        print_error(expression, "Unexpected symbol", i);
    }
}

void Parser::handle_after_closed_bracket(List<Lexem>& lexems, State& currentState, std::string& currentToken,
    LStack<char>& brackets, const std::string& expression, size_t i, char c) {
    if (c == ')' || c == ']' || c == '}') {
        if (!brackets.is_empty() && brackets.top() == get_matching_bracket(c)) {
            brackets.pop();
        }
        else {
            if (brackets.is_empty())
                print_error(expression, "Unexpected closed bracket", i);
            print_error(expression, "Wrong type of bracket", i);
        }
        lexems.push_back(Lexem(std::string(1, c), get_bracket_type(c, false)));
    }
    else if (c == '|') {
        if (!brackets.is_empty() && brackets.top() == '|') {
            brackets.pop();
        }
        else {
            if (brackets.is_empty())
                print_error(expression, "Unexpected closed bracket", i);
            print_error(expression, "Wrong type of bracket", i);
        }
        lexems.push_back(Lexem(")", ClosedBracket));
        currentState = AFTER_CLOSED_BRACKET;
    }
    else if (is_operator(c)) {
        lexems.push_back(Lexem(std::string(1, c), Operator));
        currentState = AFTER_OPERATOR;
    }
    else if (is_valid_variable_char(c)) {
        print_error(expression, "Unexcepted operand", i);
    }
    else {
        print_error(expression, "Unexpected symbol", i);
    }
}

void Parser::handle_after_function(List<Lexem>& lexems, State& currentState, std::string& currentToken,
    LStack<char>& brackets, const std::string& expression, size_t i, char c) {
    if (c == '(' || c == '[' || c == '{') {
        brackets.push(c);
        lexems.push_back(Lexem(std::string(1, c), OpenBracket));
        currentState = AFTER_OPEN_BRACKET;
    }
    else if (c == '|') {
        brackets.push(c);
        lexems.push_back(Lexem("abs", Function, DBL_MAX, -1, my_abs));
        lexems.push_back(Lexem("(", OpenBracket));
        currentState = AFTER_OPEN_BRACKET;
    }
    else {
        print_error(expression, "There is no open bracket after the function", i - 1);
    }
}

void Parser::handle_after_operand(List<Lexem>& lexems, State& currentState, std::string& currentToken,
    LStack<char>& brackets, const std::string& expression, size_t i, char c) {
    if (c == ')' || c == ']' || c == '}') {
        if (!brackets.is_empty() && brackets.top() == get_matching_bracket(c)) {
            brackets.pop();
        }
        else {
            if (brackets.is_empty())
                print_error(expression, "Unexpected closed bracket", i);
            print_error(expression, "Wrong type of bracket", i);
        }
        lexems.push_back(Lexem(std::string(1, c), get_bracket_type(c, false)));
        currentState = AFTER_CLOSED_BRACKET;
    }
    else if (c == '|') {
        if (!brackets.is_empty() && brackets.top() == '|') {
            brackets.pop();
        }
        else {
            print_error(expression, "Wrong type of bracket", i);
        }
        lexems.push_back(Lexem(")", ClosedBracket));
        currentState = AFTER_CLOSED_BRACKET;
    }
    else if (is_operator(c)) {
        lexems.push_back(Lexem(std::string(1, c), Operator));
        currentState = AFTER_OPERATOR;
    }
    else if (is_valid_variable_char(c)) {
        print_error(expression, "Unexcepted operand", i);
    }
    else if (c == '(' || c == '[' || c == '{') {
        print_error(expression, "Unexpected open bracket", i);
    }
    else {
        print_error(expression, "Unexpected symbol", i);
    }
}

void Parser::handle_remaining_token(List<Lexem>& lexems, State& currentState,
    std::string& currentToken) {
    if (!currentToken.empty()) {
        if (currentState == IN_NUMBER) {
            lexems.push_back(Lexem(currentToken, Constant, std::stod(currentToken)));
        }
        else if (currentState == IN_VARIABLE) {
            if (is_function(currentToken)) {
                if (currentToken == "sin") {
                    Lexem lex("sin", Function, DBL_MAX, -1, my_sin);
                    lexems.push_back(lex);
                }
                else if (currentToken == "cos") {
                    Lexem lex("cos", Function, DBL_MAX, -1, my_cos);
                    lexems.push_back(lex);
                }
                else if (currentToken == "tg") {
                    Lexem lex("tg", Function, DBL_MAX, -1, my_tg);
                    lexems.push_back(lex);
                }
                currentState = AFTER_FUNCTION;
                currentToken.clear();
            }
            else {
                lexems.push_back(Lexem(currentToken, Variable));
            }
        }
    }
}

void Parser::validate_final_state(State currentState, const std::string& expression) {
    if (currentState == AFTER_OPERATOR) {
        print_error(expression, "Expression can not ends with operator", expression.length() - 1);
    }
    else if (currentState == AFTER_UN_OPERATOR) {
        print_error(expression, "Expression can not ends with unary operator", expression.length() - 1);
    }
    else if (currentState == AFTER_OPEN_BRACKET) {
        print_error(expression, "Expression can not ends with unclosed bracket", expression.length() - 1);
    }
    else if (currentState == AFTER_FUNCTION) {
        print_error(expression, "There is no open bracket after the function", expression.length() - 1);
    }
    else if (currentState == START) {
        print_error(expression, "Expression can not be empty", expression.length() - 1);
    }
}

List<Lexem> Parser::parse(std::string expression) {
    List<Lexem> lexems;
    State currentState = START;
    std::string currentToken;
    LStack<char> brackets;

    for (size_t i = 0; i < expression.length(); i++) {
        char c = expression[i];
        if (c == ' ') continue;

        switch (currentState) {
        case START: handle_start(lexems, currentState, currentToken, brackets, expression, i, c); break;
        case IN_NUMBER: handle_in_number(lexems, currentState, currentToken, brackets, expression, i, c); break;
        case IN_VARIABLE: handle_in_variable(lexems, currentState, currentToken, brackets, expression, i, c); break;
        case AFTER_OPERATOR: handle_after_operator(lexems, currentState, currentToken, brackets, expression, i, c); break;
        case AFTER_UN_OPERATOR: handle_after_un_operator(lexems, currentState, currentToken, brackets, expression, i, c); break;
        case AFTER_OPEN_BRACKET: handle_after_open_bracket(lexems, currentState, currentToken, brackets, expression, i, c); break;
        case AFTER_CLOSED_BRACKET: handle_after_closed_bracket(lexems, currentState, currentToken, brackets, expression, i, c); break;
        case AFTER_FUNCTION: handle_after_function(lexems, currentState, currentToken, brackets, expression, i, c); break;
        case AFTER_OPERAND: handle_after_operand(lexems, currentState, currentToken, brackets, expression, i, c); break;
        }
    }

    if (!brackets.is_empty()) {
        print_error(expression, "Missing closing bracket", expression.length());
    }

    handle_remaining_token(lexems, currentState, currentToken);
    validate_final_state(currentState, expression);

    return lexems;
}