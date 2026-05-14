#include <gtest/gtest.h>
#include "../lib_hashc_table_container/hashc_table_container.h"
#include "../lib_table/table.h"

TEST(TestHashTableCLib, correct_create) {
	Table<HashTableContainerC, std::string, int> t;

	EXPECT_TRUE(t.is_empty());
}

TEST(TestHashTableCLib, correct_insert_found_and_erase) {
	Table<HashTableContainerC, std::string, int> t;
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

TEST(TestHashTableCLib, correct_erase) {
	Table<HashTableContainerC, std::string, int> t;

	t.insert("100", 100);
	t.insert("200", 200);
	t.insert("300", 300);
	t.insert("400", 400);
	t.insert("500", 500);

	EXPECT_EQ(*t.found("100"), 100);
	EXPECT_EQ(*t.found("300"), 300);
	EXPECT_EQ(*t.found("500"), 500);

	std::cout << t;

	t.erase("100");
	t.erase("300");
	t.erase("500");

	EXPECT_EQ(t.found("100"), nullptr);
	EXPECT_EQ(t.found("300"), nullptr);
	EXPECT_EQ(t.found("500"), nullptr);
	EXPECT_EQ(*t.found("200"), 200);
	EXPECT_EQ(*t.found("400"), 400);

	std::cout << t;

	t.erase("200");
	t.erase("400");

	EXPECT_EQ(t.found("200"), nullptr);
	EXPECT_EQ(t.found("400"), nullptr);

	EXPECT_TRUE(t.is_empty());
}
