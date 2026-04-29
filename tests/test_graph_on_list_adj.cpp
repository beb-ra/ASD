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

TEST(TestLGraphLib, correct_throw_add_and_delete_edge_in_unoriented_graph) {
    std::vector<std::pair<int, int>> data = {
        {1, 2},
        {4, 5},
        {7, 8}
    };

    LGraph<int> graph(data, false);

    graph.add_edge(5, 7);
    EXPECT_THROW(graph.add_edge(7, 5), std::logic_error);
    graph.delete_edge(7, 5);
    EXPECT_NO_THROW(graph.add_edge(5, 7));
    graph.delete_edge(5, 7);
    EXPECT_NO_THROW(graph.add_edge(7, 5));

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

    EXPECT_THROW(graph.delete_edge(2, 1), std::logic_error);

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

TEST(TestLGraphLib, dijkstra_test_weighted_oriented_graph) {
    std::vector<std::pair<std::pair<int, int>, int>> data = {
        {{1, 2}, 3},
        {{4, 5}, 6},
        {{7, 8}, 9}
    };

    LGraph<int> graph(data, true, true);

    graph.add_edge(2, 7, 5); // 1 -> 2 -> 7 -> 8 | 3 + 5 + 9 (17)

    graph.add_edge(1, 5, 5);
    graph.add_edge(5, 8, 1); // 1 -> 5 -> 8 | 5 + 1 (6)

    graph.add_edge(1, 8, 8); // 1 -> 8 | (8)

    List<int> result = graph.find_min_way(1, 8);
    List<int> expected({ 1, 5, 8 });
    EXPECT_EQ(result, expected);

    graph.delete_edge(1, 5);
    result = graph.find_min_way(1, 8);
    List<int> expected2({ 1, 8 });
    EXPECT_EQ(result, expected2);

    graph.delete_edge(1, 8);
    result = graph.find_min_way(1, 8);
    List<int> expected3({ 1, 2, 7, 8 });
    EXPECT_EQ(result, expected3);

    graph.add_edge(8, 1);
    result = graph.find_min_way(1, 8);
    List<int> expected4({ 1, 2, 7, 8 });
    EXPECT_EQ(result, expected4);

    graph.delete_edge(1, 2);
    EXPECT_THROW(graph.find_min_way(1, 8), std::logic_error);
}

TEST(TestLGraphLib, dijkstra_test_weighted_unoriented_graph) {
    std::vector<std::pair<std::pair<int, int>, int>> data = {
        {{1, 2}, 3},
        {{4, 5}, 6},
        {{7, 8}, 9}
    };

    LGraph<int> graph(data, false, true);

    graph.add_edge(2, 7, 5); // 1 -> 2 -> 7 -> 8 | 3 + 5 + 9 (17)

    graph.add_edge(1, 5, 5);
    graph.add_edge(5, 8, 1); // 1 -> 5 -> 8 | 5 + 1 (6)

    graph.add_edge(1, 8, 8); // 1 -> 8 | (8)

    List<int> result = graph.find_min_way(1, 8);
    List<int> expected({ 1, 5, 8 });
    EXPECT_EQ(result, expected);

    graph.delete_edge(1, 5);
    result = graph.find_min_way(1, 8);
    List<int> expected2({ 1, 8 });
    EXPECT_EQ(result, expected2);

    graph.delete_edge(1, 8);
    result = graph.find_min_way(1, 8);
    List<int> expected3({ 1, 2, 7, 8 });
    EXPECT_EQ(result, expected3);

    graph.delete_edge(1, 2);
    EXPECT_THROW(graph.find_min_way(1, 8), std::logic_error);
}

TEST(TestLGraphLib, dijkstra_test_unweighted_oriented_graph) {
    std::vector<std::pair<std::pair<int, int>, int>> data = {
        {{1, 2}, 3},
        {{4, 5}, 6},
        {{7, 8}, 9}
    };

    LGraph<int> graph(data, true, false);

    graph.add_edge(2, 7, 5); // 1 -> 2 -> 7 -> 8

    graph.add_edge(1, 5, 5);
    graph.add_edge(5, 8, 1); // 1 -> 5 -> 8

    graph.add_edge(1, 8, 8); // 1 -> 8

    List<int> result = graph.find_min_way(1, 8);
    List<int> expected1({ 1, 8 });
    EXPECT_EQ(result, expected1);

    graph.delete_edge(1, 8);
    result = graph.find_min_way(1, 8);
    List<int> expected2({ 1, 5, 8 });
    EXPECT_EQ(result, expected2);

    graph.delete_edge(5, 8);
    result = graph.find_min_way(1, 8);
    List<int> expected3({ 1, 2, 7, 8 });
    EXPECT_EQ(result, expected3);

    graph.add_edge(8, 1);
    result = graph.find_min_way(1, 8);
    List<int> expected4({ 1, 2, 7, 8 });
    EXPECT_EQ(result, expected4);

    graph.delete_edge(1, 2);
    EXPECT_THROW(graph.find_min_way(1, 8), std::logic_error);
}

TEST(TestLGraphLib, dijkstra_test_unweighted_unoriented_graph) {
    std::vector<std::pair<std::pair<int, int>, int>> data = {
        {{1, 2}, 3},
        {{4, 5}, 6},
        {{7, 8}, 9}
    };

    LGraph<int> graph(data, false, false);

    graph.add_edge(2, 7, 5); // 1 -> 2 -> 7 -> 8

    graph.add_edge(1, 5, 5);
    graph.add_edge(5, 8, 1); // 1 -> 5 -> 8

    graph.add_edge(1, 8, 8); // 1 -> 8

    List<int> result = graph.find_min_way(1, 8);
    List<int> expected1({ 1, 8 });
    EXPECT_EQ(result, expected1);

    graph.delete_edge(1, 8);
    result = graph.find_min_way(1, 8);
    List<int> expected2({ 1, 5, 8 });
    EXPECT_EQ(result, expected2);

    graph.delete_edge(5, 8);
    result = graph.find_min_way(1, 8);
    List<int> expected3({ 1, 2, 7, 8 });
    EXPECT_EQ(result, expected3);

    graph.add_edge(8, 1);
    result = graph.find_min_way(1, 8);
    List<int> expected4({ 1, 8 });
    EXPECT_EQ(result, expected4);

    graph.delete_edge(1, 2);
    graph.delete_edge(1, 8);
    EXPECT_THROW(graph.find_min_way(1, 8), std::logic_error);
}