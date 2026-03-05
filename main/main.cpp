// Copyright 2024 Marina Usova

#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "polynom.h"
#include "tree.h"

int main() {
	//Polynom m("p", "x^2yz + 5x - 3z + 2x + 0");
	//std::cout << m;

	Tree<int, int> t;
	t.insert(1, 1);
	std::cout << t.find(1);
}

#endif  // EASY_EXAMPLE
