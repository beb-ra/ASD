// Copyright 2024 Marina Usova

#define MATRIX_INTERFACE
#ifdef MATRIX_INTERFACE

#include <iostream>
#include <iomanip>
#include <clocale>
#include <cstdlib>

#define COMMON 0
#define TRIANGLE 1
#define MATRIX_A 1
#define MATRIX_B 2
#define MATRIX_C 3

// какого вида матрицы
// выбор размера матриц
// введите матрицы А, В
// вывод матриц 
// выберите операцию
// вывести итоговую матрицу. сохранить вместо A, B, C? или отмена
// зациклить выбор операции

class TriangleMatrix {
    int _n;
public:
    TriangleMatrix() { _n = 2; }
    TriangleMatrix(int n) { _n = n; }
    int get_n() { return _n; }
};
class Matrix {
    int _n, _m;
public:
    Matrix() { _n = 2; _m = 2; }
    Matrix(int n, int m) { _n = n; _m = m; }
    int get_n() { return _n; }
    int get_m() { return _m; }
    Matrix operator + (const Matrix&) const {}
    Matrix operator - (const Matrix&) const {}
    Matrix operator * (const Matrix&) const {}
    Matrix operator * (int) const {}
};
class MathVector;

int enter_matrix_type();
int* enter_matrix_size(int);
int enter_tmatrix_size(int);
void enter_matrix(Matrix, int);
void enter_matrix(TriangleMatrix, int);
void print_matrix(Matrix, int);
void print_matrix(TriangleMatrix, int);
int select_matrix_operations();
char* select_matrices();
char select_matrix();
void do_operation_on_matrices(int, Matrix, Matrix);
void do_operation_on_matrices(int, TriangleMatrix, TriangleMatrix);
int select_scalar();

int main() {
    setlocale(LC_ALL, "Russian");
    int type = enter_matrix_type();
    system("cls");
    switch (type) {
    case 0: {
        int* mass1 = enter_matrix_size(MATRIX_A);
        int size_n = mass1[0], size_m = mass1[1];
        delete mass1;
        Matrix matrixA(size_n, size_m);
        enter_matrix(matrixA, 1);
        system("cls");

        int* mass2 = enter_matrix_size(MATRIX_B);
        size_n = mass2[0], size_m = mass2[1];
        delete mass2;
        Matrix matrixB(size_n, size_m);
        enter_matrix(matrixB, 2);
        system("cls");

        print_matrix(matrixA, MATRIX_A);
        print_matrix(matrixB, MATRIX_B);
        // Matrix matrixC;
        // до while вынести без С

        int operation = select_matrix_operations();
        Matrix matrixC; // записать в нее результат
        if (operation >= 0 && operation <= 2) {
            char* mass3 = select_matrices();
            if (mass3[0] == 'A') {
                if (mass3[1] == 'A') do_operation_on_matrices(operation, matrixA, matrixA);
                else if (mass3[1] == 'B') do_operation_on_matrices(operation, matrixA, matrixB);
                else // возбуждение ошибки что матрицы C нет
            }
            else if (mass3[0] == 'B') {
                if (mass3[1] == 'A') do_operation_on_matrices(operation, matrixB, matrixA);
                else if (mass3[1] == 'B') do_operation_on_matrices(operation, matrixB, matrixB);
                else // возбуждение ошибки что матрицы C нет
            }
            else // возбуждение ошибки что матрицы C нет
            delete mass3;
        }
        else if (operation == 3) {
            int scalar = select_scalar();
            char matrix_char = select_matrix();
            Matrix matrix3(matrixA.get_n(), matrixA.get_m());

            switch (matrix_char) {
            case 'A': {
                matrix3 = matrixA * scalar;
            }
            case 'B':
                matrix3 = matrixB * scalar;
            case 'C':
               // возбуждение ошибки что матрицы C нет
            }
        }
        

        while (1) {
            int operation = select_matrix_operations();
            if (operation >= 0 && operation <= 2) {
                char* mass3 = select_matrices();
                if (mass3[0] == 'A') {
                    if (mass3[1] == 'A') do_operation_on_matrices(operation, matrixA, matrixA);
                    else if (mass3[1] == 'B') do_operation_on_matrices(operation, matrixA, matrixB);
                    else do_operation_on_matrices(operation, matrixA, matrixC);
                }
                else if (mass3[0] == 'B') {
                    if (mass3[1] == 'A') do_operation_on_matrices(operation, matrixB, matrixA);
                    else if (mass3[1] == 'B') do_operation_on_matrices(operation, matrixB, matrixB);
                    else do_operation_on_matrices(operation, matrixB, matrixC);
                }
                else {
                    if (mass3[1] == 'A') do_operation_on_matrices(operation, matrixC, matrixA);
                    else if (mass3[1] == 'B') do_operation_on_matrices(operation, matrixC, matrixB);
                    else do_operation_on_matrices(operation, matrixC, matrixC);
                }
                delete mass3;
            }
            else if (operation == 3) {
                int scalar = select_scalar();
                char matrix_char = select_matrix();
                Matrix matrix3(matrixA.get_n(), matrixA.get_m());

                switch (matrix_char) {
                case 'A': {
                    matrix3 = matrixA * scalar;
                }
                case 'B': 
                    matrix3 = matrixB * scalar;
                case 'C':
                    matrix3 = matrixC * scalar;
                }
            }
        }
    } break;
    case 1: {
        int size_n = enter_tmatrix_size(MATRIX_A);
        TriangleMatrix matrixA(size_n);
        enter_matrix(matrixA, 1);
        system("cls");

        size_n = enter_tmatrix_size(MATRIX_B);
        TriangleMatrix matrixB(size_n);
        enter_matrix(matrixB, 2);
        system("cls");

        print_matrix(matrixA, MATRIX_A);
        print_matrix(matrixB, MATRIX_B);
    } break;
    }

    return 0;
}

int enter_matrix_type() {
    int type;
    std::cout << "ТИП МАТРИЦЫ\n0 - обычная\n1 - треугольная\nВаш выбор: ";
    while (1) {
        std::cin >> type;
        if (type == COMMON || type == TRIANGLE) break;
        std::cout << "\nНекорректный ввод, попробуйте еще: ";
    }
    return type;
}

int* enter_matrix_size(int num) {
    int size_n, size_m;
    if (num == MATRIX_A) std::cout << "РАЗМЕР МАТРИЦЫ\nВведите размер матрицы А (два числа через пробел): ";
    else if (num == MATRIX_B) std::cout << "РАЗМЕР МАТРИЦЫ\nВведите размер матрицы B (два числа через пробел): ";
    else std::cout << "РАЗМЕР МАТРИЦЫ\nВведите размер матрицы C (два числа через пробел): ";

    while (1) {
        std::cin >> size_n;
        std::cin >> size_m;
        if (size_n > 0 && size_m > 0) break;
        std::cout << "\nНекорректный ввод, попробуйте еще: ";
    }
    
    int* mass = new int[2];
    mass[0] = size_n;
    mass[1] = size_m;

    return mass;
}

int enter_tmatrix_size(int num) {
    int size_n;
    if (num == MATRIX_A) std::cout << "РАЗМЕР МАТРИЦЫ\nВведите размер треугольной матрицы А (одно число): ";
    else if (num == MATRIX_B) std::cout << "РАЗМЕР МАТРИЦЫ\nВведите размер треугольной матрицы B (одно число): ";
    else std::cout << "РАЗМЕР МАТРИЦЫ\nВведите размер треугольной матрицы C (одно число): ";

    while (1) {
        std::cin >> size_n;
        if (size_n > 0) break;
        std::cout << "\nНекорректный ввод, попробуйте еще: ";
    }
    return size_n;
}

void enter_matrix(Matrix matr, int num) {
    int p; //
    if (num == MATRIX_A) std::cout << "Введите матрицу A\n";
    else if (num == MATRIX_B) std::cout << "Введите матрицу B\n";
    else std::cout << "Введите матрицу C\n";

    for (size_t i = 0; i < matr.get_n(); i++) {
        std::cout << "Введите строку матрицы (элементы через пробел): ";
        for (size_t j = 0; j < matr.get_m(); j++) {
            // std::cin >> matr[i][j];
            std::cin >> p;
        }
    }
}

void enter_matrix(TriangleMatrix matr, int num) {
    int p; //
    if (num == MATRIX_A) std::cout << "Введите матрицу A\n";
    else if (num == MATRIX_B) std::cout << "Введите матрицу B\n";
    else std::cout << "Введите матрицу C\n";

    for (size_t i = 0; i < matr.get_n(); i++) {
        std::cout << "Введите строку матрицы (элементы через пробел): ";
        for (size_t j = 0; j < matr.get_n(); j++) {
            // std::cin >> matr[i][j];
            std::cin >> p;
        }
    }
}

void print_matrix(Matrix matr, int num) {
    if (num == MATRIX_A) std::cout << "\tМАТРИЦА A\n";
    else if (num == MATRIX_B) std::cout << "\tМАТРИЦА B\n";
    else std::cout << "\tМАТРИЦА C\n";

    for (size_t i = 0; i < matr.get_n(); i++) {
        for (size_t j = 0; j < matr.get_n(); j++) {
            // std::cout << matr[i][j];
            std::cout << "* ";
        }
        std::cout << "\n";
    }
}

void print_matrix(TriangleMatrix matr, int num) {
    if (num == MATRIX_A) std::cout << "\tМАТРИЦА A\n";
    else if (num == MATRIX_B) std::cout << "\tМАТРИЦА B\n";
    else std::cout << "\tМАТРИЦА C\n";

    for (size_t i = 0; i < matr.get_n(); i++) {
        for (size_t j = 0; j < matr.get_n(); j++) {
            // std::cout << matr[i][j];
            std::cout << "* ";
        }
        std::cout << "\n";
    }
}

char* select_matrices() {
    char letter1, letter2;
    std::cout << "Выберите первую матрицу (A, B или C): ";
    while (1) {
        std::cin >> letter1;
        if (letter1 == 'A' || letter1 == 'B' || letter1 == 'C') break;
        if (letter1 == 'a') { letter1 = 'A'; break; }
        if (letter1 == 'b') { letter1 = 'B'; break; }
        if (letter1 == 'c') { letter1 = 'C'; break; }
        std::cout << "\nНекорректный ввод, попробуйте еще: ";
    }
    std::cout << "Выберите первую матрицу (A, B или C): ";
    while (1) {
        std::cin >> letter2;
        if (letter2 == 'A' || letter2 == 'B' || letter2 == 'C') break;
        if (letter2 == 'a') { letter2 = 'A'; break; }
        if (letter2 == 'b') { letter2 = 'B'; break; }
        if (letter2 == 'c') { letter2 = 'C'; break; }
        std::cout << "\nНекорректный ввод, попробуйте еще: ";
    }

    char* mass = new char[2];
    mass[0] = letter1;
    mass[1] = letter2;

    return mass;
}

char select_matrix() {
    char letter;
    std::cout << "Выберите матрицу (A, B или C): ";
    while (1) {
        std::cin >> letter;
        if (letter == 'A' || letter == 'B' || letter == 'C') break;
        if (letter == 'a') { letter = 'A'; break; }
        if (letter == 'b') { letter = 'B'; break; }
        if (letter == 'c') { letter = 'C'; break; }
        std::cout << "\nНекорректный ввод, попробуйте еще: ";
    }
    return letter;
}

int select_matrix_operations() {
    int operation;
    std::cout << "Выберите операцию над матрицами\n0 - сложение\n1 - вычитание\n2 - умножение\n3 - умножение на скаляр\nВаш выбор: ";
    while (1) {
        std::cin >> operation;
        if (operation >= 0 && operation <= 3) return operation;
        std::cout << "\nНекорректный ввод, попробуйте еще: ";
    }
}

void do_operation_on_matrices(int operation, Matrix matrix1, Matrix matrix2) {
    switch (operation) {
    case 0: {
        Matrix matrix3(matrix1.get_n(), matrix1.get_m());
        // try catch?
        matrix3 = matrix1 + matrix2;

    } break;
    case 1: {
        Matrix matrix3(matrix1.get_n(), matrix1.get_m());
        // try catch?
        matrix3 = matrix1 - matrix2;

    } break;
    case 2: {
        Matrix matrix3(matrix1.get_n(), matrix2.get_m());
        // try catch?
        matrix3 = matrix1 * matrix2;
    } break;
    }
}

int select_scalar() {
    int scalar;
    std::cout << "Ведите скаляр (целое число): ";
    std::cin >> scalar;
    return scalar;
}

#endif  // MATRIX_INTERFACE
