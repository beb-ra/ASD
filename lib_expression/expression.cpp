#include "expression.h"

Expression::Expression(std::string expression) {
    _lexems = Parser::parse(expression);
    convert_to_postfix();
}

Expression::Expression(List<Lexem>& lexems) : _lexems(lexems) {
    convert_to_postfix();
}

void Expression::set_variables(const std::string& name, double value) {
    bool is_found = false;
    for (auto& lexem : _polish_record) {
        if (lexem.name == name) {
            lexem.value = value;
            is_found = true;
        }
    }

    if (!is_found)
        throw std::invalid_argument("No matching variables found\n");
}

TVector<Lexem> Expression::get_variables() const {
    TVector<Lexem> variables;

    for (List<Lexem>::ConstIterator it = _polish_record.begin();
        it != _polish_record.end(); it++) {
        const Lexem& lexem = *it;

        if (lexem.type == TypeLexem::Variable) {
            if (find_first_elem(variables, lexem) == -1) {
                variables.push_back(lexem);
            }
        }
    }
    return variables;
}

List<Lexem> Expression::get_lexems() const {
    return _lexems;
}

double Expression::calculate() {
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
            if (lexem.value == DBL_MAX)
                throw std::logic_error("The variable has no value set: " + name);
            stack.push(lexem.value);
            break;

        case Operator: {
            if (stack.size() < 2) {
                throw std::logic_error("Not enough operands for operator: " + name);
            }
            double right = stack.top(); stack.pop();
            double left = stack.top(); stack.pop();

            if (name == "+") stack.push(left + right);
            else if (name == "-") stack.push(left - right);
            else if (name == "*") stack.push(left * right);
            else if (name == "/") {
                if (right == 0) throw std::logic_error("Division by zero");
                stack.push(left / right);
            }
            else if (name == "^") stack.push(std::pow(left, right));
            break;
        }

        case UnOperator:
            if (stack.is_empty()) {
                throw std::logic_error("Not enough operands for unary operator: " + name);
            }
            if (name == "~") {
                double val = stack.top(); stack.pop();
                stack.push(-val);
            }
            break;

        case Function: {
            if (stack.is_empty()) {
                throw std::logic_error("Not enough operands for function: " + name);
            }
            double val = stack.top(); stack.pop();

            stack.push(lexem.function(val));
            break;
        }

        default:
            break;
        }
    }

    if (stack.size() != 1) {
        throw std::logic_error("Invalid expression");
    }

    return stack.top();
}

void Expression::convert_to_postfix() {
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
            if (!stack.is_empty() && stack.top().type == OpenBracket) {
                stack.pop();
            }
            if (!stack.is_empty() && stack.top().type == Function) {
                _polish_record.push_back(stack.top());
                stack.pop();
            }
            break;

        case Function:
            stack.push(lexem);
            break;

        case UnOperator:
        case Operator:
            while (!stack.is_empty() &&
                get_precedence(stack.top()) >= get_precedence(lexem)) {
                _polish_record.push_back(stack.top());
                stack.pop();
            }
            stack.push(lexem);
            break;
        }
    }

    while (!stack.is_empty()) {
        _polish_record.push_back(stack.top());
        stack.pop();
    }
}

bool Expression::brackets_match(const Lexem& open, const Lexem& close) const {
    std::string open_val = open.name;
    std::string close_val = close.name;
    return (open_val == "(" && close_val == ")") ||
        (open_val == "{" && close_val == "}") ||
        (open_val == "[" && close_val == "]");
}

int Expression::get_precedence(const Lexem& lexem) const {
    TypeLexem type = lexem.type;
    std::string name = lexem.name;

    if (type == Function) return 5;
    if (name == "^") return 4;
    if (type == UnOperator) return 3;
    if (name == "*" || name == "/") return 2;
    if (name == "+" || name == "-") return 1;

    return 0;
}

bool Expression::is_opening_bracket(Lexem lexem) const {
    return lexem.type == OpenBracket;
}

bool Expression::is_closing_bracket(Lexem lexem) const {
    return lexem.type == ClosedBracket;
}

std::string Expression::to_string() const {
    std::string result;
    TypeLexem prev_type = None;

    for (auto it = _lexems.begin(); it != _lexems.end(); ++it) {
        const Lexem& current = *it;

        bool need_space = true;

        if (it == _lexems.begin()) {
            need_space = false;
        }
        else if (current.type == ClosedBracket) {
            need_space = false;
        }
        else if (prev_type == UnOperator) {
            need_space = false;
        }
        else if (current.type == OpenBracket) {
            if (prev_type == Function) {
                need_space = false;
            }
        }
        else if (current.type == UnOperator) {
            need_space = false;
        }
        else if (prev_type == OpenBracket) {
            need_space = false;
        }

        if (need_space && !result.empty()) {
            result += " ";
        }

        result += (current.name == "~") ? "-" : current.name;
        prev_type = current.type;
    }

    return result;
}
