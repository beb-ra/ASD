#include <vector>
#include "../lib_matrix/matrix.h"

/*
template <class T>
class MGraph {
	struct Vertex {
		int index;
		T value;
	};
	bool _is_oriented;
	bool _is_weight;
	Matrix<Vertex<T>> _data;
public:
	MGraph(std::vector<std::pair<T, T>>, bool, bool);
	add_vertex(const T&);
	delete_vertex(const T&);
	add_edge(const T&, const T&);
	delete_edge(const T&, const T&);
};

template <class T>
MGraph<T>::MGraph(std::vector<std::pair<T, T>> data, bool is_oriented, bool is_weight) : 
	_is_oriented(is_oriented), _is_weight(is_weight) {
	T min = data[0].first, max = data[0].first;
	std::vector<std::pair<int, T>> vertex;
	for (auto it = data.begin(); it != data.end(); it++) {
		if ((*it).first < min) {
			min = (*it).first;
		}
		if ((*it).second < min) {
			min = (*it).second;
		}
		if ((*it).first > max) {
			max = (*it).first;
		}
		if ((*it).second > max) {
			max = (*it).second;
		}

	}
}
*/