#include <gtest/gtest.h>
#include "../lib_list/list.h"

TEST(TestListNodeLib, try_create) {
	ASSERT_NO_THROW(List<int>::Node n(5));
}

TEST(TestListNodeLib, correct_create) {
	List<int>::Node n(5);

	EXPECT_EQ(5, n.value);
	EXPECT_EQ(nullptr, n.next);
}

TEST(TestListNodeLib, correct_create_2) {
	List<int>::Node n(5);
	List<int>::Node n2(111, &n);

	EXPECT_EQ(111, n2.value);
	EXPECT_EQ(&n, n2.next);
}

TEST(TestListLib, try_create) {
	ASSERT_NO_THROW(List<int> l);
}

TEST(TestListLib, correct_create) {
	List<int> l;

	EXPECT_TRUE(l.is_empty());
	EXPECT_EQ(0, l.size());
	EXPECT_EQ(nullptr, l.head());
	EXPECT_EQ(nullptr, l.tail());
}

TEST(TestListLib, correct_push_front) {
	List<int> l;
	l.push_front(111);

	EXPECT_FALSE(l.is_empty());
	EXPECT_EQ(1, l.size());
	EXPECT_EQ(111, l.head()->value);
	EXPECT_EQ(111, l.tail()->value);
}

TEST(TestListLib, correct_push_front_2) {
	List<int> l;
	l.push_front(22);
	l.push_front(11);
	l.push_front(7);

	EXPECT_EQ(3, l.size());
	EXPECT_EQ(7, l.head()->value);
	EXPECT_EQ(22, l.tail()->value);
}

TEST(TestListLib, correct_push_back) {
	List<int> l;
	l.push_back(111);

	EXPECT_FALSE(l.is_empty());
	EXPECT_EQ(1, l.size());
	EXPECT_EQ(111, l.head()->value);
	EXPECT_EQ(111, l.tail()->value);
}

TEST(TestListLib, correct_push_back_2) {
	List<int> l;
	l.push_back(111);
	l.push_back(222);
	l.push_back(333);

	EXPECT_EQ(3, l.size());
	EXPECT_EQ(111, l.head()->value);
	EXPECT_EQ(333, l.tail()->value);
}

TEST(TestListLib, correct_push_front_and_back) {
	List<int> l;
	l.push_back(111);
	l.push_front(1);
	l.push_back(222);
	l.push_front(2);
	l.push_back(333);
	l.push_front(3);   // 3 2 1 111 222 333

	EXPECT_EQ(6, l.size());
	EXPECT_EQ(3, l.head()->value);
	EXPECT_EQ(2, l.head()->next->value);
	EXPECT_EQ(1, l.head()->next->next->value);
	EXPECT_EQ(111, l.head()->next->next->next->value);
	EXPECT_EQ(222, l.head()->next->next->next->next->value);
	EXPECT_EQ(333, l.tail()->value);
}

TEST(TestListLib, try_create_with_copy) {
	List<int> l;

	ASSERT_NO_THROW(List<int> l2(l));
}

TEST(TestListLib, corect_create_with_copy) {
	List<int> l;
	l.push_back(11);
	l.push_back(22);
	l.push_back(33);
	List<int> l2(l);

	List<int>::Node* node1 = l.head();
	List<int>::Node* node2 = l2.head();
	for (size_t i = 0; i < l.size(); i++) {
		EXPECT_EQ(node1->value, node2->value);
		node1 = node1->next;
		node2 = node2->next;
	}

	EXPECT_EQ(l.size(), l2.size());
	EXPECT_EQ(3, l2.size());
	EXPECT_EQ(11, l2.head()->value);
	EXPECT_EQ(33, l2.tail()->value);
}

TEST(TestListLib, correct_insert) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.insert(2, 111);

	EXPECT_EQ(5, l.size());
	EXPECT_EQ(111, l.head()->next->next->value);
}

TEST(TestListLib, correct_insert_at_begin) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.insert(static_cast <size_t>(0), 111);

	EXPECT_EQ(5, l.size());
	EXPECT_EQ(111, l.head()->value);
}

TEST(TestListLib, correct_insert_at_begin_2) {
	List<int> l;
	l.insert(static_cast <size_t>(0), 111);

	EXPECT_EQ(1, l.size());
	EXPECT_EQ(111, l.head()->value);
}

TEST(TestListLib, correct_insert_at_end) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.insert(static_cast <size_t>(4), 111);

	EXPECT_EQ(5, l.size());
	EXPECT_EQ(111, l.tail()->value);
}

TEST(TestListLib, throw_uncorrect_insert) {
	List<int> l;

	EXPECT_TRUE(l.is_empty());
	EXPECT_THROW(l.insert(5, 111), std::invalid_argument);
}

TEST(TestListLib, correct_insert_by_pointer) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	List<int>::Node* node1 = l.head();
	l.insert(node1, 111);    // 1 111 2 3

	EXPECT_EQ(l.size(), 4);
	EXPECT_EQ(l.head()->value, 1);
	EXPECT_EQ(l.head()->next->value, 111);
	EXPECT_EQ(l.head()->next->next->value, 2);
	EXPECT_EQ(l.tail()->value, 3);
}

TEST(TestListLib, correct_insert_at_end_by_pointer) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	List<int>::Node* node1 = l.tail();
	l.insert(node1, 111);    // 1 2 3 111

	EXPECT_EQ(l.size(), 4);
	EXPECT_EQ(l.head()->value, 1);
	EXPECT_EQ(l.head()->next->value, 2);
	EXPECT_EQ(l.head()->next->next->value, 3);
	EXPECT_EQ(l.tail()->value, 111);
}

TEST(TestListLib, correct_pop_front) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.pop_front();
	l.pop_front();

	EXPECT_EQ(2, l.size());
	EXPECT_EQ(3, l.head()->value);
	EXPECT_EQ(4, l.tail()->value);
}

TEST(TestListLib, correct_pop_front_2) {
	List<int> l;
	l.push_back(1);
	l.pop_front();

	EXPECT_EQ(0, l.size());
	EXPECT_EQ(nullptr, l.head());
	EXPECT_EQ(nullptr, l.tail());
	EXPECT_TRUE(l.is_empty());
}

TEST(TestListLib, correct_pop_back) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.pop_back();
	l.pop_back();

	EXPECT_EQ(2, l.size());
	EXPECT_EQ(1, l.head()->value);
	EXPECT_EQ(2, l.tail()->value);
}

TEST(TestListLib, correct_pop_back_2) {
	List<int> l;
	l.push_back(1);
	l.pop_back();

	EXPECT_EQ(0, l.size());
	EXPECT_TRUE(l.is_empty());
	EXPECT_EQ(nullptr, l.head());
	EXPECT_EQ(nullptr, l.tail());
}

TEST(TestListLib, throw_uncorrect_pop_front) {
	List<int> l;

	EXPECT_TRUE(l.is_empty());
	EXPECT_THROW(l.pop_front(), std::invalid_argument);
}

TEST(TestListLib, throw_uncorrect_pop_back) {
	List<int> l;

	EXPECT_TRUE(l.is_empty());
	EXPECT_THROW(l.pop_back(), std::invalid_argument);
}

TEST(TestListLib, correct_erase_by_pointer) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);

	List<int>::Node* node1 = l.head()->next;
	l.erase(node1);    // 1 2  4

	EXPECT_EQ(3, l.size());
	EXPECT_EQ(1, l.head()->value);
	EXPECT_EQ(2, l.head()->next->value);
	EXPECT_EQ(4, l.head()->next->next->value);
	EXPECT_EQ(4, l.tail()->value);
}

TEST(TestListLib, correct_erase_by_pointer_2) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	List<int>::Node* node1 = l.head()->next;
	l.erase(node1);    // 1 2 

	EXPECT_EQ(2, l.size());
	EXPECT_EQ(1, l.head()->value);
	EXPECT_EQ(2, l.head()->next->value);
	EXPECT_EQ(2, l.tail()->value);
}

TEST(TestListLib, correct_erase_by_pointer_3) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	List<int>::Node* node1 = l.head();
	l.erase(node1);    // 1  3

	EXPECT_EQ(2, l.size());
	EXPECT_EQ(1, l.head()->value);
	EXPECT_EQ(3, l.head()->next->value);
	EXPECT_EQ(3, l.tail()->value);
}

TEST(TestListLib, throw_uncorrect_erase_by_pointer) {
	List<int> l;

	EXPECT_TRUE(l.is_empty());
	EXPECT_THROW(l.erase(l.head()), std::invalid_argument);
}

TEST(TestListLib, throw_uncorrect_erase_by_pointer_2) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);

	EXPECT_THROW(l.erase(nullptr), std::invalid_argument);
	EXPECT_THROW(l.erase(l.tail()), std::logic_error);
}

TEST(TestListLib, throw_uncorrect_erase_by_pointer_3) {
	List<int> l;
	l.push_back(1);

	EXPECT_THROW(l.erase(l.head()), std::logic_error);
}

TEST(TestListLib, correct_erase) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);

	l.erase(2);    // 1 2  4

	EXPECT_EQ(3, l.size());
	EXPECT_EQ(1, l.head()->value);
	EXPECT_EQ(2, l.head()->next->value);
	EXPECT_EQ(4, l.head()->next->next->value);
	EXPECT_EQ(4, l.tail()->value);
}

TEST(TestListLib, correct_erase_2) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	l.erase(2);    // 1 2 

	EXPECT_EQ(2, l.size());
	EXPECT_EQ(1, l.head()->value);
	EXPECT_EQ(2, l.head()->next->value);
	EXPECT_EQ(2, l.tail()->value);
}

TEST(TestListLib, correct_erase_3) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	l.erase(1);    // 1  3

	EXPECT_EQ(2, l.size());
	EXPECT_EQ(1, l.head()->value);
	EXPECT_EQ(3, l.head()->next->value);
	EXPECT_EQ(3, l.tail()->value);
}

TEST(TestListLib, correct_erase_4) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	l.erase(static_cast <size_t>(0));    //  2 3

	EXPECT_EQ(2, l.size());
	EXPECT_EQ(2, l.head()->value);
	EXPECT_EQ(3, l.head()->next->value);
	EXPECT_EQ(3, l.tail()->value);
}

TEST(TestListLib, throw_uncorrect_erase) {
	List<int> l;

	EXPECT_THROW(l.erase(static_cast <size_t>(0)), std::invalid_argument);
}

TEST(TestListLib, throw_uncorrect_erase_2) {
	List<int> l;
	l.push_back(1);

	EXPECT_THROW(l.erase(5), std::invalid_argument);
}

TEST(TestListLib, correct_insert_and_erase) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.insert(1, 111);
	l.erase(static_cast <size_t>(0));
	l.push_front(222);
	l.insert(2, 333);
	l.insert(4, 444);
	l.erase(1);
	l.erase(l.head()->next->next);   // 222 333 2

	EXPECT_EQ(3, l.size());
	EXPECT_EQ(222, l.head()->value);
	EXPECT_EQ(333, l.head()->next->value);
	EXPECT_EQ(2, l.tail()->value);
}

TEST(TestListLib, correct_assignment_operator) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);
	List<int> l2 = l;

	EXPECT_EQ(l, l2);
	l2.push_back(222);
	EXPECT_NE(l, l2);
}

TEST(TestListIteratorLib, try_create_iterator) {
	List<int> l;
	l.push_back(11);
	l.push_back(22);

	ASSERT_NO_THROW(List<int>::Iterator it);
}

TEST(TestListIteratorLib, correct_create_iterator) {
	List<int> l;
	List<int>::Iterator it;

	EXPECT_EQ(it.current(), nullptr);
}

TEST(TestListIteratorLib, correct_operator_star) {
	List<int> l;
	for (int i = 0; i < 3; i++) {
		l.push_back(i + 1);
	}
	List<int>::Iterator it = l.begin();

	EXPECT_EQ(*it, 1);
	*it = 100;
	EXPECT_EQ(*it, 100);
	EXPECT_EQ(l.head()->value, 100);
}

TEST(TestListIteratorLib, throw_uncorrect_operator_star) {
	List<int> l;
	for (int i = 0; i < 3; i++) {
		l.push_back(i + 1);
	}
	List<int>::Iterator it = l.end();

	EXPECT_THROW(*it, std::logic_error);
}

TEST(TestListIteratorLib, throw_uncorrect_increment) {
	List<int> l;
	for (int i = 0; i < 3; i++) {
		l.push_back(i + 1);
	}
	List<int>::Iterator it = l.end();

	EXPECT_THROW(it++, std::logic_error);
	EXPECT_THROW(++it, std::logic_error);
}

TEST(TestListIteratorLib, correct_iteration) {
	List<int> l;
	for (int i = 0; i < 4; i++) {
		l.push_back(i + 1);
	}
	List<int>::Iterator it;

	int i = 1;
	for (it = l.begin(); it != l.end(); it++) {
		EXPECT_EQ(i++, *it);
	}
}

TEST(TestListIteratorLib, correct_iteration_2) {
	List<int> l;

	for (int i = 0; i < 4; i++) {
		l.push_back(i + 1);
	}

	int i = 1;
	List<int>::Iterator it;
	for (it = l.begin(); it != l.end(); it++, i++) {
		*it = i + 100;
	}

	it = l.begin();
	EXPECT_EQ(101, *it);
	EXPECT_EQ(102, *(++it));
	EXPECT_EQ(103, *(++it));
	EXPECT_EQ(104, *(++it));
}

TEST(TestListIteratorLib, correct_begin_and_end) {
	List<int> l;

	EXPECT_EQ(l.begin(), l.end());
}

TEST(TestListIteratorLib, correct_assignment) {
	List<int> l;
	for (int i = 0; i < 3; i++) {
		l.push_back(i + 1);
	}
	List<int>::Iterator it1 = l.begin();
	List<int>::Iterator it2 = ++l.begin();

	it2 = it1;
	EXPECT_EQ(it1, it2);
	EXPECT_EQ(*it1, *it2);
}

TEST(TestListIteratorLib, correct_equality) {
	List<int> l;
	l.push_back(1);
	l.push_back(2);

	List<int>::Iterator it1 = l.begin();
	List<int>::Iterator it2 = l.begin();
	List<int>::Iterator it3 = ++l.begin();

	EXPECT_TRUE(it1 == it2);
	EXPECT_FALSE(it1 == it3);
	EXPECT_TRUE(it1 != it3);
}
