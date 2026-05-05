// Copyright 2024 Marina Usova

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <clocale>
#include "algorithms.h"
//#include "graph_on_list_adj.h"

//#define LABYRINTH
#define MIN_WAY_IN_LAB

int main() {
#ifdef LABYRINTH
	setlocale(LC_ALL, "rus");
	int h, w, x, y;
	while (true) {
		std::cout << "¬ведите высоту лабиринта: ";
		std::cin >> h;
		std::cout << "¬ведите ширину лабиринта: ";
		std::cin >> w;
		std::cout << "¬ведите номер €чейки входа в лабиринт: ";
		std::cin >> x;
		std::cout << "¬ведите номер €чейки выхода из лабиринта: ";
		std::cin >> y;
		try {
			Matrix<bool> answer = generate(x, y, h, w);
			print_lab(answer, h, w, x, y);
			break;
		}
		catch (const std::exception& e) {
			system("cls");
			std::cout << "Ќекорректный ввод, ошибка: " << e.what() << "\nѕопробуйте еще раз\n";
		}
	}
#endif
#ifdef MIN_WAY_IN_LAB 
	setlocale(LC_ALL, "rus");
	int h, w, x, y;
	while (true) {
		std::cout << "¬ведите высоту лабиринта: ";
		std::cin >> h;
		std::cout << "¬ведите ширину лабиринта: ";
		std::cin >> w;
		std::cout << "¬ведите номер €чейки входа в лабиринт: ";
		std::cin >> x;
		std::cout << "¬ведите номер €чейки выхода из лабиринта: ";
		std::cin >> y;
		try {
			Matrix<bool> matrix = generate(x, y, h, w);
			print_lab_with_shortest_path(matrix, h, w, x, y);
			break;
		}
		catch (const std::exception& e) {
			system("cls");
			std::cout << "Ќекорректный ввод, ошибка: " << e.what() << "\nѕопробуйте еще раз\n";
		}
	}
#endif
	return 0;
}

