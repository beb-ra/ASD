#pragma once
#include <iostream>
#include <string>

enum TypeLexem {
    Constant, Variable, OpenBracket, ClosedBracket,
    Function, Operator, UnOperator, None
};

struct Lexem {
    std::string name;
    TypeLexem type;
    double value;
    int priority;
    double (*function)(double);

    Lexem(std::string _name = "", TypeLexem _type = None, double _value = DBL_MAX,
        int _priority = -1, double(*_function)(double) = nullptr);

    bool operator==(const Lexem& other) const;

    bool operator!=(const Lexem& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Lexem& lexem) {
        os << lexem.name;
        return os;
    }
};
