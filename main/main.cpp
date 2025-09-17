// Copyright 2024 Marina Usova

#define MATRIX_INTERFACE
#ifdef MATRIX_INTERFACE

#include <iostream>
#include <iomanip>
#include <cstdlib>

#define DEBUG

#define ADD 0
#define SUB 1
#define MULT 2
#define MULT_SCALAR 3
#define EXIT 4

#define COMMON 0
#define TRIANGLE 1
#define MATRIX_A 1
#define MATRIX_B 2
#define MATRIX_C 3
#define RESULT_MATRIX 4

#ifdef DEBUG
class TriangleMatrix {
    int _n;
public:
    TriangleMatrix() { _n = 2; }
    TriangleMatrix(int n) { _n = n; }
    int get_n() const { return _n; }
    TriangleMatrix operator + (const TriangleMatrix&) const { TriangleMatrix m; return m; }
    TriangleMatrix operator - (const TriangleMatrix&) const { TriangleMatrix m; return m; }
    TriangleMatrix operator * (const TriangleMatrix&) const { TriangleMatrix m; return m; }
    TriangleMatrix operator * (int) const { TriangleMatrix m; return m; }
};
class Matrix {
    int _n, _m;
public:
    Matrix() { _n = 2; _m = 2; }
    Matrix(int n, int m) { _n = n; _m = m; }
    int get_n() const { return _n; }
    int get_m() const { return _m; }
    Matrix operator + (const Matrix&) const { Matrix m; return m; }
    Matrix operator - (const Matrix&) const { Matrix m; return m; }
    Matrix operator * (const Matrix&) const { Matrix m; return m; }
    Matrix operator * (int) const { Matrix m; return m; }
};
class MathVector;
std::istream& operator >> (std::istream& in, Matrix& m) { return in; }
std::istream& operator >> (std::istream& in, TriangleMatrix& num) { return in; }
#endif

void handle_matrices();
void handle_triangle_matrices();
Matrix do_binary_operation(int, char, char, const Matrix&, const Matrix&, const Matrix&);
Matrix do_scalar_operation(int, char, const Matrix&, const Matrix&, const Matrix&);
TriangleMatrix do_binary_operation(int, char, char, const TriangleMatrix&, const TriangleMatrix&, const TriangleMatrix&);
TriangleMatrix do_scalar_operation(int, char, const TriangleMatrix&, const TriangleMatrix&, const TriangleMatrix&);
void do_matrix_operations(Matrix&, Matrix&, Matrix&);
void do_matrix_operations(TriangleMatrix&, TriangleMatrix&, TriangleMatrix&);
int enter_matrix_type();
int* enter_matrix_size(int);
int enter_tmatrix_size(int);
void enter_matrix(Matrix&, int);
void enter_matrix(TriangleMatrix&, int);
void print_matrix(const Matrix&, int);
void print_matrix(const TriangleMatrix&, int);
void print_result(const Matrix&, const Matrix&, const Matrix&, const Matrix&);
void print_result(const TriangleMatrix&, const TriangleMatrix&, const TriangleMatrix&, const TriangleMatrix&);
void save_result(char, Matrix&, Matrix&, Matrix&, Matrix&);
void save_result(char, TriangleMatrix&, TriangleMatrix&, TriangleMatrix&, TriangleMatrix&);
int select_matrix_operations();
char* select_matrices();
char select_matrix(bool);
Matrix do_operation_on_matrices(int, const Matrix&, const Matrix&);
TriangleMatrix do_operation_on_matrices(int, const TriangleMatrix&, const TriangleMatrix&);
int select_scalar();

int main() {
    int type = enter_matrix_type();
    system("cls");
    switch (type) {
    case 0: {
        handle_matrices();
    } break;
    case 1: {
        handle_triangle_matrices();
    } break;
    }

    return 0;
}

void handle_matrices() {
    int* mass1 = enter_matrix_size(MATRIX_A);
    int size_n = mass1[0], size_m = mass1[1];
    delete mass1;
    Matrix matrixA(size_n, size_m);
    enter_matrix(matrixA, MATRIX_A);

    int* mass2 = enter_matrix_size(MATRIX_B);
    size_n = mass2[0], size_m = mass2[1];
    delete mass2;
    Matrix matrixB(size_n, size_m);
    enter_matrix(matrixB, MATRIX_B);
    system("cls");

    print_matrix(matrixA, MATRIX_A);
    print_matrix(matrixB, MATRIX_B);

    Matrix matrixC;
    do_matrix_operations(matrixA, matrixB, matrixC);
}

void handle_triangle_matrices() {
    int size_n = enter_tmatrix_size(MATRIX_A);
    TriangleMatrix matrixA(size_n);
    enter_matrix(matrixA, MATRIX_A);
    system("cls");

    size_n = enter_tmatrix_size(MATRIX_B);
    TriangleMatrix matrixB(size_n);
    enter_matrix(matrixB, MATRIX_B);
    system("cls");

    print_matrix(matrixA, MATRIX_A);
    print_matrix(matrixB, MATRIX_B);

    TriangleMatrix matrixC;
    do_matrix_operations(matrixA, matrixB, matrixC);
}

void print_matrix(const Matrix& matr, int num) {
    if (num == MATRIX_A) std::cout << "\tMATRIX A\n";
    else if (num == MATRIX_B) std::cout << "\tMATRIX B\n";
    else if (num == MATRIX_C) std::cout << "\tMATRIX C\n";
    else std::cout << "\tRESULT MATRIX\n";

    for (size_t i = 0; i < matr.get_n(); i++) {
        for (size_t j = 0; j < matr.get_m(); j++) {
#ifdef DEBUG
            std::cout << "* ";
#else
            std::cout << matr[i][j] << " ";
#endif
        }
        std::cout << "\n";
    }
}

void print_matrix(const TriangleMatrix& matr, int num) {
    if (num == MATRIX_A) std::cout << "\tMATRIX A\n";
    else if (num == MATRIX_B) std::cout << "\tMATRIX B\n";
    else if (num == MATRIX_C) std::cout << "\tMATRIX C\n";
    else std::cout << "\tRESULT MATRIX\n";

    for (size_t i = 0; i < matr.get_n(); i++) {
        for (size_t j = 0; j < matr.get_n(); j++) {
#ifdef DEBUG
            std::cout << "* ";
#else
            std::cout << matr[i][j] << " ";
#endif
        }
        std::cout << "\n";
    }
}

void print_result(const Matrix& matrixA, const Matrix& matrixB, const Matrix& matrixC, const Matrix& result) {
    system("cls");
    print_matrix(result, RESULT_MATRIX);
    system("pause");
    system("cls");
    print_matrix(matrixA, MATRIX_A);
    print_matrix(matrixB, MATRIX_B);
    print_matrix(matrixC, MATRIX_C);
}

void print_result(const TriangleMatrix& matrixA, const TriangleMatrix& matrixB, const TriangleMatrix& matrixC, const TriangleMatrix& result) {
    system("cls");
    print_matrix(result, RESULT_MATRIX);
    system("pause");
    system("cls");
    print_matrix(matrixA, MATRIX_A);
    print_matrix(matrixB, MATRIX_B);
    print_matrix(matrixC, MATRIX_C);
}

void save_result(char matrix_char, Matrix& matrixA, Matrix& matrixB, Matrix& matrixC, Matrix& result) {
    switch (matrix_char) {
    case 'A': {
        matrixA = result;
    } break;
    case 'B': {
        matrixB = result;
    } break;
    case 'C': {
        matrixC = result;
    }
    }
    system("cls");
    print_matrix(matrixA, MATRIX_A);
    print_matrix(matrixB, MATRIX_B);
    print_matrix(matrixC, MATRIX_C);
}

void save_result(char matrix_char, TriangleMatrix& matrixA, TriangleMatrix& matrixB, TriangleMatrix& matrixC, TriangleMatrix& result) {
    switch (matrix_char) {
    case 'A': {
        matrixA = result;
    } break;
    case 'B': {
        matrixB = result;
    } break;
    case 'C': {
        matrixC = result;
    }
    }
    system("cls");
    print_matrix(matrixA, MATRIX_A);
    print_matrix(matrixB, MATRIX_B);
    print_matrix(matrixC, MATRIX_C);
}

void do_matrix_operations(Matrix& matrixA, Matrix& matrixB, Matrix& matrixC) {
    int operation = select_matrix_operations();

    if (operation >= ADD && operation <= MULT) {
        matrixC = do_operation_on_matrices(operation, matrixA, matrixB);
    }
    else if (operation == MULT_SCALAR) {
        int scalar = select_scalar();
        char matrix_char = select_matrix(false);

        matrixC = do_scalar_operation(scalar, matrix_char, matrixA, matrixB, matrixC);
    }
    else if (operation == EXIT) return;
    print_result(matrixA, matrixB, matrixC, matrixC);

    Matrix matrix;
    while (1) {
        int operation = select_matrix_operations();

        if (operation >= ADD && operation <= MULT) {
            char* mass3 = select_matrices();
            matrix = do_binary_operation(operation, mass3[0], mass3[1], matrixA, matrixB, matrixC);
            delete mass3;
        }
        else if (operation == MULT_SCALAR) {
            int scalar = select_scalar();
            char matrix_char = select_matrix(true);

            matrix = do_scalar_operation(scalar, matrix_char, matrixA, matrixB, matrixC);
        }
        else if (operation == EXIT) return;
        print_result(matrixA, matrixB, matrixC, matrix);
        std::cout << "Select which matrix to save the result\n";
        char matrix_char = select_matrix(true);
        save_result(matrix_char, matrixA, matrixB, matrixC, matrix);
    }
}

void do_matrix_operations(TriangleMatrix& matrixA, TriangleMatrix& matrixB, TriangleMatrix& matrixC) {
    int operation = select_matrix_operations();

    if (operation >= ADD && operation <= MULT) {
        matrixC = do_operation_on_matrices(operation, matrixA, matrixB);
    }
    else if (operation == MULT_SCALAR) {
        int scalar = select_scalar();
        char matrix_char = select_matrix(false);

        matrixC = do_scalar_operation(scalar, matrix_char, matrixA, matrixB, matrixC);
    }
    else if (operation == EXIT) return;
    print_result(matrixA, matrixB, matrixC, matrixC);

    TriangleMatrix matrix;
    while (1) {
        int operation = select_matrix_operations();

        if (operation >= ADD && operation <= MULT) {
            char* mass3 = select_matrices();
            matrix = do_binary_operation(operation, mass3[0], mass3[1], matrixA, matrixB, matrixC);
            delete mass3;
        }
        else if (operation == MULT_SCALAR) {
            int scalar = select_scalar();
            char matrix_char = select_matrix(true);

            matrix = do_scalar_operation(scalar, matrix_char, matrixA, matrixB, matrixC);
        }
        else if (operation == EXIT) return;
        print_result(matrixA, matrixB, matrixC, matrix);
        std::cout << "Select which matrix to save the result\n";
        char matrix_char = select_matrix(true);
        save_result(matrix_char, matrixA, matrixB, matrixC, matrix);
    }
}

TriangleMatrix do_scalar_operation(int scalar, char matrix_char, const TriangleMatrix& matrixA, 
    const TriangleMatrix& matrixB, const TriangleMatrix& matrixC) {
    switch (matrix_char) {
    case 'A': {
        return matrixA * scalar;
    } break;
    case 'B': {
        return matrixB * scalar;
    } break;
    case 'C':
        return matrixC * scalar;
    }
}

Matrix do_scalar_operation(int scalar, char matrix_char, const Matrix& matrixA, const Matrix& matrixB, const Matrix& matrixC) {
    switch (matrix_char) {
    case 'A': {
        return matrixA * scalar;
    } break;
    case 'B': {
        return matrixB * scalar;
    } break;
    case 'C':
        return matrixC * scalar;
    }
}

int enter_matrix_type() {
    int type;
    std::cout << "MATRIX TYPE\n0 - common\n1 - triangular\nYour choice: ";
    while (1) {
        std::cin >> type;
        if (type == COMMON || type == TRIANGLE) break;
        std::cout << "Incorrect input, please try again: ";
    }
    return type;
}

int* enter_matrix_size(int num) {
    int size_n, size_m;
    if (num == MATRIX_A) std::cout << "MATRIX SIZE\nEnter the size of matrix A (two numbers separated by a space): ";
    else if (num == MATRIX_B) std::cout << "MATRIX SIZE\nEnter the size of matrix B (two numbers separated by a space): ";
    else if (num == MATRIX_C) std::cout << "MATRIX SIZE\nEnter the size of matrix C (two numbers separated by a space): ";
    else std::cout << "MATRIX SIZE\nEnter the size of matrix (two numbers separated by a space): ";

    while (1) {
        std::cin >> size_n;
        std::cin >> size_m;
        if (size_n > 0 && size_m > 0) break;
        std::cout << "Incorrect input, please try again: ";
    }
    
    int* mass = new int[2];
    mass[0] = size_n;
    mass[1] = size_m;

    return mass;
}

int enter_tmatrix_size(int num) {
    int size_n;
    if (num == MATRIX_A) std::cout << "MATRIX SIZE\nEnter the size of triangular matrix A (two numbers separated by a space): ";
    else if (num == MATRIX_B) std::cout << "MATRIX SIZE\nEnter the size of triangular matrix B (two numbers separated by a space): ";
    else if (num == MATRIX_C) std::cout << "MATRIX SIZE\nEnter the size of triangular matrix C (two numbers separated by a space): ";
    else std::cout << "MATRIX SIZE\nEnter the size of triangular matrix (two numbers separated by a space): ";

    while (1) {
        std::cin >> size_n;
        if (size_n > 0) break;
        std::cout << "Incorrect input, please try again: ";
    }
    return size_n;
}

void enter_matrix(Matrix& matr, int num) {
#ifdef DEBUG
    int p; 
    if (num == MATRIX_A) std::cout << "Enter the matrix A\n";
    else if (num == MATRIX_B) std::cout << "Enter the matrix B\n";
    else std::cout << "Enter the matrix C\n";

    for (size_t i = 0; i < matr.get_n(); i++) {
        std::cout << "Enter the matrix row (elements separated by spaces): ";
        for (size_t j = 0; j < matr.get_m(); j++) {
            // std::cin >> matr[i][j];
            std::cin >> p;
        }
    }
#else
    if (num == MATRIX_A) std::cout << "Enter the matrix A\n";
    else if (num == MATRIX_B) std::cout << "Enter the matrix B\n";
    else std::cout << "Enter the matrix C\n";

    std::cin >> matr;
#endif
}

void enter_matrix(TriangleMatrix& matr, int num) {
#ifdef DEBUG
    int p;
    if (num == MATRIX_A) std::cout << "Enter the matrix A\n";
    else if (num == MATRIX_B) std::cout << "Enter the matrix B\n";
    else std::cout << "Enter the matrix C\n";

    for (size_t i = 0; i < matr.get_n(); i++) {
        std::cout << "Enter the matrix row (elements separated by spaces): ";
        for (size_t j = 0; j < matr.get_n(); j++) {
            // std::cin >> matr[i][j];
            std::cin >> p;
        }
    }
#else
    if (num == MATRIX_A) std::cout << "Enter the matrix A\n";
    else if (num == MATRIX_B) std::cout << "Enter the matrix B\n";
    else std::cout << "Enter the matrix C\n";

    std::cin >> matr;
#endif
}

char* select_matrices() {
    char letter1, letter2;
    std::cout << "Select the first matrix (A, B or C): ";
    while (1) {
        std::cin >> letter1;
        if (letter1 == 'A' || letter1 == 'B' || letter1 == 'C') break;
        if (letter1 == 'a') { letter1 = 'A'; break; }
        if (letter1 == 'b') { letter1 = 'B'; break; }
        if (letter1 == 'c') { letter1 = 'C'; break; }
        std::cout << "Incorrect input, please try again: ";
    }
    std::cout << "Select the second matrix (A, B or C): ";
    while (1) {
        std::cin >> letter2;
        if (letter2 == 'A' || letter2 == 'B' || letter2 == 'C') break;
        if (letter2 == 'a') { letter2 = 'A'; break; }
        if (letter2 == 'b') { letter2 = 'B'; break; }
        if (letter2 == 'c') { letter2 = 'C'; break; }
        std::cout << "Incorrect input, please try again: ";
    }

    char* mass = new char[2];
    mass[0] = letter1;
    mass[1] = letter2;

    return mass;
}

char select_matrix(bool isC) {
    char letter;
    std::cout << "Select the matrix (A, B or C): ";
    if (isC) {
        while (1) {
            std::cin >> letter;
            if (letter == 'A' || letter == 'B' || letter == 'C') break;
            if (letter == 'a') { letter = 'A'; break; }
            if (letter == 'b') { letter = 'B'; break; }
            if (letter == 'c') { letter = 'C'; break; }
            std::cout << "Incorrect input, please try again: ";
        }
    }
    else {
        while (1) {
            std::cin >> letter;
            if (letter == 'A' || letter == 'B') break;
            if (letter == 'a') { letter = 'A'; break; }
            if (letter == 'b') { letter = 'B'; break; }
            std::cout << "Incorrect input, please try again: ";
        }
    }
    return letter;
}

int select_matrix_operations() {
    int operation;
    std::cout << "Select a matrix operation\n0 - addition\n1 - subtraction\n2 - multiplication\n3 - multiplication by a scalar\n4 - exit\nYour choice: ";
    while (1) {
        std::cin >> operation;
        if (operation >= ADD && operation <= EXIT) return operation;
        std::cout << "Incorrect input, please try again: ";
    }
}

Matrix do_operation_on_matrices(int operation, const Matrix& matrix1, const Matrix& matrix2) {
    Matrix matrix;

    switch (operation) {
    case ADD: {
        try {
            matrix = matrix1 + matrix2;
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Matrix addition error: " << e.what() << std::endl;
        }

    } break;
    case SUB: {
        try {
            matrix = matrix1 - matrix2;
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Matrix subtraction error: " << e.what() << std::endl;
        }

    } break;
    case MULT: {
        try {
            matrix = matrix1 * matrix2;
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Matrix multiplication error: " << e.what() << std::endl;
        }
    }
    }
    return matrix;
}

TriangleMatrix do_operation_on_matrices(int operation, const TriangleMatrix& matrix1, const TriangleMatrix& matrix2) {
    TriangleMatrix matrix;

    switch (operation) {
    case ADD: {
        try {
            matrix = matrix1 + matrix2;
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Matrix addition error: " << e.what() << std::endl;
        }

    } break;
    case SUB: {
        try {
            matrix = matrix1 - matrix2;
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Matrix subtraction error: " << e.what() << std::endl;
        }

    } break;
    case MULT: {
        try {
            matrix = matrix1 * matrix2;
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Matrix multiplication error: " << e.what() << std::endl;
        }
    }
    }
    return matrix;
}

Matrix do_binary_operation(int operation, char matrix1, char matrix2, const Matrix& matrixA, const Matrix& matrixB, const Matrix& matrixC) {
    if (matrix1 == 'A') {
        if (matrix2 == 'A') return do_operation_on_matrices(operation, matrixA, matrixA);
        else if (matrix2 == 'B') return do_operation_on_matrices(operation, matrixA, matrixB);
        else if (matrix2 == 'C') return do_operation_on_matrices(operation, matrixA, matrixC);
    }
    else if (matrix1 == 'B') {
        if (matrix2 == 'A') return do_operation_on_matrices(operation, matrixB, matrixA);
        else if (matrix2 == 'B') return do_operation_on_matrices(operation, matrixB, matrixB);
        else if (matrix2 == 'C') return do_operation_on_matrices(operation, matrixB, matrixC);
    }
    else if (matrix1 == 'C') {
        if (matrix2 == 'A') return do_operation_on_matrices(operation, matrixC, matrixA);
        else if (matrix2 == 'B') return do_operation_on_matrices(operation, matrixC, matrixB);
        else if (matrix2 == 'C') return do_operation_on_matrices(operation, matrixC, matrixC);
    }
}

TriangleMatrix do_binary_operation(int operation, char matrix1, char matrix2, const TriangleMatrix& matrixA, 
    const TriangleMatrix& matrixB, const TriangleMatrix& matrixC) {
    if (matrix1 == 'A') {
        if (matrix2 == 'A') return do_operation_on_matrices(operation, matrixA, matrixA);
        else if (matrix2 == 'B') return do_operation_on_matrices(operation, matrixA, matrixB);
        else if (matrix2 == 'C') return do_operation_on_matrices(operation, matrixA, matrixC);
    }
    else if (matrix1 == 'B') {
        if (matrix2 == 'A') return do_operation_on_matrices(operation, matrixB, matrixA);
        else if (matrix2 == 'B') return do_operation_on_matrices(operation, matrixB, matrixB);
        else if (matrix2 == 'C') return do_operation_on_matrices(operation, matrixB, matrixC);
    }
    else if (matrix1 == 'C') {
        if (matrix2 == 'A') return do_operation_on_matrices(operation, matrixC, matrixA);
        else if (matrix2 == 'B') return do_operation_on_matrices(operation, matrixC, matrixB);
        else if (matrix2 == 'C') return do_operation_on_matrices(operation, matrixC, matrixC);
    }
}

int select_scalar() {
    int scalar;
    std::cout << "Enter a scalar (integer): ";
    std::cin >> scalar;
    return scalar;
}

#endif  // MATRIX_INTERFACE
