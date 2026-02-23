#include <gtest/gtest.h>
#include "../lib_uns_table_vec/uns_table_vec.h"

TEST(TestUnsTableVecLib, correct_create) {
	UnsortedTableV<int, int> t;

	EXPECT_TRUE(t.rows().is_empty());
}

TEST(TestUnsTableVecLib, correct) {
	UnsortedTableV<int, int> t;
	t.insert(3, 4);
	t.insert(1, 2);
	t.insert(3, 111);

	EXPECT_EQ(*(t.found(1)), 2);
	EXPECT_EQ(*(t.found(3)), 111);

	std::cout << t;

	t.erase(1);
	t.erase(3);
	EXPECT_TRUE(t.rows().is_empty());
	EXPECT_THROW(t.erase(5), std::logic_error);
}