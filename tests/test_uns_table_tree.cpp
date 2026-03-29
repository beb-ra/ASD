#include <gtest/gtest.h>
#include "../lib_uns_table_tree/uns_table_tree.h"

TEST(TestUnsTableTreeLib, correct_create) {
	UnsortedTableTree<int, int> t;

	EXPECT_TRUE(t.rows().is_empty());
}

TEST(TestUnsTableTreeLib, correct_insert_found_and_erase) {
	UnsortedTableTree<int, int> t;
	t.insert(3, 4);
	t.insert(1, 2);
	t.insert(11, 11);
	EXPECT_THROW(t.insert(3, 333), std::logic_error);

	std::cout << t;

	EXPECT_EQ(*(t.found(1)), 2);
	EXPECT_EQ(*(t.found(3)), 4);

	t.erase(1);
	t.erase(3);

	std::cout << t;

	EXPECT_EQ(t.found(1), nullptr);
	EXPECT_EQ(t.found(3), nullptr);
	EXPECT_FALSE(t.rows().is_empty());

	EXPECT_THROW(t.erase(3), std::logic_error);
	EXPECT_THROW(t.erase(5), std::logic_error);
}

TEST(TestUnsTableTreeLib, correct_erase) {
	UnsortedTableTree<int, int> t;
	UnsortedTableTree<int, int> expected;

	for (int i = 0; i < 5; i++) {
		t.insert((i + 1) * 100, (i + 1) * 100);
	}
	expected.insert(200, 200);
	expected.insert(400, 400);

	std::cout << t;

	t.erase(100);
	t.erase(300);
	t.erase(500);

	std::cout << t;

	t.erase(200);
	t.erase(400);

	EXPECT_TRUE(t.rows().is_empty());
}