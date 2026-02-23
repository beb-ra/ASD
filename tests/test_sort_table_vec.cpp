#include <gtest/gtest.h>
#include "../lib_sort_table_vec/sort_table_vec.h"

TEST(TestSortTableVecLib, correct_create) {
	SortedTableV<int, int> t;

	EXPECT_TRUE(t.rows().is_empty());
}

TEST(TestSortTableVecLib, correct) {
	SortedTableV<int, int> t;
	t.insert(1, 2);
	t.insert(3, 4);

	std::cout << t;
	t.insert(3, 111);

	EXPECT_EQ(*(t.found(1)), 2);
	EXPECT_EQ(*(t.found(3)), 111);

	t.erase(1);
	std::cout << t;
	t.erase(3);

	EXPECT_TRUE(t.rows().is_empty());
	EXPECT_THROW(t.erase(5), std::logic_error);
}