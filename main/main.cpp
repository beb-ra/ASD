#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "bstree.h"
#include "heap.h"

#define SIZE 10
//#define TREE_SORT
#define HEAP_SORT

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
}


