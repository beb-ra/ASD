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
    //Lexem(std::string _name = "", TypeLexem _type = None, double _value = DBL_MAX, int _priority = -1, double(*_function)(double) = nullptr) { /* ... */ }
    /* ... */

    Lexem(std::string _name = "", TypeLexem _type = None, double _value = DBL_MAX,
        int _priority = -1, double(*_function)(double) = nullptr)
        : name(_name), type(_type), value(_value), priority(_priority), function(_function)
    {
        if (type == Constant && value == DBL_MAX && !name.empty()) {
            try {
                value = std::stod(name);
            }
            catch (...) {
                value = 0.0;
            }
        }
    }

    bool operator==(const Lexem& other) const {
        if (type != other.type || name != other.name) {
            return false;
        }
        if (type == Constant && std::abs(value - other.value) > 1e-10) {
            return false;
        }
        if (type == Function && function != other.function) {
            return false;
        }
        return true;
    }

    bool operator!=(const Lexem& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, const Lexem& lexem) {
        os << lexem.name;
        return os;
    }
};
