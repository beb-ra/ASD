#include <gtest/gtest.h>
#include "../lib_uns_table_list/uns_table_list.h"

TEST(TestUnsTableListLib, correct_create) {
	UnsortedTableList<int, int> t;

	EXPECT_TRUE(t.rows().is_empty());
}

TEST(TestUnsTableListLib, correct) {
	UnsortedTableList<int, int> t;
	t.insert(3, 4);
	t.insert(1, 2);
	t.insert(3, 111);

	EXPECT_EQ(*(t.found(1)), 2);
	EXPECT_EQ(*(t.found(3)), 111);

	std::cout << t;

	t.erase(1);

	std::cout << t;

	t.erase(3);
	EXPECT_TRUE(t.rows().is_empty());
	EXPECT_THROW(t.erase(5), std::logic_error);
}