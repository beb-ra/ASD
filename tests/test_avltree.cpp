#include <gtest/gtest.h>
#include <iostream>
#include "../lib_avltree/avltree.h"

TEST(TestAVLTreeLib, correct_create) {
	AVLTree<int, int> t;

	EXPECT_TRUE(t.is_empty());
}

TEST(TestAVLTreeLib, correct_insert_found_and_erase_leaf) {
	AVLTree<int, int> t;
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

TEST(TestAVLTreeLib, correct_erase_node_with_multi_children) {
	AVLTree<int, int> t;
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


TEST(TestAVLTreeLib, correct_erase_root) {
	AVLTree<int, int> t;
	EXPECT_THROW(t.erase(3), std::logic_error);

	t.insert(3, 3);
	t.insert(5, 5);
	t.insert(2, 2);

	t.erase(3);
	EXPECT_EQ(t.find(5)->_data.value, 5);
	EXPECT_EQ(t.find(5)->_left->_data.value, 2);
	EXPECT_EQ(t.find(3), nullptr);
}

TEST(TestAVLTreeLib, throw_uncorrect_insert) {
	AVLTree<int, int> t;
	EXPECT_THROW(t.erase(3), std::logic_error);

	t.insert(3, 3);
	EXPECT_THROW(t.insert(3, 3), std::logic_error);
	EXPECT_THROW(t.insert(3, 4), std::logic_error);
	t.insert(5, 5);
	t.insert(2, 2);
	EXPECT_THROW(t.insert(2, 2), std::logic_error);
}