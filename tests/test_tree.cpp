#include <gtest/gtest.h>
#include <iostream>
#include "../lib_tree/tree.h"

TEST(TestTreeLib, correct_create) {
	Tree<int, int> t;

	EXPECT_TRUE(t.is_empty());
}
/*
TEST(TestTreeLib, correct_insert_found_and_erase) {
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

	std::cout << t;

	t.erase(4);
	std::cout << t;

	t.erase(1);
	std::cout << t;

	t.erase(2);
	std::cout << t;

	t.erase(2);
	std::cout << t;

	t.erase(2);
	std::cout << t;

	t.erase(1);
	std::cout << t;

	t.erase(1);
	std::cout << t;
}
*/