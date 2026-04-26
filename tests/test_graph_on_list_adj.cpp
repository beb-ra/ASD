#include <gtest/gtest.h>
#include "../lib_graph_on_list_adj/graph_on_list_adj.h"

TEST(TestLGraphLib, correct_create_oriented_weighted_graph) {
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

TEST(TestLGraphLib, correct_create_oriented_unweighted_graph_first_constructor) {
    std::vector<std::pair<std::pair<int, int>, int>> data = {
        {{1, 2}, 3},
        {{4, 5}, 6},
        {{7, 8}, 9}
    };

    LGraph<int> graph(data, true, false);

    EXPECT_EQ(graph.data()[0]->_value, 1);
    EXPECT_EQ(graph.data()[1]->_value, 2);
    EXPECT_EQ(graph.data()[2]->_value, 4);
    EXPECT_EQ(graph.data()[3]->_value, 5);
    EXPECT_EQ(graph.data()[4]->_value, 7);
    EXPECT_EQ(graph.data()[5]->_value, 8);

    EXPECT_EQ(graph.data()[0]->_edges.head()->value.first->_value, 2);
    EXPECT_EQ(graph.data()[0]->_edges.head()->value.second, 1);
    EXPECT_EQ(graph.data()[2]->_edges.head()->value.first->_value, 5);
    EXPECT_EQ(graph.data()[2]->_edges.head()->value.second, 1);
    EXPECT_EQ(graph.data()[4]->_edges.head()->value.first->_value, 8);
    EXPECT_EQ(graph.data()[4]->_edges.head()->value.second, 1);
}

TEST(TestLGraphLib, correct_create_unoriented_weighted_graph) {
    std::vector<std::pair<std::pair<int, int>, int>> data = {
        {{1, 2}, 3},
        {{4, 5}, 6},
        {{7, 8}, 9}
    };

    LGraph<int> graph(data, false, true);

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

    EXPECT_EQ(graph.data()[1]->_edges.head()->value.first->_value, 1);
    EXPECT_EQ(graph.data()[1]->_edges.head()->value.second, 3);
    EXPECT_EQ(graph.data()[3]->_edges.head()->value.first->_value, 4);
    EXPECT_EQ(graph.data()[3]->_edges.head()->value.second, 6);
    EXPECT_EQ(graph.data()[5]->_edges.head()->value.first->_value, 7);
    EXPECT_EQ(graph.data()[5]->_edges.head()->value.second, 9);
}

TEST(TestLGraphLib, correct_create_unoriented_unweighted_graph_first_constructor) {
    std::vector<std::pair<std::pair<int, int>, int>> data = {
        {{1, 2}, 3},
        {{4, 5}, 6},
        {{7, 8}, 9}
    };

    LGraph<int> graph(data, false, false);

    EXPECT_EQ(graph.data()[0]->_value, 1);
    EXPECT_EQ(graph.data()[1]->_value, 2);
    EXPECT_EQ(graph.data()[2]->_value, 4);
    EXPECT_EQ(graph.data()[3]->_value, 5);
    EXPECT_EQ(graph.data()[4]->_value, 7);
    EXPECT_EQ(graph.data()[5]->_value, 8);

    EXPECT_EQ(graph.data()[0]->_edges.head()->value.first->_value, 2);
    EXPECT_EQ(graph.data()[0]->_edges.head()->value.second, 1);
    EXPECT_EQ(graph.data()[2]->_edges.head()->value.first->_value, 5);
    EXPECT_EQ(graph.data()[2]->_edges.head()->value.second, 1);
    EXPECT_EQ(graph.data()[4]->_edges.head()->value.first->_value, 8);
    EXPECT_EQ(graph.data()[4]->_edges.head()->value.second, 1);

    EXPECT_EQ(graph.data()[1]->_edges.head()->value.first->_value, 1);
    EXPECT_EQ(graph.data()[1]->_edges.head()->value.second, 1);
    EXPECT_EQ(graph.data()[3]->_edges.head()->value.first->_value, 4);
    EXPECT_EQ(graph.data()[3]->_edges.head()->value.second, 1);
    EXPECT_EQ(graph.data()[5]->_edges.head()->value.first->_value, 7);
    EXPECT_EQ(graph.data()[5]->_edges.head()->value.second, 1);
}

TEST(TestLGraphLib, correct_create_oriented_unweighted_graph_second_constructor) {
    std::vector<std::pair<int, int>> data = {
        {1, 2},
        {4, 5},
        {7, 8}
    };

    LGraph<int> graph(data, true);

    EXPECT_EQ(graph.data()[0]->_value, 1);
    EXPECT_EQ(graph.data()[1]->_value, 2);
    EXPECT_EQ(graph.data()[2]->_value, 4);
    EXPECT_EQ(graph.data()[3]->_value, 5);
    EXPECT_EQ(graph.data()[4]->_value, 7);
    EXPECT_EQ(graph.data()[5]->_value, 8);

    EXPECT_EQ(graph.data()[0]->_edges.head()->value.first->_value, 2);
    EXPECT_EQ(graph.data()[0]->_edges.head()->value.second, 1);
    EXPECT_EQ(graph.data()[2]->_edges.head()->value.first->_value, 5);
    EXPECT_EQ(graph.data()[2]->_edges.head()->value.second, 1);
    EXPECT_EQ(graph.data()[4]->_edges.head()->value.first->_value, 8);
    EXPECT_EQ(graph.data()[4]->_edges.head()->value.second, 1);
}

TEST(TestLGraphLib, correct_create_unoriented_unweighted_graph_second_constructor) {
    std::vector<std::pair<int, int>> data = {
        {1, 2},
        {4, 5},
        {7, 8}
    };

    LGraph<int> graph(data, false);

    EXPECT_EQ(graph.data()[0]->_value, 1);
    EXPECT_EQ(graph.data()[1]->_value, 2);
    EXPECT_EQ(graph.data()[2]->_value, 4);
    EXPECT_EQ(graph.data()[3]->_value, 5);
    EXPECT_EQ(graph.data()[4]->_value, 7);
    EXPECT_EQ(graph.data()[5]->_value, 8);

    EXPECT_EQ(graph.data()[0]->_edges.head()->value.first->_value, 2);
    EXPECT_EQ(graph.data()[0]->_edges.head()->value.second, 1);
    EXPECT_EQ(graph.data()[2]->_edges.head()->value.first->_value, 5);
    EXPECT_EQ(graph.data()[2]->_edges.head()->value.second, 1);
    EXPECT_EQ(graph.data()[4]->_edges.head()->value.first->_value, 8);
    EXPECT_EQ(graph.data()[4]->_edges.head()->value.second, 1);

    EXPECT_EQ(graph.data()[1]->_edges.head()->value.first->_value, 1);
    EXPECT_EQ(graph.data()[1]->_edges.head()->value.second, 1);
    EXPECT_EQ(graph.data()[3]->_edges.head()->value.first->_value, 4);
    EXPECT_EQ(graph.data()[3]->_edges.head()->value.second, 1);
    EXPECT_EQ(graph.data()[5]->_edges.head()->value.first->_value, 7);
    EXPECT_EQ(graph.data()[5]->_edges.head()->value.second, 1);
}

TEST(TestLGraphLib, correct_add_vertex) {
    std::vector<std::pair<int, int>> data = {
        {1, 2},
        {4, 5},
        {7, 8}
    };

    LGraph<int> graph(data, false);
    std::cout << graph;

    graph.add_vertex(11);
    EXPECT_TRUE(graph.data()[6]->_edges.is_empty());
    graph.add_edge(11, 1);
    EXPECT_EQ(graph.data()[0]->_edges.head()->next->value.first->_value, 11);
    EXPECT_EQ(graph.data()[6]->_edges.head()->value.first->_value, 1);

    std::cout << graph;
}

TEST(TestLGraphLib, correct_add_edge_and_delete_edge) {
    std::vector<std::pair<int, int>> data = {
        {1, 2},
        {4, 5},
        {7, 8}
    };

    LGraph<int> graph(data, true);
    graph.add_edge(4, 8);

    graph.add_vertex(11);

    graph.add_edge(4, 11);
    graph.add_edge(2, 5);
    std::cout << graph;

    EXPECT_EQ(graph.data()[1]->_edges.head()->value.first->_value, 5);
    EXPECT_EQ(graph.data()[2]->_edges.head()->value.first->_value, 5);
    EXPECT_EQ(graph.data()[2]->_edges.head()->next->value.first->_value, 8);
    EXPECT_EQ(graph.data()[2]->_edges.head()->next->next->value.first->_value, 11);

    graph.delete_edge(4, 8);
    EXPECT_EQ(graph.data()[2]->_edges.head()->value.first->_value, 5);
    EXPECT_EQ(graph.data()[2]->_edges.head()->next->value.first->_value, 11);

    graph.delete_edge(4, 5);
    EXPECT_EQ(graph.data()[2]->_edges.head()->value.first->_value, 11);

    graph.delete_edge(4, 11);
    EXPECT_TRUE(graph.data()[2]->_edges.is_empty());

    std::cout << graph;
}

TEST(TestLGraphLib, correct_delete_vertex) {
    std::vector<std::pair<int, int>> data = {
        {1, 2},
        {4, 5},
        {7, 8}
    };

    LGraph<int> graph(data, false);
    std::cout << graph;

    graph.add_vertex(11);
    EXPECT_TRUE(graph.data()[6]->_edges.is_empty());

    graph.add_edge(11, 8);
    EXPECT_EQ(graph.data()[5]->_edges.head()->next->value.first->_value, 11);
    EXPECT_EQ(graph.data()[6]->_edges.head()->value.first->_value, 8);

    graph.add_edge(8, 4);
    graph.add_edge(4, 2);
    graph.add_edge(4, 11);
    graph.delete_vertex(8);
    EXPECT_EQ(graph.data()[5]->_edges.head()->next, nullptr); // 11: 4
    EXPECT_TRUE(graph.data()[4]->_edges.is_empty()); // 8: 
    EXPECT_EQ(graph.data()[2]->_edges.head()->next->next->value.first->_value, 11); // 4: 5 2 11
    EXPECT_EQ(graph.data()[2]->_edges.head()->next->value.first->_value, 2);
    EXPECT_EQ(graph.data()[2]->_edges.head()->value.first->_value, 5);

    std::cout << graph;
}


