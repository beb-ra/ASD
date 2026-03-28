#include <gtest/gtest.h>
#include <iostream>
#include "../lib_sort_table_bst/sort_table_bst.h"

TEST(TestSortTableBSTLib, correct_create) {
	SortedTableBST<int, int> t;

	EXPECT_TRUE(t.rows().is_empty());
}

TEST(TestSortTableBSTLib, correct_insert_found_and_erase) {
	SortedTableBST<int, int> t;
	t.insert(1, 2);
	t.insert(3, 4);
	t.insert(11, 11);
	EXPECT_THROW(t.insert(3, 111), std::logic_error);

	std::cout << t;

	EXPECT_EQ(*(t.found(1)), 2);
	EXPECT_EQ(*(t.found(11)), 11);

	t.erase(1);
	t.erase(11);
	t.erase(3);

	EXPECT_EQ(t.found(1), nullptr);
	EXPECT_EQ(t.found(11), nullptr);
	EXPECT_TRUE(t.rows().is_empty());

	EXPECT_THROW(t.erase(3), std::logic_error);
	EXPECT_THROW(t.erase(5), std::logic_error);
}

TEST(TestSortTableBSTLib, correct_erase) {
	SortedTableBST<int, int> t;
	SortedTableBST<int, int> expected;

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