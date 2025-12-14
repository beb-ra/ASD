#include <iostream>
#include <iomanip>
#include "../lib_tvector/tvector.h"
#include "../lib_expression/expression.h"
#include "../lib_parser/parser.h"

#define MENU_SIZE 5
#define EXIT 0
#define ADD_EXP 1
#define DELETE 2
#define SET_VARS 3
#define CALCULATE 4

void print_start() {
    std::cout << "\t\t\tКАЛЬКУЛЯТОР АРИФМЕТИЧЕСКИХ ВЫРАЖЕНИЙ\n";
    std::cout << "\nВведите первое выражение: ";
}

std::string lexems_to_string(const List<Lexem>& lexems) {
    std::string result;

    for (auto it = lexems.begin(); it != lexems.end(); ++it) {
        result += (*it).name;
        auto next_it = it;
        ++next_it;
        if (next_it != lexems.end()) {
            result += " ";
        }
    }

    return result;
}

std::string format_variables(const TVector<Lexem>& variables) {
    std::string result;

    for (size_t i = 0; i < variables.size(); i++) {
        if (i > 0) result += ", ";
        if (variables[i].value == DBL_MAX) {
            result += variables[i].name + " = ?";
        }
        else {
            //result += variables[i].name + " = " + std::to_string(variables[i].value);
            std::stringstream ss;
            ss << std::fixed << std::setprecision(3) << variables[i].value;
            result += variables[i].name + " = " + ss.str();
        }

        /*
        if (result.length() > 25) {
            result = result.substr(0, 22) + "...";
            break;
        }
        */
    }

    if (variables.size() == 0) {
        result = "-";
    }

    return result;
}

void print_menu(const TVector<Expression>& exs) {
    system("cls");

    std::cout << "\t\t\tКАЛЬКУЛЯТОР АРИФМЕТИЧЕСКИХ ВЫРАЖЕНИЙ\n\n";
    std::cout << " ID  | ВЫРАЖЕНИЕ                              | ПЕРЕМЕННЫЕ\n";
    std::cout << "-----+----------------------------------------+---------------------------\n";

    if (exs.size() == 0) {
        std::cout << "\t\tВыражения пока не добавлены\n";
    }
    for (size_t i = 0; i < exs.size(); i++) {
        std::cout << " ";
        if (i + 1 < 10) std::cout << " ";
        std::cout << i + 1 << "  | ";

        std::string expr = lexems_to_string(exs[i].get_lexems());
        if (expr.length() > 38) {
            expr = expr.substr(0, 35) + "...";
        }
        std::cout << expr;

        int spaces = 38 - expr.length();
        for (int j = 0; j < spaces; j++) std::cout << " ";

        std::cout << " | ";

        std::string vars = format_variables(exs[i].get_variables());
        std::cout << vars << "\n";
    }

    std::cout << "--------------------------------------------------------------------------\n\n";

    std::cout << "Меню:\n";
    std::cout << "1: Добавить новое выражение\n";
    std::cout << "2: Удалить выражение\n";
    std::cout << "3: Задать переменные\n";
    std::cout << "4: Вычислить значение выражения\n";
    std::cout << "0: Выход\n";
    std::cout << "Ваш выбор: ";
}

std::string get_string() {
    if (std::cin.peek() == '\n') {
        std::cin.ignore();
    }
    std::string s;
    std::getline(std::cin, s);

    return s;
}

size_t select_option(size_t n) {
    size_t answer;
    while (true) {
        std::cin >> answer;
        if (answer < n) break;
        std::cout << "Некорректное значение, попробуйте снова: ";
    }
    return answer;
}

size_t select_index(size_t n) {
    size_t answer;
    while (true) {
        std::cin >> answer;
        if (answer <= n && answer > 0) break;
        std::cout << "Некорректный ID, попробуйте снова: ";
    }
    return answer;
}

void set_variable(TVector<Expression>& expressions, size_t ind) {
    std::string var, value;
    while (true) {
        std::cout << "Введите переменную: ";
        var = get_string();
        std::cout << "Введите значение: ";
        value = get_string();
        try {
            double num;
            std::stringstream ss(value);
            if (!(ss >> num)) {
                std::cout << "Ошибка: не удалось преобразовать в число\n";
                std::cout << "Попробуйте еще раз\n";
                continue;
            }
            char remaining;
            if (ss >> remaining) {
                std::cout << "Ошибка: в строке есть лишние символы\n";
                std::cout << "Попробуйте еще раз\n";
                continue;
            }
            expressions[ind].set_variables(var, num);
            break;
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what();
            std::cout << "Попробуйте еще раз\n";
        }
    }
}

void start_set_variables(TVector<Expression>& expressions) {
    if (expressions.size() == 0) {
        std::cout << "Ошибка: не введено ни одного выражения\n";
        system("pause");
        return;
    }
    size_t ind;
    if (expressions.size() == 1) {
        ind = 0;
    }
    else {
        std::cout << "Введите ID выражения: ";
        ind = select_index(expressions.size()) - 1;
    }
    TVector<Lexem> variables = expressions[ind].get_variables();
    if (variables.size() == 0) {
        std::cout << "Ошибка: в выражении нет переменных\n";
        system("pause");
        return;
    }
    for (int i = 0; i < variables.size(); i++) {
        set_variable(expressions, ind);
    }
}

void start_calculate(TVector<Expression>& expressions) {
    size_t ind;
    if (expressions.size() == 0) {
        std::cout << "Ошибка: нет выражений для вычисления" << std::endl;
        system("pause");
        return;
    }
    if (expressions.size() == 1) {
        ind = 0;
    }
    else {
        std::cout << "Введите ID выражения: ";
        ind = select_index(expressions.size()) - 1;
    }
    try {
        double result = expressions[ind].calculate();
        std::cout << "Результат: " << result << std::endl;
        system("pause");
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        system("pause");
    }
}

void start_delete(TVector<Expression>& expressions) {
    size_t ind;
    if (expressions.size() == 0) {
        std::cout << "Ошибка: не введено ни одного выражения\n";
        system("pause");
        return;
    }
    if (expressions.size() == 1) {
        ind = 0;
    }
    else {
        std::cout << "Введите ID выражения: ";
        ind = select_index(expressions.size());
    }
    expressions.erase(ind);
}

void start_add_expression(TVector<Expression>& expressions) {
    std::cout << "Введите выражение: ";
    Expression expression;
    while (true) {
        std::string s = get_string();
        try {
            expression = Expression(s);
            break;
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
        std::cout << "Некорректное выражение, попробуйте снова: ";
    }
    expressions.push_back(expression);
}

Expression get_expression() {
    std::string s;
    Expression expression;
    while (true) {
        s = get_string();
        try {
            expression = Expression(s);
            break;
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
        std::cout << "Некорректное выражение, попробуйте снова: ";
    }
    return expression;
}

int main() {
    setlocale(LC_ALL, "Russian");
    print_start();
    Expression expression = get_expression();
    TVector<Expression> expressions;
    expressions.push_back(expression);

    while (true) {
        print_menu(expressions);
        size_t selected = select_option(MENU_SIZE);
        switch (selected) {
        case EXIT: return 0;
        case ADD_EXP: 
            start_add_expression(expressions);
            break;
        case DELETE: 
            start_delete(expressions);
            break;
        case SET_VARS: 
            start_set_variables(expressions);
            break;
        case CALCULATE: 
            start_calculate(expressions);
            break;
        }
    }
    /*
    std::string s = "   ";
    try {
        Expression e(s);
        e.print();
        double result = e.calculate();
        std::cout << result << std::endl;
    }
    catch (const std::logic_error& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
    
    
    //std::string s = "21 * (x + 33 * y)";
    //std::string s = "x_1 * sin(y + 7) + y * (-|x_2 - 17| + 23)";
    //std::string s = "||x| - |y||";
    */
}

