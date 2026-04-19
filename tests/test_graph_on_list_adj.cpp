#include <gtest/gtest.h>
#include "../lib_graph_on_list_adj/graph_on_list_adj.h"

TEST(TestLGraphLib, correct_create) {
    std::vector<std::pair<std::pair<int, int>, int>> data = {
        {{1, 2}, 3},
        {{4, 5}, 6},
        {{7, 8}, 9}
    };

    LGraph<int> graph(data, true, true);

    EXPECT_EQ(graph.data()[0]->_value, 1);
    EXPECT_EQ(graph.data()[1]->_value, 2);
    EXPECT_EQ(graph.data()[2]->_value, 4);
    EXPECT_EQ(graph.data()[3]->_value, 5);
    EXPECT_EQ(graph.data()[4]->_value, 7);
    EXPECT_EQ(graph.data()[5]->_value, 8);

    EXPECT_EQ(graph.data()[0]->_edges.head()->value.first->_value, 2);
    EXPECT_EQ(graph.data()[0]->_edges.head()->value.second, 3);
    EXPECT_EQ(graph.data()[2]->_edges.head()->value.first->_value, 5);
    EXPECT_EQ(graph.data()[2]->_edges.head()->value.second, 6);
    EXPECT_EQ(graph.data()[4]->_edges.head()->value.first->_value, 8);
    EXPECT_EQ(graph.data()[4]->_edges.head()->value.second, 9);
}