#include <gtest/gtest.h>
#include "../lib_node/node.h"

TEST(TestNodeLib, try_create) {
	ASSERT_NO_THROW(Node<int> n(5));
}

TEST(TestNodeLib, correct_create) {
	Node<int> n(5);

	EXPECT_EQ(5, n.value());
	EXPECT_EQ(nullptr, n.next());
}

TEST(TestNodeLib, correct_create_2) {
	Node<int> n(5);
	Node<int> n2(111, &n);

	EXPECT_EQ(111, n2.value());
	EXPECT_EQ(&n, n2.next());
}

TEST(TestNodeLib, correct_setters) {
	Node<int> n(5);
	Node<int> n2(111, &n);
	Node<int> n3(77, &n);

	n2.set_value(22);
	n2.set_next(&n3);

	EXPECT_EQ(22, n2.value());
	EXPECT_EQ(&n3, n2.next());
	EXPECT_EQ(&n, n2.next()->next());
}