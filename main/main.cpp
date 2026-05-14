//#include <iostream>
//#include <iomanip>
//#include <cstdlib>
//#include <ctime>
//#include "bstree.h"
//#include "heap.h"
//#include "pqueue.h"
//#include <string>
//#include "hash_table.h"
//#include "hashc_table.h"

#include "table.h"
#include "rbtree.h"

#define SIZE 10
//#define TREE_SORT
//#define HEAP_SORT
//#define PRIORITY_QUEUE
//#define DICTIONARIES_MERGING

int main() {
	srand(static_cast<unsigned int>(time(0)));

	Table<RBTree, int, int> table;
	
	//table.insert(1, 1);
	//std::cout << table;
/*
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
	/////
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
#ifdef DICTIONARIES_MERGING
	/*
	TVector<std::pair<std::string, int>> dict1;
	TVector<std::pair<std::string, int>> dict2;

	dict1.push_back(std::pair<std::string, int>("table", 1349));
	dict1.push_back(std::pair<std::string, int>("hash", 1985));
	dict1.push_back(std::pair<std::string, int>("list", 4372));

	dict2.push_back(std::pair<std::string, int>("massive", 4312));
	dict2.push_back(std::pair<std::string, int>("list", 5863));
	dict2.push_back(std::pair<std::string, int>("hash", 4317));
	dict2.push_back(std::pair<std::string, int>("vector", 2586));

	HashTableOA<int> table;
	for (int i = 0; i < 3; i++) {
		table.insert(dict1[i].first, dict1[i].second);
	}
	for (int i = 0; i < 4; i++) {
		try {
			table.insert(dict2[i].first, dict2[i].second);
		}
		catch (...) {}
	}

	std::cout << table;
	/////
	TVector<std::pair<std::string, int>> dict1;
	TVector<std::pair<std::string, int>> dict2;

	dict1.push_back(std::pair<std::string, int>("table", 1349));
	dict1.push_back(std::pair<std::string, int>("hash", 1985));
	dict1.push_back(std::pair<std::string, int>("list", 4372));

	dict2.push_back(std::pair<std::string, int>("massive", 4312));
	dict2.push_back(std::pair<std::string, int>("list", 5863));
	dict2.push_back(std::pair<std::string, int>("hash", 4317));
	dict2.push_back(std::pair<std::string, int>("vector", 2586));

	HashTableC<int> table;
	for (int i = 0; i < 3; i++) {
		table.insert(dict1[i].first, dict1[i].second);
	}
	for (int i = 0; i < 4; i++) {
		try {
			table.insert(dict2[i].first, dict2[i].second);
		}
		catch (...) {}
	}

	std::cout << table;
#endif
*/
	return 0;
}


