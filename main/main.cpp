// Copyright 2024 Marina Usova

#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "skiplist.h"

int main() {
	Skiplist<int, int> slist;
	slist.insert(1, 1);
	slist.insert(3, 3);
	slist.insert(6, 6);
	slist.insert(7, 7);
	slist.insert(12, 12);
	slist.insert(18, 18);
	slist.insert(16, 16);
	slist.insert(24, 24);
	slist.insert(20, 20);
	slist.insert(25, 25);
	slist.insert(19, 20);
	slist.print();
}

#endif  // EASY_EXAMPLE
