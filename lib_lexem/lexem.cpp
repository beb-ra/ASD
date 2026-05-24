#include "lexem.h"

Lexem::Lexem(std::string _name, TypeLexem _type, double _value,
    int _priority, double(*_function)(double))
    : name(_name), type(_type), value(_value), priority(_priority), function(_function)
{
    if (type == Constant && value == DBL_MAX && !name.empty()) {
        try {
            value = std::stod(name);
        }
        catch (const std::exception& e) {
            value = 0.0;
        }
    }
}

bool Lexem::operator==(const Lexem& other) const {
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

bool Lexem::operator!=(const Lexem& other) const {
    return !(*this == other);
}