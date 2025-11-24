#include <gtest/gtest.h>
#include "../lib_dlist/dlist.h"

TEST(TestDListNodeLib, try_create) {
	ASSERT_NO_THROW(DList<int>::DNode n(5));
}

TEST(TestDListNodeLib, correct_create) {
	DList<int>::DNode n(5);

	EXPECT_EQ(5, n.value);
	EXPECT_EQ(nullptr, n.next);
	EXPECT_EQ(nullptr, n.prev);
}

TEST(TestDListNodeLib, correct_create_2) {
	DList<int>::DNode n1(5);
	DList<int>::DNode n2(22, nullptr, &n1);
	n1.next = &n2;
	DList<int>::DNode n3(111, nullptr, &n2);

	EXPECT_EQ(22, n2.value);
	EXPECT_EQ(&n2, n1.next);
	EXPECT_EQ(&n1, n2.prev);
}

TEST(TestDListLib, try_create) {
	ASSERT_NO_THROW(DList<int> l);
}

TEST(TestDListLib, correct_create) {
	DList<int> l;

	EXPECT_TRUE(l.is_empty());
	EXPECT_EQ(0, l.size());
	EXPECT_EQ(nullptr, l.dhead());
	EXPECT_EQ(nullptr, l.dtail());
}

TEST(TestDListLib, correct_push_front) {
	DList<int> l;
	l.push_front(111);

	EXPECT_FALSE(l.is_empty());
	EXPECT_EQ(1, l.size());
	EXPECT_EQ(111, l.dhead()->value);
	EXPECT_EQ(111, l.dtail()->value);
}

TEST(TestDListLib, correct_push_front_2) {
	DList<int> l;
	l.push_front(22);
	l.push_front(11);
	l.push_front(7);

	EXPECT_EQ(3, l.size());
	EXPECT_EQ(7, l.dhead()->value);
	EXPECT_EQ(22, l.dtail()->value);
}

TEST(TestDListLib, correct_push_back) {
	DList<int> l;
	l.push_back(111);

	EXPECT_FALSE(l.is_empty());
	EXPECT_EQ(1, l.size());
	EXPECT_EQ(111, l.dhead()->value);
	EXPECT_EQ(111, l.dtail()->value);
}

TEST(TestDListLib, correct_push_back_2) {
	DList<int> l;
	l.push_back(111);
	l.push_back(222);
	l.push_back(333);

	EXPECT_EQ(3, l.size());
	EXPECT_EQ(111, l.dhead()->value);
	EXPECT_EQ(333, l.dtail()->value);
}

TEST(TestDListLib, correct_push_front_and_back) {
	DList<int> l;
	l.push_back(111);
	l.push_front(1);
	l.push_back(222);
	l.push_front(2);
	l.push_back(333);
	l.push_front(3);   // 3 2 1 111 222 333

	EXPECT_EQ(6, l.size());
	EXPECT_EQ(3, l.dhead()->value);
	EXPECT_EQ(2, l.dhead()->next->value);
	EXPECT_EQ(1, l.dhead()->next->next->value);
	EXPECT_EQ(111, l.dtail()->prev->prev->value);
	EXPECT_EQ(222, l.dtail()->prev->value);
	EXPECT_EQ(333, l.dtail()->value);
}

TEST(TestDListLib, try_create_with_copy) {
	DList<int> l;

	ASSERT_NO_THROW(DList<int> l2(l));
}

TEST(TestDListLib, corect_create_with_copy) {   // переписать с помощью итераторов а то кринж
	DList<int> l;
	l.push_back(11);
	l.push_back(22);
	l.push_back(33);
	DList<int> l2(l);

	DList<int>::DNode* node1 = l.dhead();
	DList<int>::DNode* node2 = l2.dhead();
	for (size_t i = 0; i < l.size(); i++) {
		EXPECT_EQ(node1->value, node2->value);
		node1 = static_cast<DList<int>::DNode*>(node1->next);
		node2 = static_cast<DList<int>::DNode*>(node2->next);
	}

	EXPECT_EQ(l.size(), l2.size());
	EXPECT_EQ(3, l2.size());
	EXPECT_EQ(11, l2.dhead()->value);
	EXPECT_EQ(33, l2.dtail()->value);
}

TEST(TestDListLib, correct_create_with_initialize) {
	DList<int> l = { 1, 2, 3, 4, 5 };
	DList<int> l2;
	for (int i = 0; i < 5; i++) {
		l2.push_back(i + 1);
	}

	EXPECT_EQ(5, l.size());
	EXPECT_EQ(l, l2);
}

TEST(TestDListLib, correct_insert) {
	DList<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.insert(2, 111);   // 1 2 111 3 4

	EXPECT_EQ(5, l.size());
	EXPECT_EQ(111, l.dhead()->next->next->value);
	EXPECT_EQ(111, l.dtail()->prev->prev->value);
}

TEST(TestDListLib, correct_insert_at_begin) {
	DList<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.insert(static_cast <size_t>(0), 111);

	EXPECT_EQ(5, l.size());
	EXPECT_EQ(111, l.dhead()->value);
}

TEST(TestDListLib, correct_insert_at_begin_2) {
	DList<int> l;
	l.insert(static_cast <size_t>(0), 111);

	EXPECT_EQ(1, l.size());
	EXPECT_EQ(111, l.dhead()->value);
}

TEST(TestDListLib, correct_insert_at_end) {
	DList<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.insert(static_cast <size_t>(4), 111);

	EXPECT_EQ(5, l.size());
	EXPECT_EQ(111, l.dtail()->value);
}

TEST(TestDListLib, throw_uncorrect_insert) {
	DList<int> l;

	EXPECT_TRUE(l.is_empty());
	EXPECT_THROW(l.insert(5, 111), std::invalid_argument);
}

TEST(TestDListLib, correct_insert_by_pointer) {
	DList<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	DList<int>::DNode* node1 = l.dhead();
	l.insert(node1, 111);    // 1 111 2 3

	EXPECT_EQ(l.size(), 4);
	EXPECT_EQ(l.dhead()->value, 1);
	EXPECT_EQ(l.dhead()->next->value, 111);
	EXPECT_EQ(l.dtail()->prev->value, 2);
	EXPECT_EQ(l.dtail()->value, 3);
}

TEST(TestDListLib, correct_insert_at_end_by_pointer) {
	DList<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	DList<int>::DNode* node1 = l.dtail();
	l.insert(node1, 111);    // 1 2 3 111

	EXPECT_EQ(l.size(), 4);
	EXPECT_EQ(l.dhead()->value, 1);
	EXPECT_EQ(l.dhead()->next->value, 2);
	EXPECT_EQ(l.dtail()->prev->value, 3);
	EXPECT_EQ(l.dtail()->value, 111);
}

TEST(TestDListLib, correct_pop_front) {
	DList<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.pop_front();
	l.pop_front();

	EXPECT_EQ(2, l.size());
	EXPECT_EQ(3, l.dhead()->value);
	EXPECT_EQ(4, l.dtail()->value);
}

TEST(TestDListLib, correct_pop_front_2) {
	DList<int> l;
	l.push_back(1);
	l.pop_front();

	EXPECT_EQ(0, l.size());
	EXPECT_EQ(nullptr, l.dhead());
	EXPECT_EQ(nullptr, l.dtail());
	EXPECT_TRUE(l.is_empty());
}

TEST(TestDListLib, correct_pop_back) {
	DList<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.pop_back();
	l.pop_back();

	EXPECT_EQ(2, l.size());
	EXPECT_EQ(1, l.dhead()->value);
	EXPECT_EQ(2, l.dtail()->value);
}

TEST(TestDListLib, correct_pop_back_2) {
	DList<int> l;
	l.push_back(1);
	l.pop_back();

	EXPECT_EQ(0, l.size());
	EXPECT_TRUE(l.is_empty());
	EXPECT_EQ(nullptr, l.dhead());
	EXPECT_EQ(nullptr, l.dtail());
}

TEST(TestDListLib, throw_uncorrect_pop_front) {
	DList<int> l;

	EXPECT_TRUE(l.is_empty());
	EXPECT_THROW(l.pop_front(), std::invalid_argument);
}

TEST(TestDListLib, throw_uncorrect_pop_back) {
	DList<int> l;

	EXPECT_TRUE(l.is_empty());
	EXPECT_THROW(l.pop_back(), std::invalid_argument);
}

TEST(TestDListLib, correct_erase_by_pointer) {
	DList<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);

	DList<int>::DNode* node1 = l.dhead()->next;
	l.erase(node1);    // 1  3 4

	EXPECT_EQ(3, l.size());
	EXPECT_EQ(1, l.dhead()->value);
	EXPECT_EQ(3, l.dhead()->next->value);
	EXPECT_EQ(4, l.dhead()->next->next->value);
	EXPECT_EQ(4, l.dtail()->value);
}

TEST(TestDListLib, correct_erase_by_pointer_2) {
	DList<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	DList<int>::DNode* node1 = l.dhead()->next->next;
	l.erase(node1);    // 1 2 

	EXPECT_EQ(2, l.size());
	EXPECT_EQ(1, l.dhead()->value);
	EXPECT_EQ(2, l.dhead()->next->value);
	EXPECT_EQ(2, l.dtail()->value);
}

TEST(TestDListLib, correct_erase_by_pointer_3) {
	DList<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	DList<int>::DNode* node1 = l.dhead();
	l.erase(node1);    //  2 3

	EXPECT_EQ(2, l.size());
	EXPECT_EQ(2, l.dhead()->value);
	EXPECT_EQ(3, l.dhead()->next->value);
	EXPECT_EQ(3, l.dtail()->value);
}

TEST(TestDListLib, throw_uncorrect_erase_by_pointer) {
	DList<int> l;

	EXPECT_TRUE(l.is_empty());
	EXPECT_THROW(l.erase(l.dhead()), std::invalid_argument);
}

TEST(TestDListLib, throw_uncorrect_erase_by_pointer_2) {
	DList<int> l;
	l.push_back(1);
	l.push_back(2);

	EXPECT_THROW(l.erase(nullptr), std::invalid_argument);
	EXPECT_THROW(l.erase(l.dtail()->next), std::logic_error);
}

TEST(TestDListLib, throw_uncorrect_erase_by_pointer_3) {
	DList<int> l;
	l.push_back(1);

	EXPECT_THROW(l.erase(l.dhead()->next), std::logic_error);
}

TEST(TestDListLib, correct_erase) {
	DList<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);

	l.erase(2);    // 1 2  4

	EXPECT_EQ(3, l.size());
	EXPECT_EQ(1, l.dhead()->value);
	EXPECT_EQ(2, l.dhead()->next->value);
	EXPECT_EQ(2, l.dtail()->prev->value);
	EXPECT_EQ(4, l.dtail()->value);
}

TEST(TestDListLib, correct_erase_2) {
	DList<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	l.erase(2);    // 1 2 

	EXPECT_EQ(2, l.size());
	EXPECT_EQ(1, l.dhead()->value);
	EXPECT_EQ(2, l.dhead()->next->value);
	EXPECT_EQ(2, l.dtail()->value);
}

TEST(TestDListLib, correct_erase_3) {
	DList<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	l.erase(1);    // 1  3

	EXPECT_EQ(2, l.size());
	EXPECT_EQ(1, l.dhead()->value);
	EXPECT_EQ(3, l.dhead()->next->value);
	EXPECT_EQ(3, l.dtail()->value);
}

TEST(TestDListLib, correct_erase_4) {
	DList<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	l.erase(static_cast <size_t>(0));    //  2 3

	EXPECT_EQ(2, l.size());
	EXPECT_EQ(2, l.dhead()->value);
	EXPECT_EQ(3, l.dhead()->next->value);
	EXPECT_EQ(3, l.dtail()->value);
}

TEST(TestDListLib, throw_uncorrect_erase) {
	DList<int> l;

	EXPECT_THROW(l.erase(static_cast <size_t>(0)), std::invalid_argument);
}

TEST(TestDListLib, throw_uncorrect_erase_2) {
	DList<int> l;
	l.push_back(1);

	EXPECT_THROW(l.erase(5), std::invalid_argument);
}

TEST(TestDListLib, correct_insert_and_erase) {
	DList<int> l;
	l.push_back(1);
	l.push_back(2);
	l.insert(1, 111);
	l.erase(static_cast <size_t>(0));
	l.push_front(222);
	l.insert(2, 333);
	l.insert(4, 444);
	l.erase(1);
	l.erase(l.dhead()->next->next); // 222 333 444

	EXPECT_EQ(3, l.size());
	EXPECT_EQ(222, l.dhead()->value);
	EXPECT_EQ(333, l.dhead()->next->value);
	EXPECT_EQ(444, l.dtail()->value);
}

TEST(TestDListLib, correct_assignment_operator) {
	DList<int> l;
	l.push_back(1);
	l.push_back(2);
	DList<int> l2 = l;

	EXPECT_EQ(l, l2);
	l2.push_back(222);
	EXPECT_NE(l, l2);
}

TEST(TestDListIteratorLib, try_create_iterator) {
	DList<int> l;
	l.push_back(11);
	l.push_back(22);

	ASSERT_NO_THROW(DList<int>::Iterator it);
}

TEST(TestDListIteratorLib, correct_create_iterator) {
	DList<int> l;
	DList<int>::Iterator it;

	EXPECT_EQ(it.current(), nullptr);
}

TEST(TestDListIteratorLib, correct_operator_star) {
	DList<int> l;
	for (int i = 0; i < 3; i++) {
		l.push_back(i + 1);
	}
	DList<int>::Iterator it = l.begin();

	EXPECT_EQ(*it, 1);
	*it = 100;
	EXPECT_EQ(*it, 100);
	EXPECT_EQ(l.dhead()->value, 100);
}

TEST(TestDListIteratorLib, throw_uncorrect_operator_star) {
	DList<int> l;
	for (int i = 0; i < 3; i++) {
		l.push_back(i + 1);
	}
	DList<int>::Iterator it = l.end();

	EXPECT_THROW(*it, std::logic_error);
}

TEST(TestDListIteratorLib, throw_uncorrect_increment) {
	DList<int> l;
	for (int i = 0; i < 3; i++) {
		l.push_back(i + 1);
	}
	DList<int>::Iterator it = l.end();

	EXPECT_THROW(it++, std::logic_error);
	EXPECT_THROW(++it, std::logic_error);
}

TEST(TestDListIteratorLib, throw_uncorrect_decrement) {
	DList<int> l;
	for (int i = 0; i < 3; i++) {
		l.push_back(i + 1);
	}
	DList<int>::Iterator it = l.rend();

	EXPECT_THROW(it--, std::logic_error);
	EXPECT_THROW(--it, std::logic_error);
}

TEST(TestDListIteratorLib, correct_iteration) {
	DList<int> l;
	for (int i = 0; i < 4; i++) {
		l.push_back(i + 1);
	}
	DList<int>::Iterator it;

	int i = 1;
	for (it = l.begin(); it != l.end(); it++) {
		EXPECT_EQ(i++, *it);
	}
}

TEST(TestDListIteratorLib, correct_iteration_2) {
	DList<int> l;

	for (int i = 0; i < 4; i++) {
		l.push_back(i+1);
	}

	int i = 1;
	DList<int>::Iterator it;
	for (it = l.begin(); it != l.end(); it++, i++) {
		*it = i + 100;
	}

	it = l.begin();
	EXPECT_EQ(101, *it);
	EXPECT_EQ(102, *(++it));
	EXPECT_EQ(103, *(++it));
	EXPECT_EQ(104, *(++it));
}

TEST(TestDListIteratorLib, correct_reverse_iteration) {
	DList<int> l;
	for (int i = 0; i < 4; i++) {
		l.push_back(i + 1);
	}
	DList<int>::Iterator it;

	int i = 4;
	for (it = l.rbegin(); it != l.rend(); it++) {
		EXPECT_EQ(i--, *it);
	}
}

TEST(TestDListIteratorLib, correct_reverse_iteration_2) {
	DList<int> l;

	for (int i = 0; i < 4; i++) {
		l.push_back(i + 1);
	}

	int i = 4;
	DList<int>::Iterator it;
	for (it = l.rbegin(); it != l.rend(); it--, i--) {
		*it = i + 100;
	}

	it = l.begin();
	EXPECT_EQ(101, *it);
	EXPECT_EQ(102, *(++it));
	EXPECT_EQ(103, *(++it));
	EXPECT_EQ(104, *(++it));
}

TEST(TestDListIteratorLib, correct_begin_and_end) {
	DList<int> l;

	EXPECT_EQ(l.begin(), l.end());
}

TEST(TestDListIteratorLib, correct_assignment) {
	DList<int> l;
	for (int i = 0; i < 3; i++) {
		l.push_back(i + 1);
	}
	DList<int>::Iterator it1 = l.begin();
	DList<int>::Iterator it2 = ++l.begin();

	it2 = it1;
	EXPECT_EQ(it1, it2);
	EXPECT_EQ(*it1, *it2);
}

TEST(TestDListIteratorLib, correct_equality) {
	DList<int> l;
	l.push_back(1);
	l.push_back(2);

	DList<int>::Iterator it1 = l.begin();
	DList<int>::Iterator it2 = l.begin();
	DList<int>::Iterator it3 = ++l.begin();

	EXPECT_TRUE(it1 == it2);
	EXPECT_FALSE(it1 == it3);
	EXPECT_TRUE(it1 != it3);
}