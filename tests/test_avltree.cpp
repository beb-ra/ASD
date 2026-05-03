#include <gtest/gtest.h>
#include <iostream>
#include "../lib_avltree/avltree.h"

TEST(TestAVLTreeLib, correct_create) {
	AVLTree<int, int> t;
	t.insert(3, 3);
	t.insert(1, 1);
	t.insert(4, 4);
	t.insert(2, 2);
	
	AVLTree<int, int> t2(t);

	EXPECT_EQ(t.find(3)->_data.value, 3);
	EXPECT_EQ(t.find(3)->_left->_data.value, 1);
	EXPECT_EQ(t.find(3)->_left->_right->_data.value, 2);
	EXPECT_EQ(t.find(3)->_right->_data.value, 4);

	std::cout << t2;
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
	std::cout << t;

	EXPECT_EQ(t.find(3), nullptr);
	EXPECT_EQ(t.find(2)->_left->_data.key, 1);
	EXPECT_EQ(t.find(2)->_right->_data.key, 4);
	EXPECT_EQ(t.find(4)->_right, nullptr);

	t.insert(5, 5);
	t.insert(9, 9);

	std::cout << t;

	EXPECT_EQ(t.find(2)->_right->_data.key, 5);
	EXPECT_EQ(t.find(2)->_right->_right->_data.key, 9);
	EXPECT_EQ(t.find(2)->_right->_left->_data.key, 4);
	EXPECT_EQ(t.find(2)->_left->_data.key, 1);

	t.erase(2);
	EXPECT_EQ(t.find(4)->_right->_data.key, 5);
	EXPECT_EQ(t.find(4)->_right->_right->_data.key, 9);
	EXPECT_EQ(t.find(4)->_left->_data.key, 1);
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

TEST(TestAVLTreeLib, throw_uncorrect_insert_and_erase) {
	AVLTree<int, int> t;
	EXPECT_THROW(t.erase(3), std::logic_error);

	t.insert(3, 3);
	EXPECT_THROW(t.insert(3, 3), std::logic_error);
	EXPECT_THROW(t.insert(3, 4), std::logic_error);
	t.insert(5, 5);
	t.insert(2, 2);
	EXPECT_THROW(t.insert(2, 2), std::logic_error);

	EXPECT_THROW(t.erase(10), std::logic_error);
}

TEST(TestAVLTreeLib, correct_insert_turns) {
	AVLTree<int, int> t;

	t.insert(4, 4);
	t.insert(5, 5);
	t.insert(7, 7);

	EXPECT_EQ(t.find(5)->_right->_data.value, 7);
	EXPECT_EQ(t.find(5)->_left->_data.value, 4);

	t.insert(2, 2);
	t.insert(1, 1);

	EXPECT_EQ(t.find(5)->_right->_data.value, 7);
	EXPECT_EQ(t.find(5)->_left->_data.value, 2);
	EXPECT_EQ(t.find(5)->_left->_right->_data.value, 4);
	EXPECT_EQ(t.find(5)->_left->_left->_data.value, 1);

	t.insert(3, 3);

	std::cout << t;

	EXPECT_EQ(t.find(4)->_right->_data.value, 5);
	EXPECT_EQ(t.find(4)->_right->_right->_data.value, 7);
	EXPECT_EQ(t.find(4)->_left->_data.value, 2);
	EXPECT_EQ(t.find(4)->_left->_right->_data.value, 3);
	EXPECT_EQ(t.find(4)->_left->_left->_data.value, 1);
	std::cout << t;
}

TEST(TestAVLTreeLib, correct_erase_turns) {
	AVLTree<int, int> t;

	t.insert(4, 4);
	t.insert(5, 5);
	t.insert(7, 7);
	t.insert(2, 2);
	t.insert(1, 1);
	t.insert(3, 3);

	std::cout << t;

	t.erase(7);
	t.erase(5);

	EXPECT_EQ(t.find(2)->_right->_data.value, 4);
	EXPECT_EQ(t.find(2)->_right->_left->_data.value, 3);
	EXPECT_EQ(t.find(2)->_left->_data.value, 1);
	std::cout << t;
}

TEST(TestAVLTreeLib, correct_erase_turns_2) {
	AVLTree<float, float> t;

	t.insert(5, 5);
	t.insert(3, 3);
	t.insert(7, 7);
	t.insert(1, 1);
	t.insert(6, 6);
	t.insert(4, 4);
	t.insert(8, 8);
	t.insert(0.5, 0.5);
	t.insert(5.5, 5.5);
	t.insert(7.5, 7.5);
	t.insert(6.5, 6.5);
	t.insert(9, 9);
	t.insert(8.5, 8.5);

	std::cout << t;

	t.erase(4);
	EXPECT_EQ(t.find(7)->_right->_right->_data.value, 9);
	EXPECT_EQ(t.find(7)->_right->_right->_left->_data.value, 8.5);
	EXPECT_EQ(t.find(7)->_right->_left->_data.value, 7.5);
	EXPECT_EQ(t.find(7)->_left->_left->_left->_data.value, 0.5);
	EXPECT_EQ(t.find(7)->_left->_left->_right->_data.value, 3);
	EXPECT_EQ(t.find(7)->_left->_left->_data.value, 1);
	EXPECT_EQ(t.find(7)->_left->_right->_right->_data.value, 6.5);
	EXPECT_EQ(t.find(7)->_left->_right->_left->_data.value, 5.5);
	EXPECT_EQ(t.find(7)->_left->_right->_data.value, 6);

	std::cout << t;
}

TEST(TestAVLTreeLib, check_heights_after_all_rotations) {
    AVLTree<int, int> t;

    t.insert(10, 10);
    t.insert(20, 20);
    t.insert(30, 30);

    EXPECT_EQ(t.find(20)->_height, 2);
    EXPECT_EQ(t.find(10)->_height, 1);
    EXPECT_EQ(t.find(30)->_height, 1);

    t.insert(5, 5);
    t.insert(1, 1);

    EXPECT_EQ(t.find(5)->_height, 2);
    EXPECT_EQ(t.find(1)->_height, 1);

    t.insert(7, 7);
	//      10
	//     /  \
	//    5   20
	//   / \
	//  1   7

	EXPECT_EQ(t.find(10)->_right->_data.value, 20);
	EXPECT_EQ(t.find(10)->_left->_data.value, 5);
	EXPECT_EQ(t.find(10)->_left->_right->_data.value, 7);
	EXPECT_EQ(t.find(10)->_left->_left->_data.value, 1);
    EXPECT_EQ(t.find(5)->_height, 2);
    EXPECT_EQ(t.find(7)->_height, 1);
	EXPECT_EQ(t.find(10)->_height, 3);
	EXPECT_EQ(t.find(20)->_height, 2);
}