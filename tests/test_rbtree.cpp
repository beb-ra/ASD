#include <gtest/gtest.h>
#include <iostream>
#include "../lib_rbtree/rbtree.h"

TEST(TestRBTreeLib, correct_create) {
	RBTree<int, int> t;
	t.insert(3, 3);
	t.insert(1, 1);
	t.insert(4, 4);
	t.insert(2, 2);

	RBTree<int, int> t2(t);

	EXPECT_EQ(t2.find(3)->_color, Color::black);
	EXPECT_EQ(t2.find(3)->_right->_data.key, 4);
	EXPECT_EQ(t2.find(3)->_left->_data.key, 1);
	EXPECT_EQ(t2.find(3)->_left->_right->_data.key, 2);

	std::cout << t2;
}

TEST(TestRBTreeLib, correct_insert_with_recoloor_one_floor) {
	RBTree<int, int> t;
	t.insert(3, 3);
	EXPECT_EQ(t.find(3)->_color, Color::black);

	t.insert(1, 1);
	EXPECT_EQ(t.find(3)->_color, Color::black);
	EXPECT_EQ(t.find(1)->_color, Color::red);
	t.insert(4, 4);
	EXPECT_EQ(t.find(3)->_color, Color::black);
	EXPECT_EQ(t.find(1)->_color, Color::red);
	EXPECT_EQ(t.find(4)->_color, Color::red);
	t.insert(2, 2);
	EXPECT_EQ(t.find(3)->_color, Color::black);
	EXPECT_EQ(t.find(1)->_color, Color::black);
	EXPECT_EQ(t.find(4)->_color, Color::black);
	EXPECT_EQ(t.find(2)->_color, Color::red);

	std::cout << t;
}

TEST(TestRBTreeLib, correct_insert) {
	RBTree<float, float> t;
	t.insert(3, 3);
	EXPECT_EQ(t.find(3)->_color, Color::black);

	t.insert(1, 1);
	EXPECT_EQ(t.find(3)->_color, Color::black);
	EXPECT_EQ(t.find(1)->_color, Color::red);
	t.insert(4, 4);
	EXPECT_EQ(t.find(3)->_color, Color::black);
	EXPECT_EQ(t.find(1)->_color, Color::red);
	EXPECT_EQ(t.find(4)->_color, Color::red);

	std::cout << t;

	t.insert(7, 7);
	std::cout << t;

	t.insert(11, 11);
	std::cout << t;

	t.insert(13, 13);
	std::cout << t;

	t.insert(12, 12);
	std::cout << t;

	t.insert(10, 10);
	std::cout << t;
}