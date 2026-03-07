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
	t.insert(4, 4);
	t.insert(1, 2);
	t.insert(1, 3);
	std::cout << (*t.find(1)) << " ";

	t.insert(2, 2);
	t.insert(2, 3);
	t.insert(2, 4);

	std::cout << (*t.find(2)) << " ";

	std::cout << (*t.find(1)) << " ";
	std::cout << (*t.find(4)) << " ";
	std::cout << t.find(5) << "\n";

	t.print_clr();
	t.print_lcr();
	t.print_lrc();
	t.print_w();

	t.erase(4);
	t.print_w();

	t.erase(1);
	t.print_w();

	t.erase(2);
	t.print_w();

	t.erase(2);
	t.print_w();

	t.erase(2);
    t.print_w();

	t.erase(1);
	t.print_w();

	t.erase(1);
	t.print_w();
}

#endif  // EASY_EXAMPLE
