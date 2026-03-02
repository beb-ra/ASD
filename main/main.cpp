// Copyright 2024 Marina Usova

#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "skiplist.h"

int main() {
	Skiplist<int, int> slist;
	slist.insert(3, 3);
	slist.insert(6, 6);
	slist.insert(7, 7);
	slist.insert(9, 9);
	slist.insert(12, 12);
	slist.insert(19, 19);
	slist.insert(17, 17);
	slist.insert(26, 26);
	slist.insert(21, 21);
	slist.insert(25, 25);
	slist.print();
}

#endif  // EASY_EXAMPLE
