#include <vector>
#include <set>
#include <map>
#include "../lib_list/list.h"
#include "../lib_matrix/matrix.h"

template <class T>
class LGraph {
	struct Vertex {
		int _index;
		T _value;
		List<std::pair<Vertex*, int>> _edges;

		Vertex(int index, T value) : _index(index), _value(value), _edges() {}
		Vertex(int index, T value, std::pair<Vertex*, int> pair) :
			_index(index), _value(value), _edges() {
			_edges.push_back(pair);
		}
	};

	bool _is_oriented;
	bool _is_weighted;
	std::vector<Vertex*> _graph;

public:
	LGraph(std::vector<std::pair<T, T>>, bool, bool);
	LGraph(std::vector<std::pair<std::pair<T, T>, int>>, bool, bool);
	void delete_vertex(const T&);
	void add_edge(const T&, const T&, int weight = 0);
	void delete_edge(const T&, const T&);

	const std::vector<Vertex*> data() const noexcept {
		return _graph;
	}
private:
	int find_vertex_index(const T&) const;
};

template <class T>
LGraph<T>::LGraph(std::vector<std::pair<std::pair<T, T>, int>> data, bool is_oriented, bool is_weighted) :
	_is_oriented(is_oriented), _is_weighted(is_weighted) { // если вершина сама с собой че будет
	std::set<T> set_vertex;
	std::map<T, Vertex*> temp_index;
	int index = 0;
	for (int i = 0; i < data.size(); i++) {
		if (set_vertex.find(data[i].first.first) == set_vertex.end()) {
			set_vertex.insert(data[i].first.first);
			Vertex* new_vertex = new Vertex(index, data[i].first.first);
			temp_index.insert({ data[i].first.first, new_vertex });
			index++;
		}
		if (set_vertex.find(data[i].first.second) == set_vertex.end()) {
			set_vertex.insert(data[i].first.second);
			Vertex* new_vertex = new Vertex(index, data[i].first.second);
			temp_index.insert({ data[i].first.second, new_vertex });
			index++;
		}
	}

	_graph.resize(set_vertex.size());

	for (auto it = temp_index.begin(); it != temp_index.end(); it++) {
		_graph[(*it).second->_index] = (*it).second;
	}

	for (int i = 0; i < data.size(); i++) {
		if (data[i].first.first == data[i].first.second) {
			throw std::logic_error("The edge must connect two different vertices");
		}
		Vertex* from_vertex = temp_index[data[i].first.first];
		Vertex* to_vertex = temp_index[data[i].first.second];

		int weight = data[i].second;

		from_vertex->_edges.push_back({ to_vertex, weight });

		if (!_is_oriented) {
			to_vertex->_edges.push_back({ from_vertex, weight });
		}
	}

	std::cout << "";
}

template <class T>
void LGraph<T>::delete_vertex(const T& value) {
	int index_to_remove = find_vertex_index(value);
	_graph.erase(_graph.begin() + index_to_remove);

	int i = 0;
	for (auto it = _graph.begin(); it != _graph.end(); it++, i++) {
		if ((*it)->_index > index_to_remove) {
			(*it)->_index = i;
		}
		if ((*it)->_edges.is_empty()) continue;

		auto it1 = (*it)->_edges.begin();
		if ((*it1).first->_value == value) {
			(*it)->_edges.pop_front();
			continue;
		}
		for (; it1 != (*it)->_edges.end(); it1++) {
			auto it2 = it1;
			it2++;
			if (it2 == (*it)->_edges.end()) break;

			if ((*it2).first->_value == value) {
				(*it)->_edges.erase(it1.current());
			}
		}
	}

	std::cout << "";
}

template <class T>
int LGraph<T>::find_vertex_index(const T& value) const {
	for (int i = 0; i < _graph.size(); i++) {
		if (_graph[i]->_value == value) {
			return i;
		}
	}
	throw std::logic_error("The vertex not found");
}

template <class T>
void LGraph<T>::add_edge(const T& first_value, const T& second_value, int weight) {
	if (first_value == second_value) {
		throw std::logic_error("The edge must connect two different vertices");
	}
	int first_index = find_vertex_index(first_value);
	int second_index = find_vertex_index(second_value);

	// существовало ли ребро до этого
	for (auto it = _graph[first_index]->_edges.begin(); it != _graph[first_index]->_edges.end(); it++) {
		if ((*it).first == _graph[second_index]) {
			throw std::logic_error("The edge already exist");
		}
	}

	_graph[first_index]->_edges.push_back({ _graph[second_index], weight });
	if (!_is_oriented) {
		_graph[second_index]->_edges.push_back({ _graph[first_index], weight });
	}

	std::cout << "";
}

template <class T>
void LGraph<T>::delete_edge(const T& first_value, const T& second_value) {
	int first_index = find_vertex_index(first_value);
	int second_index = find_vertex_index(second_value);

	auto it1 = _graph[first_index]->_edges.begin();
	if ((*it1).first == _graph[second_index]) {
		_graph[first_index]->_edges.pop_front();
		return;
	}
	for (; it1 != _graph[first_index]->_edges.end(); it1++) {
		auto it2 = it1;
		it2++;
		if (it2 == _graph[first_index]->_edges.end()) break;

		if ((*it2).first == _graph[second_index]) {
			_graph[first_index]->_edges.erase(it1.current());
			return;
		}
	}
	throw std::logic_error("The edge not found");
}

/*
template <class T>
class LGraph {
	struct Vertex {
		int _index;
		T _value;
		List<std::pair<Vertex*, int>> _edges;

		Vertex(int index, T value) : _index(index), _value(value), _edges() {}
		Vertex(int index, T value, std::pair<Vertex*, int> pair) : 
			_index(index), _value(value), _edges() {
			_edges.push_back(pair);
		}
	};

	bool _is_oriented;
	bool _is_weighted;
	std::vector<List<Vertex*>> _graph;

public:
	LGraph(std::vector<std::pair<T, T>>, bool, bool);
	LGraph(std::vector<std::pair<std::pair<T, T>, int>>, bool, bool);
	void delete_vertex(const T&);
	void add_edge(const T&, const T&);
	void delete_edge(const T&, const T&);

private:
	int find_vertex_index(const T&) const;
};

template <class T>
LGraph<T>::LGraph(std::vector<std::pair<std::pair<T, T>, int>> data, bool is_oriented, bool is_weighted) : 
	_is_oriented(is_oriented), _is_weighted(is_weighted) {
	std::set<T> set_vertex;
	std::map<T, Vertex*> temp_index;
	int index = 0;
	for (int i = 0; i < data.size(); i++) {
		if (set_vertex.find(data[i].first.first) == set_vertex.end()) {
			set_vertex.insert(data[i].first.first);
			Vertex* new_vertex = new Vertex(index, data[i].first.first);
			temp_index.insert({ data[i].first.first, new_vertex });
			index++;
		}
		if (set_vertex.find(data[i].first.second) == set_vertex.end()) {
			set_vertex.insert(data[i].first.second);
			Vertex* new_vertex = new Vertex(index, data[i].first.second);
			temp_index.insert({ data[i].first.second, new_vertex });
			index++;
		}
	}

	_graph.resize(set_vertex.size());

	for (auto it = temp_index.begin(); it != temp_index.end(); it++) {
		_graph[(*it).second->_index].push_back((*it).second);
	}

	for (int i = 0; i < data.size(); i++) {
		Vertex* from_vertex = temp_index[data[i].first.first];
		Vertex* to_vertex = temp_index[data[i].first.second];
		int weight = data[i].second;

		from_vertex->_edges.push_back({ to_vertex, weight });

		_graph[from_vertex->_index].push_back(to_vertex);

		if (!_is_oriented) {
			to_vertex->_edges.push_back({ from_vertex, weight });
			_graph[to_vertex->_index].push_back(from_vertex);
		}
	}

	std::cout << "";
}

template <class T>
void LGraph<T>::delete_vertex(const T& value) {
	int index_to_remove = find_vertex_index(value);
	_graph.erase(_graph.begin() + index_to_remove);

	int i = 0;
	for (auto it = _graph.begin(); it != _graph.end(); it++, i++) {
		auto it1 = (*it).begin();
		if ((*it1)->_value == value) {
			(*it).pop_front();
		}
		for (; it1 != (*it).end(); it1++) {
			auto it2 = it1;
			it2++;
			if (it2 == (*it).end()) break;

			if ((*it2)->_value == value) {
				(*it).erase(it1.current());
			}
		}
	    
		if ((*it).head()->value->_index > index_to_remove) {
			(*it).head()->value->_index = i;
		}
	}

	std::cout << "";
}

template <class T>
int LGraph<T>::find_vertex_index(const T& value) const {
	for (int i = 0; i < _graph.size(); i++) {
		if (_graph[i].head()->value->_value == value) {
			return i;
		}
	}
	throw std::logic_error("The vertex not found");
}

template <class T>
void LGraph<T>::add_edge(const T& first_value, const T& second_value) {
	int first_index = find_vertex_index(first_value);
	int second_index = find_vertex_index(second_value);

	_graph[first_index].push_back(_graph[second_index].head()->value);
	if (!_is_oriented) {
		_graph[second_index].push_back(_graph[first_index].head()->value);
	}

	std::cout << "";
}

template <class T>
void LGraph<T>::delete_edge(const T& first_value, const T& second_value) {
	int first_index = find_vertex_index(first_value);
	int second_index = find_vertex_index(second_value);

	for (auto it = _graph[first_index].begin(); it != _graph[first_index].end(); it++) {

	}
}
*/
