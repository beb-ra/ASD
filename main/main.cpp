// Copyright 2024 Marina Usova

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <clocale>
#include "algorithms.h"

int main() {
	setlocale(LC_ALL, "rus");
	int h, w, x, y;
	std::cout << "¬ведите высоту лабиринта: ";
	std::cin >> h;
	std::cout << "¬ведите ширину лабиринта: ";
	std::cin >> w;
	std::cout << "¬ведите номер €чейки входа в лабиринт: ";
	std::cin >> x;
	std::cout << "¬ведите номер €чейки выхода из лабиринта: ";
	std::cin >> y;
	Matrix<bool> answer = generate(x, y, h, w);
	print_lab(answer, h, w, x, y);
	return 0;
}
