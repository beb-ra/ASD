#include <gtest/gtest.h>
#include <iostream>
#include "../lib_rbtree/rbtree.h"

TEST(TestRBTreeLib, correct_create) {
	RBTree<int, int> t;
	EXPECT_TRUE(t.is_empty());

	t.insert(3, 3);
	t.insert(1, 1);
	t.insert(4, 4);
	t.insert(2, 2);

	RBTree<int, int> t2(t);

	EXPECT_EQ(t2.find(3)->_color, Color::black);
	EXPECT_EQ(t2.find(3)->_right->_data.key, 4);
	EXPECT_EQ(t2.find(3)->_left->_data.key, 1);
	EXPECT_EQ(t2.find(3)->_left->_right->_data.key, 2);
	EXPECT_FALSE(t.is_empty());

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
	t.insert(7, 7);
	EXPECT_EQ(t.find(3)->_color, Color::black);
	EXPECT_EQ(t.find(1)->_color, Color::black);
	EXPECT_EQ(t.find(4)->_color, Color::black);
	EXPECT_EQ(t.find(2)->_color, Color::red);
	EXPECT_EQ(t.find(7)->_color, Color::red);

	EXPECT_EQ(t.find(3)->_right->_data.key, 4);
	EXPECT_EQ(t.find(3)->_left->_data.key, 1);
	EXPECT_EQ(t.find(3)->_left->_right->_data.key, 2);
	EXPECT_EQ(t.find(3)->_right->_right->_data.key, 7);

	std::cout << t;
}

TEST(TestRBTreeLib, check_insert_with_recoloring_twice_without_rotations) {
	RBTree<int, int> t;
	t.insert(55, 55);
	t.insert(33, 33);
	t.insert(75, 75);
	t.insert(10, 10);
	t.insert(61, 61);
	t.insert(44, 44);
	t.insert(83, 83);
	t.insert(5, 5);
	t.insert(56, 56);
	t.insert(79, 79);
	t.insert(65, 65);
	t.insert(90, 90);
	t.insert(85, 85);

	std::cout << t;

	EXPECT_EQ(t.find(55)->_data.key, 55);
	EXPECT_EQ(t.find(55)->_left->_data.key, 33);
	EXPECT_EQ(t.find(55)->_left->_left->_data.key, 10);
	EXPECT_EQ(t.find(55)->_left->_right->_data.key, 44);
	EXPECT_EQ(t.find(55)->_left->_left->_left->_data.key, 5);
	EXPECT_EQ(t.find(55)->_right->_data.key, 75);
	EXPECT_EQ(t.find(55)->_right->_right->_data.key, 83);
	EXPECT_EQ(t.find(55)->_right->_right->_left->_data.key, 79);
	EXPECT_EQ(t.find(55)->_right->_right->_right->_data.key, 90);
	EXPECT_EQ(t.find(55)->_right->_left->_data.key, 61);
	EXPECT_EQ(t.find(55)->_right->_left->_left->_data.key, 56);
	EXPECT_EQ(t.find(55)->_right->_left->_right->_data.key, 65);
	EXPECT_EQ(t.find(55)->_right->_right->_right->_left->_data.key, 85);

	EXPECT_EQ(t.find(55)->_color, black);
	EXPECT_EQ(t.find(33)->_color, black);
	EXPECT_EQ(t.find(10)->_color, black);
	EXPECT_EQ(t.find(44)->_color, black);
	EXPECT_EQ(t.find(5)->_color, red);
	EXPECT_EQ(t.find(75)->_color, black);
	EXPECT_EQ(t.find(83)->_color, red);
	EXPECT_EQ(t.find(79)->_color, black);
	EXPECT_EQ(t.find(90)->_color, black);
	EXPECT_EQ(t.find(61)->_color, black);
	EXPECT_EQ(t.find(56)->_color, red);
	EXPECT_EQ(t.find(65)->_color, red);
	EXPECT_EQ(t.find(85)->_color, red);
	/*
		   [55]
		  /     \
		[33]    [75]
		/ \      /   \
	 [10] [44] [61]   (83)
	  /        / \     /  \
	(5)     (56) (65) [79] [90]
							/
						   (85)
	*/
}

TEST(TestRBTreeLib, correct_insert_with_cycle_and_rotations) {
	RBTree<float, float> t;
	t.insert(3, 3);
	EXPECT_EQ(t.find(3)->_color, Color::black);

	t.insert(1, 1);
	EXPECT_EQ(t.find(3)->_left->_data.key, 1);
	EXPECT_EQ(t.find(3)->_color, Color::black);
	EXPECT_EQ(t.find(1)->_color, Color::red);
	t.insert(4, 4);
	EXPECT_EQ(t.find(3)->_right->_data.key, 4);
	EXPECT_EQ(t.find(3)->_color, Color::black);
	EXPECT_EQ(t.find(1)->_color, Color::red);
	EXPECT_EQ(t.find(4)->_color, Color::red);
	t.insert(7, 7);
	EXPECT_EQ(t.find(3)->_right->_right->_data.key, 7);
	EXPECT_EQ(t.find(7)->_color, Color::red);
	EXPECT_EQ(t.find(3)->_color, Color::black);
	EXPECT_EQ(t.find(1)->_color, Color::black);
	EXPECT_EQ(t.find(4)->_color, Color::black);

	t.insert(11, 11);
	EXPECT_EQ(t.find(3)->_right->_right->_data.key, 11);
	EXPECT_EQ(t.find(3)->_color, Color::black);
	EXPECT_EQ(t.find(1)->_color, Color::black);
	EXPECT_EQ(t.find(7)->_color, Color::black);
	EXPECT_EQ(t.find(4)->_color, Color::red);
	EXPECT_EQ(t.find(11)->_color, Color::red);
	/*
	   [3]
	   / \
     [1] [7]
	     / \
	   (4)  (11)
	*/

	t.insert(13, 13);
	EXPECT_EQ(t.find(3)->_right->_right->_right->_data.key, 13);
	EXPECT_EQ(t.find(3)->_color, Color::black);
	EXPECT_EQ(t.find(1)->_color, Color::black);
	EXPECT_EQ(t.find(7)->_color, Color::red);
	EXPECT_EQ(t.find(4)->_color, Color::black);
	EXPECT_EQ(t.find(11)->_color, Color::black);
	/*
	   [3]
	   / \
	 [1] (7)
		 / \
	   [4]  [11]
	          \
			  (13)
	*/

	t.insert(12, 12);
	EXPECT_EQ(t.find(3)->_right->_right->_data.key, 12);
	EXPECT_EQ(t.find(3)->_color, Color::black);
	EXPECT_EQ(t.find(1)->_color, Color::black);
	EXPECT_EQ(t.find(7)->_color, Color::red);
	EXPECT_EQ(t.find(4)->_color, Color::black);
	EXPECT_EQ(t.find(11)->_color, Color::red);
	EXPECT_EQ(t.find(13)->_color, Color::red);
	EXPECT_EQ(t.find(12)->_color, Color::black);
	/*
	   [3]                        [3]
	   / \                        / \     
	 [1] (7)                    [1] (7)
		 / \                         / \
	   [4]  [11]        =>         [4]  [12] 
			  \                         /  \
			  (13)                    (11) (13)
			  /
			(12)
	*/
	t.insert(10, 10);
	EXPECT_EQ(t.find(7)->_color, Color::black);
	EXPECT_EQ(t.find(3)->_color, Color::red);
	EXPECT_EQ(t.find(1)->_color, Color::black);
	EXPECT_EQ(t.find(4)->_color, Color::black);
	EXPECT_EQ(t.find(11)->_color, Color::black);
	EXPECT_EQ(t.find(13)->_color, Color::black);
	EXPECT_EQ(t.find(12)->_color, Color::red);
	EXPECT_EQ(t.find(10)->_color, Color::red);

	EXPECT_EQ(t.find(7)->_right->_left->_left->_data.key, 10);
	EXPECT_EQ(t.find(7)->_right->_data.key, 12);
	EXPECT_EQ(t.find(7)->_left->_data.key, 3);
	EXPECT_EQ(t.find(7)->_right->_right->_data.key, 13);
	EXPECT_EQ(t.find(7)->_right->_left->_data.key, 11);
	EXPECT_EQ(t.find(7)->_left->_left->_data.key, 1);
	EXPECT_EQ(t.find(7)->_left->_right->_data.key, 4);
	/*
	   [3]                        [7]
	   / \                       /   \
	 [1] (7)                   (3)    (12)
		 / \                   / \    /  \
	   [4]  [12]        =>   [1] [4] [11] [13]
			 / \                      /  
		  (11) (13)                 (10) 
		   /
		 (10)
	*/
	std::cout << t;
}

TEST(TestRBTreeLib, correct_insert_with_rotations) {
	RBTree<int, int> t;
	t.insert(15, 15);
	t.insert(10, 10);
	t.insert(20, 20);
	t.insert(5, 5);
	t.insert(3, 3);
	t.insert(1, 1);
	t.insert(2, 2);

	EXPECT_EQ(t.find(15)->_color, Color::black);
	EXPECT_EQ(t.find(5)->_color, Color::red);
	EXPECT_EQ(t.find(20)->_color, Color::black);
	EXPECT_EQ(t.find(10)->_color, Color::black);
	EXPECT_EQ(t.find(2)->_color, Color::black);
	EXPECT_EQ(t.find(1)->_color, Color::red);
	EXPECT_EQ(t.find(3)->_color, Color::red);

	EXPECT_EQ(t.find(15)->_right->_data.key, 20);
	EXPECT_EQ(t.find(15)->_left->_data.key, 5);
	EXPECT_EQ(t.find(15)->_left->_right->_data.key, 10);
	EXPECT_EQ(t.find(15)->_left->_left->_data.key, 2);
	EXPECT_EQ(t.find(15)->_left->_left->_right->_data.key, 3);
	EXPECT_EQ(t.find(15)->_left->_left->_left->_data.key, 1);
	std::cout << t;
}

TEST(TestRBTreeLib, throw_uncorrect_insert) {
	RBTree<int, int> t;
	t.insert(3, 3);
	t.insert(1, 1);
	t.insert(4, 4);
	EXPECT_THROW(t.insert(4, 111), std::logic_error);
}