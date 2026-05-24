#define POINT_CIRCLE
#ifdef POINT_CIRCLE

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "../lib_point/point.h"
#include "../lib_circle/circle.h"
#include "../lib_algorithms/algorithms.h"

void output_result(int answer) {
    switch (answer) {
    case 0: std::cout << "intersect" << std::endl; break;
    case 1: std::cout << "touch" << std::endl; break;
    case 2: std::cout << "inside" << std::endl; break;
    case 3: std::cout << "not_intersect" << std::endl; break;
    }
}

int main() {
    Circle c1(1, 2, 3);
    Circle c2(2, 3, 1);

    int answer1 = figures_comparison(c1, c2);
    output_result(answer1);

    return 0;
}
#endif

#define MATRIX_INTERFACE
#ifdef MATRIX_INTERFACE
//#define DEBUG

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
template <class T>
class MVector {
public:
    MVector() {}
};

template <class T>
class Matrix : public MVector<MVector<T>> {
public:
    Matrix() { }
    Matrix(int n, int m) { }
    Matrix<T> operator + (const Matrix<T>&) const 
    { Matrix<T> m; return m; }
    Matrix<T> operator - (const Matrix<T>&) const 
    { Matrix<T> m; return m; }
    Matrix<T> operator * (const Matrix<T>&) const 
    { Matrix<T> m; return m; }
    Matrix<T> operator * (int) const { Matrix<T> m; return m; }
};
template <class T>
class TriangleMatrix : public Matrix<T> {
public:
    TriangleMatrix() { }
    TriangleMatrix(int n) { }
    TriangleMatrix<T> operator + (const TriangleMatrix<T>&) const 
    { TriangleMatrix<T> m; return m; }
    TriangleMatrix<T> operator - (const TriangleMatrix<T>&) const 
    { TriangleMatrix<T> m; return m; }
    TriangleMatrix<T> operator * (const TriangleMatrix<T>&) const 
    { TriangleMatrix<T> m; return m; }
    TriangleMatrix<T> operator * (int) const { TriangleMatrix<T> m; return m; }
};

template <class T>
std::istream& operator >> (std::istream& in, Matrix<T>& m) { return in; }
template <class T>
std::istream& operator << (std::istream& in, TriangleMatrix<T>& num) { return in; }
#else

#include "../lib_triangle_matrix/triangle_matrix.h"

#endif

void handle_matrices();
void handle_triangle_matrices();
template <class T>
Matrix<T> select_and_apply(int, char, char, const Matrix<T>&,
    const Matrix<T>&, const Matrix<T>&);
template <class T>
Matrix<T> start_scalar_operation(int, char, const Matrix<T>&, 
    const Matrix<T>&, const Matrix<T>&);
template <class T>
TriangleMatrix<T> select_and_apply(int, char, char,
    const TriangleMatrix<T>&, const TriangleMatrix<T>&, const TriangleMatrix<T>&);
template <class T>
TriangleMatrix<T> start_scalar_operation(int, char, 
    const TriangleMatrix<T>&, const TriangleMatrix<T>&, const TriangleMatrix<T>&);
template <class T>
bool initialize_matrix_C(Matrix<T>& matrixA, Matrix<T>& matrixB,
    Matrix<T>& matrixC);
template <class T>
bool initialize_matrix_C(TriangleMatrix<T>& matrixA, TriangleMatrix<T>& matrixB,
    TriangleMatrix<T>& matrixC);
template <class T>
void process_matrix_operations(Matrix<T>&, Matrix<T>&,
    Matrix<T>&);
template <class T>
void process_matrix_operations(TriangleMatrix<T>&, TriangleMatrix<T>&,
    TriangleMatrix<T>&);
int enter_matrix_type();
int* enter_matrix_size(int);
int enter_tmatrix_size(int);
template <class T>
void enter_matrix(Matrix<T>&, int);
template <class T>
void enter_matrix(TriangleMatrix<T>&, int);
template <class T>
void print_matrix(const Matrix<T>&, int);
template <class T>
void print_matrix(const TriangleMatrix<T>&, int);
template <class T>
void print_result(const Matrix<T>&, const Matrix<T>&, 
    const Matrix<T>&, const Matrix<T>&);
template <class T>
void print_result(const TriangleMatrix<T>&, const TriangleMatrix<T>&, 
    const TriangleMatrix<T>&, const TriangleMatrix<T>&);
template <class T>
void save_result(char, Matrix<T>&, Matrix<T>&, Matrix<T>&, 
    Matrix<T>&);
template <class T>
void save_result(char, TriangleMatrix<T>&, TriangleMatrix<T>&, 
    TriangleMatrix<T>&, TriangleMatrix<T>&);
int select_matrix_operations();
char* select_matrices();
char select_matrix(bool);
template <class T>
Matrix<T> start_bynary_operation_on_matrices(int, const Matrix<T>&,
    const Matrix<T>&);
template <class T>
TriangleMatrix<T> start_operation_on_matrices(int, 
    const TriangleMatrix<T>&, const TriangleMatrix<T>&);
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
    Matrix<int> matrixA(size_n, size_m);
    enter_matrix(matrixA, MATRIX_A);

    int* mass2 = enter_matrix_size(MATRIX_B);
    size_n = mass2[0], size_m = mass2[1];
    delete mass2;
    Matrix<int> matrixB(size_n, size_m);
    enter_matrix(matrixB, MATRIX_B);
    system("cls");

    Matrix<int> matrixC;
    bool is_exit = initialize_matrix_C(matrixA, matrixB, matrixC);
    if (is_exit) return;
    process_matrix_operations(matrixA, matrixB, matrixC);
}

void handle_triangle_matrices() {
    int size_n = enter_tmatrix_size(MATRIX_A);
    TriangleMatrix<int> matrixA(size_n);
    enter_matrix(matrixA, MATRIX_A);

    size_n = enter_tmatrix_size(MATRIX_B);
    TriangleMatrix<int> matrixB(size_n);
    enter_matrix(matrixB, MATRIX_B);
    system("cls");

    TriangleMatrix<int> matrixC;
    bool is_exit = initialize_matrix_C(matrixA, matrixB, matrixC);
    if (is_exit) return;
    process_matrix_operations(matrixA, matrixB, matrixC);
}

template <class T>
void print_matrix(const Matrix<T>& matr, int num) {
    if (num == MATRIX_A) std::cout << "\tMATRIX A\n";
    else if (num == MATRIX_B) std::cout << "\tMATRIX B\n";
    else if (num == MATRIX_C) std::cout << "\tMATRIX C\n";
    else std::cout << "\tRESULT MATRIX\n";
#ifdef DEBUG
    std::cout << "\n*The matrix output will be here*\n";
#else
    std::cout << matr;
    std::cout << "\n\n";
#endif
}

template <class T>
void print_matrix(const TriangleMatrix<T>& matr, int num) {
    if (num == MATRIX_A) std::cout << "\tMATRIX A\n";
    else if (num == MATRIX_B) std::cout << "\tMATRIX B\n";
    else if (num == MATRIX_C) std::cout << "\tMATRIX C\n";
    else std::cout << "\tRESULT MATRIX\n";
#ifdef DEBUG
    std::cout << "\n*The matrix output will be here*\n";
#else
    std::cout << matr;
    std::cout << "\n\n";
#endif
}

template <class T>
void print_result(const Matrix<T>& matrixA, const Matrix<T>& matrixB, 
    const Matrix<T>& matrixC, const Matrix<T>& result) {
    system("cls");
    print_matrix(result, RESULT_MATRIX);
    system("pause");
    system("cls");
    print_matrix(matrixA, MATRIX_A);
    print_matrix(matrixB, MATRIX_B);
    print_matrix(matrixC, MATRIX_C);
}

template <class T>
void print_result(const TriangleMatrix<T>& matrixA, const TriangleMatrix<T>& matrixB, 
    const TriangleMatrix<T>& matrixC, const TriangleMatrix<T>& result) {
    system("cls");
    print_matrix(result, RESULT_MATRIX);
    system("pause");
    system("cls");
    print_matrix(matrixA, MATRIX_A);
    print_matrix(matrixB, MATRIX_B);
    print_matrix(matrixC, MATRIX_C);
}

template <class T>
void save_result(char matrix_char, Matrix<T>& matrixA, Matrix<T>& matrixB, 
    Matrix<T>& matrixC, Matrix<T>& result) {
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

template <class T>
void save_result(char matrix_char, TriangleMatrix<T>& matrixA, TriangleMatrix<T>& matrixB, 
    TriangleMatrix<T>& matrixC, TriangleMatrix<T>& result) {
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

template <class T>
bool initialize_matrix_C(Matrix<T>& matrixA, Matrix<T>& matrixB, Matrix<T>& matrixC) {
    while (true) {
        print_matrix(matrixA, MATRIX_A);
        print_matrix(matrixB, MATRIX_B);

        int operation = select_matrix_operations();

        if (operation >= ADD && operation <= MULT) {
            try {
                matrixC = start_binary_operation(operation, matrixA, matrixB);
                break;
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Matrix operation error: " << e.what() << std::endl;
                system("pause");
                system("cls");
                continue;
            }
        }
        else if (operation == MULT_SCALAR) {
            int scalar = select_scalar();
            char matrix_char = select_matrix(false);

            matrixC = start_scalar_operation(scalar, matrix_char, matrixA, matrixB, matrixC);
            print_result(matrixA, matrixB, matrixC, matrixC);
            break;
        }
        else if (operation == EXIT) return true;
    }
    return false;
}

template <class T>
void process_matrix_operations(Matrix<T>& matrixA, Matrix<T>& matrixB, Matrix<T>& matrixC) {
    Matrix<T> matrix;
    while (true) {
        system("cls");
        print_matrix(matrixA, MATRIX_A);
        print_matrix(matrixB, MATRIX_B);
        print_matrix(matrixC, MATRIX_C);

        int operation = select_matrix_operations();

        if (operation >= ADD && operation <= MULT) {
            char* mass3 = select_matrices();
            try {
                matrix = select_and_apply(operation, mass3[0], mass3[1], matrixA, matrixB, matrixC);
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Matrix operation error: " << e.what() << std::endl;
                system("pause");
                system("cls");
                delete mass3;
                continue;
            }
            delete mass3;
        }
        else if (operation == MULT_SCALAR) {
            int scalar = select_scalar();
            char matrix_char = select_matrix(true);

            matrix = start_scalar_operation(scalar, matrix_char, matrixA, matrixB, matrixC);
        }
        else if (operation == EXIT) return;
        print_result(matrixA, matrixB, matrixC, matrix);
        std::cout << "\nSAVE\n";
        std::cout << "Select which matrix to save the result\n";
        char matrix_char = select_matrix(true);
        save_result(matrix_char, matrixA, matrixB, matrixC, matrix);
    }
}

template <class T>
bool initialize_matrix_C(TriangleMatrix<T>& matrixA, TriangleMatrix<T>& matrixB,
    TriangleMatrix<T>& matrixC) {
    while (true) {
        print_matrix(matrixA, MATRIX_A);
        print_matrix(matrixB, MATRIX_B);

        int operation = select_matrix_operations();

        if (operation >= ADD && operation <= MULT) {
            try {
                matrixC = start_binary_operation(operation, matrixA, matrixB);
                //matrixC = select_and_apply(operation, 'A', 'B', matrixA, matrixB, matrixC);
                break;
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Matrix operation error: " << e.what() << std::endl;
                system("pause");
                system("cls");
                continue;
            }
        }
        else if (operation == MULT_SCALAR) {
            int scalar = select_scalar();
            char matrix_char = select_matrix(false);

            matrixC = start_scalar_operation(scalar, matrix_char, matrixA, matrixB, matrixC);
            print_result(matrixA, matrixB, matrixC, matrixC);
            break;
        }
        else if (operation == EXIT) return true;
    }
    return false;
}

template <class T>
void process_matrix_operations(TriangleMatrix<T>& matrixA, TriangleMatrix<T>& matrixB,
    TriangleMatrix<T>& matrixC) {
    TriangleMatrix<T> matrix;
    while (true) {
        system("cls");
        print_matrix(matrixA, MATRIX_A);
        print_matrix(matrixB, MATRIX_B);
        print_matrix(matrixC, MATRIX_C);
        int operation = select_matrix_operations();

        if (operation >= ADD && operation <= MULT) {
            char* mass3 = select_matrices();
            try {
                matrix = select_and_apply(operation, mass3[0], mass3[1], matrixA, matrixB, matrixC);
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Matrix operation error: " << e.what() << std::endl;
                system("pause");
                system("cls");
                delete mass3;
                continue;
            }
            delete mass3;
        }
        else if (operation == MULT_SCALAR) {
            int scalar = select_scalar();
            char matrix_char = select_matrix(true);

            matrix = start_scalar_operation(scalar, matrix_char, matrixA, matrixB, matrixC);
        }
        else if (operation == EXIT) return;
        print_result(matrixA, matrixB, matrixC, matrix);
        std::cout << "\nSAVE\n";
        std::cout << "Select which matrix to save the result\n";
        char matrix_char = select_matrix(true);
        save_result(matrix_char, matrixA, matrixB, matrixC, matrix);
    }
}

template <class T>
TriangleMatrix<T> start_scalar_operation(int scalar, char matrix_char, const TriangleMatrix<T>& matrixA,
    const TriangleMatrix<T>& matrixB, const TriangleMatrix<T>& matrixC) {
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

template <class T>
Matrix<T> start_scalar_operation(int scalar, char matrix_char, const Matrix<T>& matrixA, 
    const Matrix<T>& matrixB, const Matrix<T>& matrixC) {
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

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return mass;
}

int enter_tmatrix_size(int num) {
    int size_n;
    if (num == MATRIX_A) std::cout << "MATRIX SIZE\nEnter the size of triangular matrix A (one number): ";
    else if (num == MATRIX_B) std::cout << "MATRIX SIZE\nEnter the size of triangular matrix B (one number): ";
    else if (num == MATRIX_C) std::cout << "MATRIX SIZE\nEnter the size of triangular matrix C (one number): ";
    else std::cout << "MATRIX SIZE\nEnter the size of triangular matrix (one number): ";

    while (1) {
        std::cin >> size_n;
        if (size_n > 0) break;
        std::cout << "Incorrect input, please try again: ";
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return size_n;
}

template <class T>
void enter_matrix(Matrix<T>& matr, int num) {
    if (num == MATRIX_A) std::cout << "Enter the matrix A\n";
    else if (num == MATRIX_B) std::cout << "Enter the matrix B\n";
    else if (num == MATRIX_C) std::cout << "Enter the matrix C\n";
    else std::cout << "Enter the matrix\n";

#ifdef DEBUG
    std::cout << "*Matrix input will be here*\n";
    system("pause");
#else
    std::cin >> matr;
#endif
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template <class T>
void enter_matrix(TriangleMatrix<T>& matr, int num) {
    if (num == MATRIX_A) std::cout << "Enter the matrix A\n";
    else if (num == MATRIX_B) std::cout << "Enter the matrix B\n";
    else if (num == MATRIX_C) std::cout << "Enter the matrix C\n";
    else std::cout << "Enter the matrix\n";

#ifdef DEBUG
    std::cout << "*Matrix input will be here*\n";
    system("pause");
#else
    std::cin >> matr;
#endif
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
    if (isC) {
        std::cout << "Select the matrix (A, B or C): ";
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
        std::cout << "Select the matrix (A or B): ";
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

template <class T>
Matrix<T> start_binary_operation(int operation, const Matrix<T>& matrix1, const Matrix<T>& matrix2) {
    Matrix<T> matrix;

    switch (operation) {
    case ADD: {
        try {
            matrix = matrix1 + matrix2;
        }
        catch (const std::invalid_argument& e) {
            throw;
        }

    } break;
    case SUB: {
        try {
            matrix = matrix1 - matrix2;
        }
        catch (const std::invalid_argument& e) {
            throw;
        }

    } break;
    case MULT: {
        try {
            matrix = matrix1 * matrix2;
        }
        catch (const std::invalid_argument& e) {
            throw;
        }
    }
    }
    return matrix;
}

template <class T>
TriangleMatrix<T> start_binary_operation(int operation, const TriangleMatrix<T>& matrix1,
    const TriangleMatrix<T>& matrix2) {
    TriangleMatrix<T> matrix;

    switch (operation) {
    case ADD: {
        try {
            matrix = matrix1 + matrix2;
        }
        catch (const std::invalid_argument& e) {
            throw;
        }

    } break;
    case SUB: {
        try {
            matrix = matrix1 - matrix2;
        }
        catch (const std::invalid_argument& e) {
            throw;
        }

    } break;
    case MULT: {
        try {
            matrix = matrix1 * matrix2;
        }
        catch (const std::invalid_argument& e) {
            throw;
        }
    }
    }
    return matrix;
}

template <class T>
Matrix<T> select_and_apply(int operation, char matrix1, char matrix2, const Matrix<T>& matrixA,
    const Matrix<T>& matrixB, const Matrix<T>& matrixC) {
    if (matrix1 == 'A') {
        if (matrix2 == 'A') return start_binary_operation(operation, matrixA, matrixA);
        else if (matrix2 == 'B') return start_binary_operation(operation, matrixA, matrixB);
        else if (matrix2 == 'C') return start_binary_operation(operation, matrixA, matrixC);
    }
    else if (matrix1 == 'B') {
        if (matrix2 == 'A') return start_binary_operation(operation, matrixB, matrixA);
        else if (matrix2 == 'B') return start_binary_operation(operation, matrixB, matrixB);
        else if (matrix2 == 'C') return start_binary_operation(operation, matrixB, matrixC);
    }
    else if (matrix1 == 'C') {
        if (matrix2 == 'A') return start_binary_operation(operation, matrixC, matrixA);
        else if (matrix2 == 'B') return start_binary_operation(operation, matrixC, matrixB);
        else if (matrix2 == 'C') return start_binary_operation(operation, matrixC, matrixC);
    }
}

template <class T>
TriangleMatrix<T> select_and_apply(int operation, char matrix1, char matrix2, const TriangleMatrix<T>& matrixA,
    const TriangleMatrix<T>& matrixB, const TriangleMatrix<T>& matrixC) {
    if (matrix1 == 'A') {
        if (matrix2 == 'A') return start_binary_operation(operation, matrixA, matrixA);
        else if (matrix2 == 'B') return start_binary_operation(operation, matrixA, matrixB);
        else if (matrix2 == 'C') return start_binary_operation(operation, matrixA, matrixC);
    }
    else if (matrix1 == 'B') {
        if (matrix2 == 'A') return start_binary_operation(operation, matrixB, matrixA);
        else if (matrix2 == 'B') return start_binary_operation(operation, matrixB, matrixB);
        else if (matrix2 == 'C') return start_binary_operation(operation, matrixB, matrixC);
    }
    else if (matrix1 == 'C') {
        if (matrix2 == 'A') return start_binary_operation(operation, matrixC, matrixA);
        else if (matrix2 == 'B') return start_binary_operation(operation, matrixC, matrixB);
        else if (matrix2 == 'C') return start_binary_operation(operation, matrixC, matrixC);
    }
}

int select_scalar() {
    int scalar;
    std::cout << "Enter a scalar (integer): ";
    std::cin >> scalar;
    return scalar;
}

#endif  // MATRIX_INTERFACE
