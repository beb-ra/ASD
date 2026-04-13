#include <iostream>
#include "../lib_matrix/matrix.h"

template <class T>
class MGraph {
	struct Vertex {
		T value;
	};
	bool _is_oriented;
	bool _is_weight;
	Matrix<T> _data;
public:
	MGraph(std::vector<std::pair<T>>, bool, bool);
	add_vertex(const T&);
	delete_vertex(const T&);
	add_edge(const T&, const T&);
	delete_edge(const T&, const T&);
};