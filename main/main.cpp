// Copyright 2024 Marina Usova

#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "bstree.h"

#define SIZE 10

int main() {
	srand(static_cast<unsigned int>(time(0)));
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
}

#endif  // EASY_EXAMPLE
