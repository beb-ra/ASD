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

    EXPECT_NO_THROW(dsu.dsu_union(1, 1));
    EXPECT_EQ(dsu.find(1), 1);
}

TEST(TestDSULib, correct_find_and_union) {
    DSU dsu(6);

    dsu.dsu_union(0, 1);
    dsu.dsu_union(1, 2);
    dsu.dsu_union(3, 4);

    EXPECT_EQ(dsu.find(0), dsu.find(1));
    EXPECT_EQ(dsu.find(1), dsu.find(2));
    EXPECT_EQ(dsu.find(3), dsu.find(4));
    EXPECT_NE(dsu.find(0), dsu.find(3));
    EXPECT_NE(dsu.find(0), dsu.find(5));
}

TEST(TestDSULib, throw_uncorrect_union_and_find) {
    DSU dsu(3);

    EXPECT_THROW(dsu.dsu_union(-1, 0), std::invalid_argument);
    EXPECT_THROW(dsu.dsu_union(0, 5), std::invalid_argument);
    EXPECT_THROW(dsu.find(-1), std::invalid_argument);
    EXPECT_THROW(dsu.find(10), std::invalid_argument);
}

TEST(TestDSULib, correct_path_compression) {
    DSU dsu(5);

    dsu.dsu_union(0, 1);
    dsu.dsu_union(1, 2);
    dsu.dsu_union(2, 3);

    int parent1 = dsu.find(0);
    int parent2 = dsu.find(3);

    EXPECT_EQ(parent1, parent2);
}