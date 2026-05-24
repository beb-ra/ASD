#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "bstree.h"
#include "heap.h"
#include "pqueue.h"
#include <string>
#include "hash_table_container.h"
#include "hashc_table_container.h"
#include "polynom.h"
#include "avltree.h"

#include "table.h"
#include "rbtree.h"
#include "list_container.h"

#include <fstream>
#include <sstream>
#include <chrono>

#define SIZE 10
//#define TREE_SORT
//#define HEAP_SORT
//#define PRIORITY_QUEUE
//#define DICTIONARIES_MERGING

#define COEFF_MAX 1000000
#define POW_MAX 1000

#define COUNT_NOT_EXIST_KEYS 5

int main() {
	srand(static_cast<unsigned int>(time(0)));
	for (int iii = 0; iii < 10; iii++) {
		Table<RBTree, std::string, Polynom> table;

		auto totalInsertTime = std::chrono::microseconds::zero();

		std::vector<std::string> exist_keys;

		std::ifstream in("polynoms.txt");
		std::string line;
		int polynoms_count = 0;
		while (std::getline(in, line)) {
			if (line.empty()) continue;
			size_t sepPos = line.find(';');
			if (sepPos == std::string::npos) continue;

			std::string name = line.substr(0, sepPos);
			Polynom p(name);

			std::string rest = line.substr(sepPos + 1);
			std::stringstream ss(rest);
			std::string monomStr;

			while (std::getline(ss, monomStr, ';')) {
				std::stringstream monomSs(monomStr);
				std::string numStr;
				int coeff, pow1, pow2, pow3;

				std::getline(monomSs, numStr, ','); coeff = std::stoi(numStr);
				std::getline(monomSs, numStr, ','); pow1 = std::stoi(numStr);
				std::getline(monomSs, numStr, ','); pow2 = std::stoi(numStr);
				std::getline(monomSs, numStr, ','); pow3 = std::stoi(numStr);

				Monom m(coeff, { pow1, pow2, pow3 });
				p += m;
			}
			auto start_insert = std::chrono::high_resolution_clock::now();
			table.insert(p.name(), p);
			auto end_insert = std::chrono::high_resolution_clock::now();
			totalInsertTime += std::chrono::duration_cast<std::chrono::microseconds>(end_insert - start_insert);
			polynoms_count++;

			exist_keys.push_back(p.name());

			//if (polynoms_count == 10000) break;
		}

		std::cout << "Total insert time: " << totalInsertTime.count() / 1000000.0 << " sec" << std::endl; // микросекунды

		std::random_shuffle(exist_keys.begin(), exist_keys.end());

		auto start_find = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < exist_keys.size(); i++) {
			if (i <= COUNT_NOT_EXIST_KEYS) {
				table.found(exist_keys[i] + "pupupu");
			}
			else {
				table.found(exist_keys[i]);
			}
		}
		auto end_find = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> totalFindTime = end_find - start_find;

		std::cout << "Total find time: " << totalFindTime.count() << " sec" << std::endl;

		auto start_erase = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < exist_keys.size(); i++) {
			table.erase(exist_keys[i]);
		}
		auto end_erase = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> totalEraseTime = end_erase - start_erase;

		std::cout << "Total erase time: " << totalEraseTime.count() << " sec" << std::endl;
	}
	return 0;
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

	Table<HashTableContainerOA, std::string, int> table;

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
	*/
	TVector<std::pair<std::string, int>> dict1;
	TVector<std::pair<std::string, int>> dict2;

	dict1.push_back(std::pair<std::string, int>("table", 1349));
	dict1.push_back(std::pair<std::string, int>("hash", 1985));
	dict1.push_back(std::pair<std::string, int>("list", 4372));

	dict2.push_back(std::pair<std::string, int>("massive", 4312));
	dict2.push_back(std::pair<std::string, int>("list", 5863));
	dict2.push_back(std::pair<std::string, int>("hash", 4317));
	dict2.push_back(std::pair<std::string, int>("vector", 2586));

	Table<HashTableContainerC, std::string, int> table;

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
}


