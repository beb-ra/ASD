#include <gtest/gtest.h>
#include <iostream>
#include "../lib_tree/tree.h"

TEST(TestTreeLib, correct_create) {
	Tree<int, int> t;

	EXPECT_TRUE(t.is_empty());
}

TEST(TestTreeLib, correct_insert_found_and_erase) {
	Tree<int, int> t;
	t.insert(1, 1);
	t.insert(4, 4);
	t.insert(1, 2);
	t.insert(1, 3);

	EXPECT_EQ(t.find(1)->_data.value, 1);

	t.insert(2, 2);
	t.insert(2, 3);
	t.insert(2, 4);

	EXPECT_EQ(t.find(2)->_data.value, 2);
	EXPECT_EQ(t.find(1)->_data.value, 1);
	EXPECT_EQ(t.find(4)->_data.value, 4);
	EXPECT_EQ(t.find(5), nullptr);

	t.print_clr();
	t.print_lcr();
	t.print_lrc();
	t.print_w();

	std::cout << t;

	t.erase(4);
	EXPECT_EQ(t.find(4), nullptr);
	EXPECT_EQ(t.find(2)->_data.value, 4);

	t.erase(1);
	EXPECT_EQ(t.find(2)->_data.value, 3);

	t.erase(2);
	EXPECT_EQ(t.find(2)->_data.value, 2);
	EXPECT_EQ(t.find(1)->_data.value, 2);

	t.erase(2);
	EXPECT_EQ(t.find(2)->_data.value, 4);
	EXPECT_EQ(t.find(1)->_data.value, 3);

	t.erase(2);
	EXPECT_EQ(t.find(1)->_data.value, 3);

	t.erase(1);
	t.erase(1);

	EXPECT_EQ(t.find(1), nullptr);
	EXPECT_TRUE(t.is_empty());
}

TEST(TestTreeLib, correct_clear) {
	Tree<int, int> t;
	t.insert(1, 1);
	t.insert(4, 4);
	t.insert(1, 2);
	t.insert(1, 3);

	t.insert(2, 2);
	t.insert(2, 3);
	t.insert(2, 4);

	t.clear();
	EXPECT_TRUE(t.is_empty());
}

TEST(TestTreeLib, beauty_print) {
	Tree<int, int> t;
	t.insert(1000, 13);
	t.insert(4, 4);
	t.insert(10, 20000);
	t.insert(1, 3);

	t.insert(200, 2);
	t.insert(2, 3000000);
	t.insert(20, 45);

	std::cout << t;
}
