#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "bstree.h"
#include "heap.h"
#include "pqueue.h"
#include <string>

#define SIZE 10
//#define TREE_SORT
//#define HEAP_SORT
#define PRIORITY_QUEUE

int main() {
	srand(static_cast<unsigned int>(time(0)));
#ifdef TREE_SORT
	BSTree<int, int> t;
	int mass[SIZE];

	for (int i = 0; i < SIZE; i++) {
		int c = rand() % 100;
		mass[i] = c;
	}
	
	for (int i = 0; i < SIZE; i++) {
		try {
			t.insert(mass[i], mass[i]);
		}
		catch (...) {}
	}

	t.print_lcr();
#endif
#ifdef HEAP_SORT
	Heap<int> h;
	int mass[SIZE];
	for (int i = 0; i < SIZE; i++) {
		int c = rand() % 100;
		mass[i] = c;
	}
	for (int i = 0; i < SIZE; i++) {
		h.insert(mass[i]);
	}

	while (!(h.is_empty())) {
		std::cout << h.get_min() << " ";
		h.pop();
	}
#endif
#ifdef PRIORITY_QUEUE 
	/*
	setlocale(LC_ALL, "rus");
	PQueue<int> q;
	int k;
	std::cout << "Введите количество приоритетных элементов: ";
	while (true) {
		std::cin >> k;
		if (k > 0) break;
		std::cout << "\nНекорректный ввод, попробуйте снова: ";
	}
	std::cout << "Порядок вставки: ";
	for (int i = 0; i < k * 2; i++) {
		int item = rand() % 100;
		int priority = rand() % 6;
		Pair<int> pair(priority, item, i);
		q.insert(pair);
		std::cout << "Приоритет: " << priority << " значение: " << item << std::endl;
	}

	std::cout << "\n" << k << " приоритетных элементов:\n";
	for (int i = 0; i < k; i++) {
		std::cout << "Приоритет: " << q.top().priority << " значение: " << q.top().value << std::endl;
		q.pop();
	}
	*/
	setlocale(LC_ALL, "rus");
	PQueue<std::string> q;
	int k;
	std::cout << "Введите количество приоритетных элементов: ";
	std::cin >> k;
	std::cout << "Порядок вставки: ";
	for (int i = 0; i < k * 2; i++) {
		std::string item = std::to_string(rand() % 100);
		int priority = rand() % 6;
		Pair<std::string> pair(priority, item, i);
		q.insert(pair);
		std::cout << "Приоритет: " << priority << " значение: " << item << std::endl;
	}

	std::cout << "\n" << k << " приоритетных элементов:\n";
	for (int i = 0; i < k; i++) {
		std::cout << "Приоритет: " << q.top().priority << " значение: " << q.top().value << std::endl;
		q.pop();
	}
#endif
}


