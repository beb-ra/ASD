#include <vector>
#include <set>
#include "../lib_matrix/matrix.h"

template <class T>
class LGraph {
	struct Vertex {
		//int index;
		T _value;
		List<std::pair<Vertex<T>*, int>> _edges;

		Vertex(T value) : _value(value), _edges() {}
		Vertex(T value, std::pair<Vertex<T>*, int> pair) : _value(value), _edges() {
			_edges.push_back(pair);
		}
	};

	bool _is_oriented;
	bool _is_weighted;
	std::vector<List<Vertex<T>*>> graph;

public:
	LGraph(std::vector<std::pair<T, T>>, bool, bool);
	LGraph(std::vector<std::pair<std::pair<T, T>, int>>, bool, bool);
	delete_vertex(const T&);
	add_edge(const T&, const T&);
	delete_edge(const T&, const T&);
};

template <class T>
LGraph<T>::LGraph(std::vector<std::pair<std::pair<T, T>, int>> data, bool is_oriented, bool is_weighted) : 
	_is_oriented(is_oriented), _is_weighted(is_weighted) {
	std::set<T> set_vertex;
	for (int i = 0; i < data.size(); i++) {
		set_vertex.insert(data[i].first.first);
		set_vertex.insert(data[i].first.second);
	}

	std::vector<List<Vertex<T>*>> graph(set_vertex.size());
	if (_is_oriented) {
		for (int i = 0; i < data.size(); i++) {
			Vertex<T> second_vertex(data[i].first.second);
			std::pair<Vertex<T>*, int> pair(second_vertex, data[i].second);
			Vertex<T> first_vertex(data[i].first.first, pair);

			graph[data[i].first.first].push_back(new_vertex);
			if (_is_weighted) {
				std::cout << " ";
			}
			else {
				std::cout << " ";
			}
		}
	}
	else {
		std::cout << " ";
	}
}
