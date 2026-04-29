#include <gtest/gtest.h>
#include "../lib_graph_on_matrix/graph_on_matrix.h"

TEST(TestMGraphLib, correct_create_oriented_weighted_graph) {
    std::vector<std::pair<std::pair<int, int>, int>> data = {
        {{1, 2}, 3},
        {{4, 5}, 6},
        {{7, 8}, 9}
    };

    MGraph<int> graph(data, true, true);
    std::cout << graph;

    EXPECT_EQ(graph.data()[0][1], 3);
    EXPECT_EQ(graph.data()[2][3], 6);
    EXPECT_EQ(graph.data()[4][5], 9);

    EXPECT_EQ(graph.data()[1][5], 0);
    EXPECT_EQ(graph.data()[3][2], 0);
}

TEST(TestMGraphLib, correct_create_oriented_unweighted_graph_first_constructor) {
    std::vector<std::pair<std::pair<int, int>, int>> data = {
        {{1, 2}, 3},
        {{4, 5}, 6},
        {{7, 8}, 9}
    };

    MGraph<int> graph(data, true, false);
    EXPECT_EQ(graph.data()[0][1], 1);
    EXPECT_EQ(graph.data()[2][3], 1);
    EXPECT_EQ(graph.data()[4][5], 1);

    EXPECT_EQ(graph.data()[2][5], 0);
    EXPECT_EQ(graph.data()[3][2], 0);
}

TEST(TestMGraphLib, correct_create_unoriented_weighted_graph) {
    std::vector<std::pair<std::pair<int, int>, int>> data = {
        {{1, 2}, 3},
        {{4, 5}, 6},
        {{7, 8}, 9}
    };

    MGraph<int> graph(data, false, true);
    EXPECT_EQ(graph.data()[0][1], 3);
    EXPECT_EQ(graph.data()[2][3], 6);
    EXPECT_EQ(graph.data()[4][5], 9);

    EXPECT_EQ(graph.data()[3][4], 0);
    EXPECT_EQ(graph.data()[1][0], 3);
    EXPECT_EQ(graph.data()[3][2], 6);
    EXPECT_EQ(graph.data()[5][4], 9);
}

TEST(TestMGraphLib, correct_create_unoriented_unweighted_graph_first_constructor) {
    std::vector<std::pair<std::pair<int, int>, int>> data = {
        {{1, 2}, 3},
        {{4, 5}, 6},
        {{7, 8}, 9}
    };

    MGraph<int> graph(data, false, false);
    EXPECT_EQ(graph.data()[0][1], 1);
    EXPECT_EQ(graph.data()[2][3], 1);
    EXPECT_EQ(graph.data()[4][5], 1);

    EXPECT_EQ(graph.data()[1][2], 0);
    EXPECT_EQ(graph.data()[1][0], 1);
    EXPECT_EQ(graph.data()[3][2], 1);
    EXPECT_EQ(graph.data()[5][4], 1);
}

TEST(TestMGraphLib, correct_create_oriented_unweighted_graph_second_constructor) {
    std::vector<std::pair<int, int>> data = {
        {1, 2},
        {4, 5},
        {7, 8}
    };

    MGraph<int> graph(data, true);
    EXPECT_EQ(graph.data()[0][1], 1);
    EXPECT_EQ(graph.data()[2][3], 1);
    EXPECT_EQ(graph.data()[4][5], 1);

    EXPECT_EQ(graph.data()[1][4], 0);
    EXPECT_EQ(graph.data()[3][2], 0);
}

TEST(TestMGraphLib, correct_create_unoriented_unweighted_graph_second_constructor) {
    std::vector<std::pair<int, int>> data = {
        {1, 2},
        {4, 5},
        {7, 8}
    };

    MGraph<int> graph(data, false);
    EXPECT_EQ(graph.data()[0][1], 1);
    EXPECT_EQ(graph.data()[2][3], 1);
    EXPECT_EQ(graph.data()[4][5], 1);

    EXPECT_EQ(graph.data()[0][2], 0);
    EXPECT_EQ(graph.data()[1][0], 1);
    EXPECT_EQ(graph.data()[3][2], 1);
    EXPECT_EQ(graph.data()[5][4], 1);
}

TEST(TestMGraphLib, correct_add_edge_and_delete_edge) {
    std::vector<std::pair<int, int>> data = {
        {1, 2},
        {4, 5},
        {7, 8}
    };

    MGraph<int> graph(data, true);
    EXPECT_EQ(graph.data()[0][1], 1);
    EXPECT_EQ(graph.data()[2][3], 1);
    EXPECT_EQ(graph.data()[4][5], 1);

    graph.add_edge(2, 5);
    EXPECT_EQ(graph.data()[1][3], 1);
    graph.add_edge(2, 8);
    EXPECT_EQ(graph.data()[1][5], 1);

    graph.delete_edge(2, 8);
    EXPECT_EQ(graph.data()[0][1], 1);
    EXPECT_EQ(graph.data()[1][3], 1);
    EXPECT_EQ(graph.data()[4][5], 1);
    EXPECT_EQ(graph.data()[2][3], 1);
    EXPECT_EQ(graph.data()[1][5], 0);

    graph.delete_edge(4, 5);
    EXPECT_EQ(graph.data()[0][1], 1);
    EXPECT_EQ(graph.data()[1][3], 1);
    EXPECT_EQ(graph.data()[4][5], 1);
    EXPECT_EQ(graph.data()[2][3], 0);
}

TEST(TestMGraphLib, correct_add_edge_and_delete_edge_unoriented_graph) {
    std::vector<std::pair<int, int>> data = {
        {1, 2},
        {4, 5},
        {7, 8}
    };

    MGraph<int> graph(data, false);
    EXPECT_EQ(graph.data()[0][1], 1);
    EXPECT_EQ(graph.data()[2][3], 1);
    EXPECT_EQ(graph.data()[4][5], 1);

    graph.add_edge(2, 5);
    EXPECT_EQ(graph.data()[1][3], 1);
    EXPECT_EQ(graph.data()[3][1], 1);
    graph.add_edge(2, 8);
    EXPECT_EQ(graph.data()[1][5], 1);
    EXPECT_EQ(graph.data()[5][1], 1);

    graph.delete_edge(2, 8);
    EXPECT_EQ(graph.data()[0][1], 1);
    EXPECT_EQ(graph.data()[1][3], 1);
    EXPECT_EQ(graph.data()[4][5], 1);
    EXPECT_EQ(graph.data()[2][3], 1);
    EXPECT_EQ(graph.data()[1][0], 1);
    EXPECT_EQ(graph.data()[3][1], 1);
    EXPECT_EQ(graph.data()[5][4], 1);
    EXPECT_EQ(graph.data()[3][2], 1);
    EXPECT_EQ(graph.data()[1][5], 0);
    EXPECT_EQ(graph.data()[5][1], 0);

    graph.delete_edge(4, 5);
    EXPECT_EQ(graph.data()[0][1], 1);
    EXPECT_EQ(graph.data()[1][3], 1);
    EXPECT_EQ(graph.data()[4][5], 1);
    EXPECT_EQ(graph.data()[1][0], 1);
    EXPECT_EQ(graph.data()[3][1], 1);
    EXPECT_EQ(graph.data()[5][4], 1);
    EXPECT_EQ(graph.data()[2][3], 0);
    EXPECT_EQ(graph.data()[3][2], 0);
}

TEST(TestMGraphLib, correct_add_edge_and_delete_all_edges) {
    std::vector<std::pair<int, int>> data = {
        {1, 2},
        {4, 5},
        {7, 8}
    };

    MGraph<int> graph(data, true);
    EXPECT_EQ(graph.data()[0][1], 1);
    EXPECT_EQ(graph.data()[2][3], 1);
    EXPECT_EQ(graph.data()[4][5], 1);

    graph.add_edge(2, 5);
    graph.add_edge(2, 8);

    graph.delete_all_edges_at_vertex(2);
    EXPECT_EQ(graph.data()[0][1], 0);
    EXPECT_EQ(graph.data()[1][3], 0);
    EXPECT_EQ(graph.data()[1][5], 0);

    EXPECT_EQ(graph.data()[2][3], 1);
    EXPECT_EQ(graph.data()[4][5], 1);
}

TEST(TestMGraphLib, correct_add_edge_and_delete_all_edges_unoriented_graph) {
    std::vector<std::pair<int, int>> data = {
        {1, 2},
        {4, 5},
        {7, 8}
    };

    MGraph<int> graph(data, false);
    EXPECT_EQ(graph.data()[0][1], 1);
    EXPECT_EQ(graph.data()[2][3], 1);
    EXPECT_EQ(graph.data()[4][5], 1);
    EXPECT_EQ(graph.data()[1][0], 1);
    EXPECT_EQ(graph.data()[3][2], 1);
    EXPECT_EQ(graph.data()[5][4], 1);

    graph.add_edge(2, 5);
    graph.add_edge(2, 8);

    graph.delete_all_edges_at_vertex(2);
    EXPECT_EQ(graph.data()[0][1], 0);
    EXPECT_EQ(graph.data()[1][3], 0);
    EXPECT_EQ(graph.data()[1][5], 0);
    EXPECT_EQ(graph.data()[1][0], 0);
    EXPECT_EQ(graph.data()[3][1], 0);
    EXPECT_EQ(graph.data()[5][1], 0);

    EXPECT_EQ(graph.data()[2][3], 1);
    EXPECT_EQ(graph.data()[4][5], 1);
    EXPECT_EQ(graph.data()[3][2], 1);
    EXPECT_EQ(graph.data()[5][4], 1);
}

