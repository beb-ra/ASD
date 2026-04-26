// Copyright 2024 Marina Usova

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <clocale>
#include "algorithms.h"
#include "graph_on_list_adj.h"

#define LABYRINTH

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
	/*
	std::vector<std::pair<std::pair<int, int>, int>> data = {
		{{1, 2}, 3},
		{{4, 5}, 6},
		{{7, 8}, 9}
	};

	LGraph<int> graph(data, true, true);

	graph.add_edge(2, 7, 5);

	graph.add_edge(1, 5, 5);
	graph.add_edge(5, 8, 1);

	graph.add_edge(1, 8, 8);

	List<int> list = graph.find_min_way(1, 8);
	for (auto it = list.begin(); it != list.end(); it++) {
		std::cout << *it << " ";
	}
	*/
	return 0;
}

