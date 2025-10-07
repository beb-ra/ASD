#pragma once

#include "../lib_matrix/matrix.h"

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