// Copyright 2024 Marina Usova

#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "polynom.h"

int main() {
	Polynom m("p", "x^2yz + 5x - 3z + 2x + 0");
	std::cout << m;
}

#endif  // EASY_EXAMPLE
