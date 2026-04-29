#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include "../lib_matrix/matrix.h"

template <class T>
class MGraph {
	bool _is_oriented;
	bool _is_weighted;
	Matrix<int> _graph;
	std::unordered_map<T, int> _value_to_index;
public:
	MGraph(std::vector<std::pair<T, T>>, bool is_oriented);
	MGraph(std::vector<std::pair<std::pair<T, T>, int>>, bool is_oriented,
		bool is_weighted);
	void delete_all_edges_at_vertex(const T&) noexcept;
	void add_edge(const T&, const T&, int weight = 1);
	void delete_edge(const T&, const T&);

	const Matrix<int>& data() const noexcept {
		return _graph;
	}

	friend std::ostream& operator<<(std::ostream& os, const MGraph& graph) {
		std::vector<T> index_to_value(graph._graph.get_n());
		for (const auto& pair : graph._value_to_index) {
			index_to_value[pair.second] = pair.first;
		}
		os << "      ";
		for (int j = 0; j < graph._graph.get_n(); j++) {
			os << std::setw(4) << index_to_value[j] << " ";
		}
		os << "\n      ";
		for (int j = 0; j < graph._graph.get_n(); j++) {
			os << "-----";
		}
		os << "\n";
		for (int i = 0; i < graph._graph.get_n(); i++) {
			os << std::setw(4) << index_to_value[i] << " |";

			for (int j = 0; j < graph._graph.get_n(); j++) {
				os << std::setw(4) << graph._graph[i][j] << " ";
			}
			os << "\n";
		}

		return os;
	}
};

template <class T>
MGraph<T>::MGraph(std::vector<std::pair<std::pair<T, T>, int>> data, bool is_oriented, bool is_weight) :
	_is_oriented(is_oriented), _is_weighted(is_weight), _value_to_index() {
	std::unordered_set<T> set_vertex;
	int index = 0;
	for (int i = 0; i < data.size(); i++) {
		if (set_vertex.find(data[i].first.first) == set_vertex.end()) {
			set_vertex.insert(data[i].first.first);
			_value_to_index.insert({ data[i].first.first, index++ });
		}
		if (set_vertex.find(data[i].first.second) == set_vertex.end()) {
			set_vertex.insert(data[i].first.second);
			_value_to_index.insert({ data[i].first.second, index++ });
		}
	}

	std::vector<int> zeros(set_vertex.size() * set_vertex.size(), 0);
	_graph = Matrix<int>(set_vertex.size(), set_vertex.size(), zeros.data());

	for (int i = 0; i < data.size(); i++) {
		if (data[i].first.first == data[i].first.second) {
			throw std::logic_error("The edge must connect two different vertices");
		}
		int from_index = _value_to_index[data[i].first.first];
		int to_index = _value_to_index[data[i].first.second];

		int weight = (_is_weighted) ? data[i].second : 1;
		_graph[from_index][to_index] = weight;
		if (!_is_oriented) {
			_graph[to_index][from_index] = weight;
		}
	}
}

template <class T>
MGraph<T>::MGraph(std::vector<std::pair<T, T>> data, bool is_oriented) :
	_is_oriented(is_oriented), _is_weighted(false), _value_to_index() {
	std::unordered_set<T> set_vertex;
	int index = 0;
	for (int i = 0; i < data.size(); i++) {
		if (set_vertex.find(data[i].first) == set_vertex.end()) {
			set_vertex.insert(data[i].first);
			_value_to_index.insert({ data[i].first, index++ });
		}
		if (set_vertex.find(data[i].second) == set_vertex.end()) {
			set_vertex.insert(data[i].second);
			_value_to_index.insert({ data[i].second, index++ });
		}
	}

	std::vector<int> zeros(set_vertex.size() * set_vertex.size(), 0);
	_graph = Matrix<int>(set_vertex.size(), set_vertex.size(), zeros.data());

	for (int i = 0; i < data.size(); i++) {
		if (data[i].first == data[i].second) {
			throw std::logic_error("The edge must connect two different vertices");
		}
		int from_index = _value_to_index[data[i].first];
		int to_index = _value_to_index[data[i].second];

		_graph[from_index][to_index] = 1;
		if (!_is_oriented) {
			_graph[to_index][from_index] = 1;
		}
	}
}

template <class T>
void MGraph<T>::delete_all_edges_at_vertex(const T& value) noexcept {
	int index = _value_to_index[value];
	for (int i = 0; i < _graph.get_n(); i++) {
		_graph[i][index] = 0;
		_graph[index][i] = 0;
	}
}

template <class T>
void MGraph<T>::add_edge(const T& first_value, const T& second_value, int weight) {
	int first_index = _value_to_index[first_value];
	int second_index = _value_to_index[second_value];
	if (_graph[first_index][second_index]) {
		throw std::logic_error("The edge is already exist");
	}
	_graph[first_index][second_index] = weight;
	if (!_is_oriented) {
		_graph[second_index][first_index] = weight;
	}
}

template <class T>
void MGraph<T>::delete_edge(const T& first_value, const T& second_value) {
	int first_index = _value_to_index[first_value];
	int second_index = _value_to_index[second_value];
	if (!_graph[first_index][second_index]) {
		throw std::logic_error("The edge is not found");
	}
	_graph[first_index][second_index] = 0;
	if (!_is_oriented) {
		_graph[second_index][first_index] = 0;
	}
}
