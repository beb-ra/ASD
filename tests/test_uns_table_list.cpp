#include <gtest/gtest.h>
#include "../lib_uns_table_list/uns_table_list.h"

TEST(TestUnsTableListLib, correct_create) {
	UnsortedTableList<int, int> t;

	EXPECT_TRUE(t.rows().is_empty());
}

TEST(TestUnsTableListLib, correct_insert_found_and_erase) {
	UnsortedTableList<int, int> t;
	t.insert(3, 4);
	t.insert(1, 2);
	t.insert(3, 111);

	std::cout << t;

	EXPECT_EQ(*(t.found(1)), 2);
	EXPECT_EQ(*(t.found(3)), 111);

	t.erase(1);
	std::cout << t;
	t.erase(3);

	EXPECT_TRUE(t.rows().is_empty());
	EXPECT_THROW(t.erase(5), std::logic_error);
}

TEST(TestUnsTableListLib, correct_erase) {
	UnsortedTableList<int, int> t;
	UnsortedTableList<int, int> expected;
	
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