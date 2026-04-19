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

    graph.delete_vertex(1);

    graph.add_edge(7, 2, 5);

    //graph.add_edge(7, 2, 15);

    graph.delete_edge(7, 2);
}

#endif  // EASY_EXAMPLE
