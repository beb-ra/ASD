#include "parser.h"

bool Parser::is_variable(char c) {
    return c == 'x' || c == 'y' || c == 'z';
}

void Parser::set_power(int powers[], char var, int value) {
    switch (var) {
    case 'x': powers[0] = value; break;
    case 'y': powers[1] = value; break;
    case 'z': powers[2] = value; break;
    }
}

Monom Parser::parse_monom(const std::string& str, size_t& pos) {
    State currentState = START;
    double coeff = 0;
    int sign = 1;
    int powers[VARS_COUNT] = { 0, 0, 0 };

    std::string currentNumber;
    char currentVar = 0;

    for (; pos < str.length(); pos++) {
        char c = str[pos];
        if (c == ' ') continue;

        switch (currentState) {
        case START:
            if (c == '+') {
                sign = 1;
                currentState = AFTER_OPERATOR;
            }
            else if (c == '-') {
                sign = -1;
                currentState = AFTER_OPERATOR;
            }
            else if (std::isdigit(c) || c == '.') {
                currentNumber += c;
                currentState = IN_COEFF;
            }
            else if (is_variable(c)) {
                coeff = 1;
                currentVar = c;
                currentState = AFTER_VARIABLE;
            }
            else {
                throw std::invalid_argument("Unexpected character at start of monom");
            }
            break;

        case IN_COEFF:
            if (std::isdigit(c) || c == '.') {
                currentNumber += c;
            }
            else if (is_variable(c)) {
                coeff = std::stod(currentNumber);
                currentNumber.clear();
                currentVar = c;
                currentState = AFTER_VARIABLE;
            }
            else {
                coeff = std::stod(currentNumber);
                currentNumber.clear();
                throw std::invalid_argument("Unexpected character at start of monom"); // ?
            }
            break;

        case AFTER_VARIABLE:
            if (c == '^') {
                currentState = AFTER_CHAR_POW;
            }
            else if (is_variable(c)) {
                set_power(powers, currentVar, 1);
                currentVar = c;
            }
            else {
                set_power(powers, currentVar, 1);
            }
            break;

        case AFTER_CHAR_POW:
            if (std::isdigit(c)) {
                currentNumber += c;
                currentState = IN_NUM_POW;
            }
            else {
                throw std::invalid_argument("Expected digit after ^");
            }
            break;

        case IN_NUM_POW:
            if (std::isdigit(c)) {
                currentNumber += c;
            }
            else if (is_variable(c)) {
                int power = std::stoi(currentNumber);
                set_power(powers, currentVar, power);
                currentNumber.clear();
                currentVar = c;
                currentState = AFTER_VARIABLE;
            }
            else {
                int power = std::stoi(currentNumber);
                set_power(powers, currentVar, power);
                currentNumber.clear();
                throw std::invalid_argument("Unexpected character at start of monom"); // ?
            }
            break;
    }

    if (currentState == IN_COEFF && !currentNumber.empty()) {
        coeff = std::stod(currentNumber);
        return Monom(sign * coeff, powers);
    }

    if (currentState == AFTER_VARIABLE) {
        set_power(powers, currentVar, 1);
        return Monom(sign * coeff, powers);
    }

    return Monom(sign * coeff, powers);
}

List<Monom> Parser::parse(const std::string& str) {
    List<Monom> monoms;
    State currentState = START;
    // скобки добавить ? LStack

    std::string currentCoeff;
    std::string currentNumber;
    char currentVar;
    double _powers[VARS_COUNT];

    for (int i = 0; i < str.length(); i++) {
        char c = str[i];

        /*
        switch (currentState) {
        case START: 
            if (std::isdigit(c)) {
                currentNumber += c;
                currentState = IN_COEFF;
            }
            else if (c == 'x') {
                currentCoeff = "1";
                currentVar = c;
                currentState = AFTER_VARIABLE;
            }
            else {
                //throw ..
            }
            break;
        case AFTER_VARIABLE:
            if (c == '^') {
                currentState = AFTER_CHAR_POW;
            }
            else {
                
            }
            break;
        case AFTER_CHAR_POW: 
            if (std::isdigit(c)) {
                currentNumber += c;
                currentState = IN_NUM_POW;
            }
            else {
                //throw ..
            }
            break;
        case IN_NUM_POW: 
            if (std::isdigit(c)) {
                currentNumber += c;
            }
            else {

            }
            break;
        case IN_COEFF: break;
        case AFTER_OPERATOR: break;
        }
        */
    }

    return monoms;
}