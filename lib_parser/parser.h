#pragma once
#include <string>
#include "../lib_list/list.h"
#include "../lib_polynom/Monom.h"

namespace Parser {
    enum State {
        START,
        IN_COEFF,
        IN_NUM_POW,
        //AFTER_COEFF,
        AFTER_VARIABLE,
        AFTER_CHAR_POW,
        AFTER_OPERATOR
    };
    Monom Parser::parse_monom(const std::string&, size_t&);
    List<Monom> parse(const std::string&);

    void Parser::set_power(int powers[], char var, int value);
    bool is_variable(char c);
}