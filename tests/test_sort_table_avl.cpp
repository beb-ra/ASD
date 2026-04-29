#include <gtest/gtest.h>
#include <iostream>
#include "../lib_sort_table_avl/sort_table_avl.h"

TEST(TestSortTableAVLTreeLib, correct_create) {
	SortedTableAVL<int, int> t;

	EXPECT_TRUE(t.rows().is_empty());
}

TEST(TestSortTableAVLTreeLib, correct_insert_found_and_erase) {
	SortedTableAVL<int, int> t;
	t.insert(11, 11);
	t.insert(1, 2);
	t.insert(3, 4);
	EXPECT_THROW(t.insert(3, 111), std::logic_error);

	t.print();
	std::cout << t;

	EXPECT_EQ(*(t.found(1)), 2);
	EXPECT_EQ(*(t.found(11)), 11);

	t.erase(1);
	t.erase(3);

	EXPECT_EQ(t.found(1), nullptr);
	EXPECT_EQ(t.found(3), nullptr);

	EXPECT_THROW(t.erase(3), std::logic_error);
	EXPECT_THROW(t.erase(5), std::logic_error);
}

TEST(TestSortTableAVLTreeLib, correct_erase) {
	SortedTableAVL<int, int> t;
	SortedTableAVL<int, int> expected;

	for (int i = 0; i < 5; i++) {
		t.insert(i + 1, i + 1);
	}
	expected.insert(2, 2);
	expected.insert(4, 4);

	t.erase(1);
	t.erase(3);
	t.erase(5);

	std::cout << t;

	t.erase(2);
	t.erase(4);

	EXPECT_TRUE(t.rows().is_empty());
}