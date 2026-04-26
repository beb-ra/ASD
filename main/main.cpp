// Copyright 2024 Marina Usova

#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "graph_on_list_adj.h"

int main() {
    std::vector<std::pair<std::pair<int, int>, int>> data = {
        {{1, 2}, 3},
        {{4, 5}, 6},
        {{7, 8}, 9}
    };

	LGraph<int> graph(data, true, true);

    graph.add_edge(2, 7, 5);

    graph.add_edge(1, 5, 5);
    graph.add_edge(5, 8, 1);

    graph.add_edge(1, 8, 8);

    List<int> list = graph.find_min_way(1, 8);
    for (auto it = list.begin(); it != list.end(); it++) {
        std::cout << *it << " ";
    }
}

#endif  // EASY_EXAMPLE
