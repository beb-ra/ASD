#pragma once
#include <iostream>
#include <map>
#include "../lib_tvector/tvector.h"
#include "../lib_list/list.h"
#include "../lib_lexem/lexem.h"
#include "../lib_parser/parser.h"

class Expression {
    List<Lexem> _lexems;
    List<Lexem> _polish_record;

public:
    Expression() = default;
    Expression(std::string expression);
    Expression(List<Lexem>& lexems);

    void set_variables(const std::string& name, double value);
    TVector<Lexem> get_variables() const;
    List<Lexem> get_lexems() const;

    double calculate();

    friend std::ostream& operator<<(std::ostream& os, const Expression& expression) {
        auto* node = expression._lexems.head();
        for (size_t i = 0; i < expression._lexems.size(); i++) {
            std::cout << node->value.name << " ";
            node = node->next;
        }
        return os;
    }
private:
    void convert_to_postfix();
    bool brackets_match(const Lexem& open, const Lexem& close) const;
    int get_precedence(const Lexem& lexem) const;
    bool is_opening_bracket(Lexem lexem) const;
    bool is_closing_bracket(Lexem lexem) const;
    void print() const;
};