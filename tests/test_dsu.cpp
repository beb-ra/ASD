#include <gtest/gtest.h>
#include <iostream>
#include "../lib_dsu/dsu.h"

TEST(TestDSULib, correct_create) {
    DSU dsu(5);

    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(i, dsu.find(i));
    }
}

TEST(TestDSULib, correct_union) {
    DSU dsu(3);

    EXPECT_NO_THROW(dsu.unite(1, 1));
    EXPECT_EQ(dsu.find(1), 1);
}

TEST(TestDSULib, correct_find_and_union_1) {
    DSU dsu(3);
    dsu.unite(0, 1);
    dsu.unite(0, 2);

    EXPECT_EQ(dsu.find(0), dsu.find(1));
    EXPECT_EQ(dsu.find(0), dsu.find(2));
    EXPECT_EQ(dsu.find(1), dsu.find(2));
}

TEST(TestDsuLib, correct_find_and_union_2) {
    DSU dsu(8);

    dsu.unite(7, 1);

    dsu.unite(4, 6);
    dsu.unite(2, 3);
    dsu.unite(2, 6);

    dsu.unite(1, 3);
    EXPECT_EQ(dsu.find(7), 2);
    EXPECT_EQ(dsu.find(1), 2);
    EXPECT_EQ(dsu.find(4), 2);
    EXPECT_EQ(dsu.find(3), 2);
    EXPECT_EQ(dsu.find(6), 2);
}

TEST(TestDSULib, correct_find_and_union_3) {
    DSU dsu(6);

    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(3, 4);

    EXPECT_EQ(dsu.find(0), dsu.find(1));
    EXPECT_EQ(dsu.find(0), dsu.find(2));
    EXPECT_EQ(dsu.find(3), dsu.find(4));
    EXPECT_NE(dsu.find(0), dsu.find(3));
    EXPECT_NE(dsu.find(0), dsu.find(5));
    EXPECT_NE(dsu.find(3), dsu.find(5));
}

TEST(TestDSULib, correct_already_union) {
    DSU dsu(4);

    dsu.unite(0, 1);
    int before = dsu.find(0);

    dsu.unite(0, 1);
    dsu.unite(1, 0);

    int after = dsu.find(0);
    EXPECT_EQ(before, after);
    EXPECT_EQ(dsu.find(0), dsu.find(1));
}

TEST(TestDSULib, throw_uncorrect_union_and_find) {
    DSU dsu(3);

    EXPECT_THROW(dsu.unite(-1, 0), std::invalid_argument);
    EXPECT_THROW(dsu.unite(0, 5), std::invalid_argument);
    EXPECT_THROW(dsu.find(-1), std::invalid_argument);
    EXPECT_THROW(dsu.find(10), std::invalid_argument);
}

TEST(TestDSULib, correct_path_compression) {
    DSU dsu(8);

    dsu.unite(1, 2);

    dsu.unite(3, 4);
    dsu.unite(5, 6);
    dsu.unite(4, 5);

    dsu.unite(2, 6);

    EXPECT_EQ(3, dsu.find(4));
    EXPECT_EQ(3, dsu.find(5));
    EXPECT_EQ(3, dsu.find(6));

    EXPECT_EQ(1, dsu.find(2));
    EXPECT_EQ(1, dsu.find(3));
}