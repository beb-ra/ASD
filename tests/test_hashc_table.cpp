#include <gtest/gtest.h>
#include "../lib_hashc_table/hashc_table.h"

TEST(TestHashTableCLib, correct_create) {
	HashTableC<int> t;

	EXPECT_TRUE(t.is_empty());
}

TEST(TestHashTableCLib, correct_insert_found_and_erase) {
	HashTableC<int> t;
	t.insert("3", 4);
	t.insert("1", 2);
	t.insert("11", 11);
	EXPECT_THROW(t.insert("3", 111), std::logic_error);

	std::cout << t;

	EXPECT_EQ(*(t.found("1")), 2);
	EXPECT_EQ(*(t.found("3")), 4);

	t.erase("1");
	t.erase("3");

	EXPECT_EQ(t.found("1"), nullptr);
	EXPECT_EQ(t.found("3"), nullptr);

	EXPECT_FALSE(t.is_empty());
	t.erase("11");
	EXPECT_TRUE(t.is_empty());

	EXPECT_THROW(t.erase("3"), std::logic_error);
	EXPECT_THROW(t.erase("5"), std::logic_error);
}

TEST(TestHashTableCLib, correct_resize) {
	HashTableC<int> t(3);

	t.insert("1", 1);
	t.insert("2", 2);
	t.insert("3", 3);
	t.insert("4", 4);

	EXPECT_EQ(t.rows().size(), 6);

	EXPECT_EQ(*t.found("2"), 2);
	EXPECT_EQ(*t.found("3"), 3);

	t.erase("3");
	t.erase("2");

	EXPECT_EQ(t.found("3"), nullptr);
	EXPECT_EQ(t.found("2"), nullptr);
	EXPECT_EQ(*t.found("1"), 1);
	EXPECT_EQ(*t.found("4"), 4);

	t.erase("1");
	t.erase("4");

	EXPECT_EQ(t.found("1"), nullptr);
	EXPECT_EQ(t.found("4"), nullptr);

	EXPECT_TRUE(t.is_empty());
}