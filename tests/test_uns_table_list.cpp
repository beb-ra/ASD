#include <gtest/gtest.h>
#include "../lib_table/table.h"
#include "../lib_list_container/list_container.h"

TEST(TestUnsTableListLib, correct_create) {
	Table<ListContainer, int, int> t;

	EXPECT_TRUE(t.rows().is_empty());
}

TEST(TestUnsTableListLib, correct_insert_found_and_erase) {
	Table<ListContainer, int, int> t;
	t.insert(3, 3);
	t.insert(1, 1);
	EXPECT_THROW(t.insert(3, 111), std::logic_error);

	std::cout << t;

	EXPECT_EQ(*(t.found(1)), 1);
	EXPECT_EQ(*(t.found(3)), 3);

	t.erase(1);
	t.erase(3);

	EXPECT_EQ(t.found(1), nullptr);
	EXPECT_EQ(t.found(3), nullptr);
	EXPECT_TRUE(t.rows().is_empty());

	EXPECT_THROW(t.erase(3), std::logic_error);
	EXPECT_THROW(t.erase(5), std::logic_error);
}

TEST(TestUnsTableListLib, correct_erase) {
	Table<ListContainer, int, int> t;
	
	for (int i = 0; i < 5; i++) {
		t.insert(i + 1, i + 1);
	}
	t.erase(1);
	t.erase(3);
	t.erase(5);

	std::cout << t;

	t.erase(2);
	t.erase(4);

	EXPECT_TRUE(t.rows().is_empty());
}