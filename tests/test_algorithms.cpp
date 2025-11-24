#include <gtest/gtest.h>
#include "../lib_algorithms/algorithms.h"

TEST(TestAlgorithmsLib, correct_not_loop_1) {
	List<int> l;
	l.push_front(22);
	l.push_front(11);
	l.push_front(7);

	EXPECT_FALSE(is_looped_1(l));
}

TEST(TestAlgorithmsLib, correct_loop_1) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.tail()->next = l.head()->next;
	
	EXPECT_TRUE(is_looped_1(l));

	l.tail()->next = nullptr;
}

TEST(TestAlgorithmsLib, correct_loop_1_2) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.tail()->next = l.head();

	EXPECT_TRUE(is_looped_1(l));

	l.tail()->next = nullptr;
}

TEST(TestAlgorithmsLib, correct_not_loop_2) {
	List<int> l;
	l.push_front(22);
	l.push_front(11);
	l.push_front(7);

	EXPECT_FALSE(is_looped_2(l));
}

TEST(TestAlgorithmsLib, correct_loop_2) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.tail()->next = l.head()->next;

	EXPECT_TRUE(is_looped_2(l));

	l.tail()->next = nullptr;
}

TEST(TestAlgorithmsLib, correct_loop_2_2) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.tail()->next = l.head();

	EXPECT_TRUE(is_looped_2(l));

	l.tail()->next = nullptr;
}

TEST(TestAlgorithmsLib, correct_find_loop) {
	List<int> list;

	for (int i = 0; i < 5; i++) {
		list.push_back(i);
	}

	EXPECT_EQ(nullptr, find_loop(list));
}

TEST(TestAlgorithmsLib, correct_find_loop_2) {
	List<int> list;

	for (int i = 0; i < 5; i++) {
		list.push_back(i);
	}

	list.tail()->next = list.head()->next->next;

	EXPECT_EQ(list.head()->next->next, find_loop(list));

	list.tail()->next = nullptr;
}

TEST(TestAlgorithmsLib, correct_find_loop_3) {
	List<int> list;

	for (int i = 0; i < 5; i++) {
		list.push_back(i);
	}

	list.tail()->next = list.head();

	EXPECT_EQ(list.head(), find_loop(list));

	list.tail()->next = nullptr;
}
