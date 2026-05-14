#include <gtest/gtest.h>
#include "../lib_unsort_vec_container/unsort_vec_container.h"
//#include "../lib_table/table.h"

TEST(TestUnsTableVecLib, correct_create) {
	Table<UnsortVecContainer, int, int> t;

	EXPECT_TRUE(t.rows().is_empty());
}

TEST(TestUnsTableVecLib, correct_insert_found_and_erase) {
	Table<UnsortVecContainer, int, int> t;
	t.insert(3, 3);
	t.insert(1, 1);
	t.insert(2, 2);
	EXPECT_THROW(t.insert(3, 111), std::logic_error);

	std::cout << t;

	EXPECT_EQ(*(t.found(1)), 1);
	EXPECT_EQ(*(t.found(3)), 3);

	t.erase(1);
	t.erase(3);

	EXPECT_EQ(t.found(1), nullptr);
	EXPECT_EQ(t.found(3), nullptr);
	t.erase(2);
	EXPECT_TRUE(t.rows().is_empty());

	EXPECT_THROW(t.erase(3), std::logic_error);
	EXPECT_THROW(t.erase(5), std::logic_error);
}

TEST(TestUnsTableVecLib, correct_erase) {
	Table<UnsortVecContainer, int, int> t;
	Table<UnsortVecContainer, int, int> expected;

	for (int i = 0; i < 5; i++) {
		t.insert(i + 1, i + 1);
	}
	expected.insert(2, 2);
	expected.insert(4, 4);

	t.erase(1);
	t.erase(3);
	t.erase(5);

	std::cout << t;

	t.erase(2);
	t.erase(4);

	EXPECT_TRUE(t.rows().is_empty());
}