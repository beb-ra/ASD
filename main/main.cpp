// Copyright 2024 Marina Usova

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "algorithms.h"

int main() {
	Matrix<bool> answer = generate(0, 11, 3, 4);
	print_lab(answer, 3, 4);
	return 0;
}
