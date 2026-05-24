#pragma once
#include <iostream>
#include "../lib_stack/stack.h"
#include "../lib_matrix/matrix.h"

enum LocationTypes { intersect, touch, inside, not_intersect };

template <class T>
LocationTypes figures_comparison(T first, T second) {
    double distance = calculate_total_diameter(first, second);
    double radius_sum = first._radius + second._radius;
    double radius_diff = std::abs(static_cast<double>(first._radius) - static_cast<double>(second._radius));

    if (distance > radius_sum) {
        return LocationTypes::not_intersect;
    }
    else if (std::abs(distance - radius_sum) < 1e-10 ||
        std::abs(distance - radius_diff) < 1e-10) {
        return LocationTypes::touch;
    }
    else if (distance <= radius_diff) {
        return LocationTypes::inside;
    }
    else {
        return LocationTypes::intersect;
    }
}

template <class T>
double calculate_total_diameter(T& first, T& second) {
    return first.calculate_distance(second.get_center());
}

bool check_brackets(std::string str);
void read_expression(std::string expression);
bool is_math_operation(char item);
bool is_number(char item);
bool is_variable(char item);

template <class T>
int local_min(Matrix<T>& matrix, int i, int j) {
	int start_elem = matrix[i][j];

	if (j > 0 && matrix[i][j - 1] < start_elem) {  //левый
		return local_min(matrix, i, j - 1);
	}
	else if (j < matrix.get_m() - 1 && matrix[i][j + 1] < start_elem) {  //правый
		return local_min(matrix, i, j + 1);
	}
	else if (i > 0 && matrix[i - 1][j] < start_elem) { //сверху
		return local_min(matrix, i - 1, j);
	}
	else if (i < matrix.get_n() - 1 && matrix[i + 1][j] < start_elem) { //снизу
		return local_min(matrix, i + 1, j);
	}
	else return start_elem;
}
