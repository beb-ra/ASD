#include <gtest/gtest.h>
#include <iostream>
#include "../lib_bstree/bstree.h"

TEST(TestBSTreeLib, correct_create) {
	BSTree<int, int> t;

	EXPECT_TRUE(t.is_empty());
}

TEST(TestBSTreeLib, correct_insert_found_and_erase_leaf) {
	BSTree<int, int> t;
	t.insert(3, 3);
	t.insert(1, 1);
	t.insert(4, 4);
	t.insert(2, 2);

	EXPECT_EQ(t.find(1)->_data.value, 1);
	EXPECT_EQ(t.find(2)->_data.value, 2);
	EXPECT_EQ(t.find(4)->_data.value, 4);
	EXPECT_EQ(t.find(3)->_data.value, 3);
	EXPECT_EQ(t.find(5), nullptr);

	std::cout << t;

	t.erase(4);
	EXPECT_EQ(t.find(4), nullptr);
	std::cout << t;

	t.erase(2);
	EXPECT_EQ(t.find(2), nullptr);
	std::cout << t;

	t.erase(1);
	EXPECT_EQ(t.find(1), nullptr);
	std::cout << t;

	t.erase(3);
	EXPECT_EQ(t.find(3), nullptr);
	std::cout << t;
}

TEST(TestBSTreeLib, correct_erase_node_with_multi_children) {
	BSTree<int, int> t;
	t.insert(3, 3);
	t.insert(1, 1);
	t.insert(5, 5);
	t.insert(2, 2);
	t.insert(4, 4);
	t.insert(6, 6);

	std::cout << t;

	t.erase(5);
	EXPECT_EQ(t.find(5), nullptr);
	EXPECT_EQ(t.find(3)->_right->_data.key, 6);
	EXPECT_EQ(t.find(3)->_right->_left->_data.key, 4);
	std::cout << t;

	t.erase(6);
	EXPECT_EQ(t.find(6), nullptr);
	EXPECT_EQ(t.find(3)->_right->_data.key, 4);
	std::cout << t;

	t.erase(3);
	EXPECT_EQ(t.find(3), nullptr);
	EXPECT_EQ(t.find(4)->_left->_data.key, 1);
	EXPECT_EQ(t.find(4)->_left->_right->_data.key, 2);
	EXPECT_EQ(t.find(4)->_right, nullptr);
	std::cout << t;

	t.insert(5, 5);
	t.insert(9, 9);
	t.erase(4);
	EXPECT_EQ(t.find(5)->_right->_data.key, 9);
	EXPECT_EQ(t.find(5)->_right->_left, nullptr);
	EXPECT_EQ(t.find(5)->_left->_data.key, 1);
	std::cout << t;
}


TEST(TestBSTreeLib, correct_erase_root) {
	BSTree<int, int> t;
	EXPECT_THROW(t.erase(3), std::logic_error);

	t.insert(3, 3);
	t.insert(5, 5);
	t.insert(2, 2);

	t.erase(3);
	EXPECT_EQ(t.find(5)->_data.value, 5);
	EXPECT_EQ(t.find(5)->_left->_data.value, 2);
	EXPECT_EQ(t.find(3), nullptr);
}

TEST(TestBSTreeLib, throw_uncorrect_insert) {
	BSTree<int, int> t;
	EXPECT_THROW(t.erase(3), std::logic_error);

	t.insert(3, 3);
	EXPECT_THROW(t.insert(3, 3), std::logic_error);
	EXPECT_THROW(t.insert(3, 4), std::logic_error);
	t.insert(5, 5);
	t.insert(2, 2);
	EXPECT_THROW(t.insert(2, 2), std::logic_error);
}

TEST(TestBSTreeLib, beauty_print) {
	BSTree<int, int> t;
	t.insert(1000, 13);
	t.insert(4, 4);
	t.insert(10, 20000);
	t.insert(1, 3);

	t.insert(200, 2);
	t.insert(2, 3000000);
	t.insert(20, 45);

	std::cout << t;

	t.print_clr();
	t.print_lcr();
	t.print_lrc();
}