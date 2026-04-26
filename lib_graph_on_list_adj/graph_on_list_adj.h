#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include "../lib_list/list.h"
#include "../lib_matrix/matrix.h"
#include "../lib_priority_queue/pqueue.h"

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

		friend std::ostream& operator<<(std::ostream& os, const Vertex& vertex) {
			os << vertex._value << ": ";
			for (auto it = vertex._edges.begin(); it != vertex._edges.end(); it++) {
				os << (*it).first->_value << " ";
			}
			os << "\n";
			return os;
		}
	};

	bool _is_oriented;
	bool _is_weighted;
	std::vector<Vertex*> _graph;

public:
	LGraph(std::vector<std::pair<T, T>>, bool is_oriented);
	LGraph(std::vector<std::pair<std::pair<T, T>, int>>, 
		bool is_oriented, bool is_weighted);
	~LGraph();
	LGraph(const LGraph&) = delete;
	LGraph& operator=(const LGraph&) = delete;

	void delete_vertex(const T&);
	void add_edge(const T&, const T&, int weight = 0);
	void add_vertex(const T&);
	void delete_edge(const T&, const T&);

	const std::vector<Vertex*> data() const noexcept {
		return _graph;
	}
	List<T> find_min_way(const T& first_vertex, const T& second_vertex);

	friend std::ostream& operator<<(std::ostream& os, const LGraph& graph) {
		for (auto it = graph._graph.begin(); it != graph._graph.end(); it++) {
			os << *(*it);
		}
		return os;
	}
private:
	int find_vertex_index(const T&) const;
};

template <class T>
LGraph<T>::LGraph(std::vector<std::pair<std::pair<T, T>, int>> data, bool is_oriented, 
	bool is_weighted) : _is_oriented(is_oriented), _is_weighted(is_weighted) {
	std::unordered_set<T> set_vertex;
	std::unordered_map<T, Vertex*> temp_index;
	int index = 0;
	for (int i = 0; i < data.size(); i++) {
		if (set_vertex.find(data[i].first.first) == set_vertex.end()) {
			set_vertex.insert(data[i].first.first);
			Vertex* new_vertex = new Vertex(index++, data[i].first.first);
			temp_index.insert({ data[i].first.first, new_vertex });
		}
		if (set_vertex.find(data[i].first.second) == set_vertex.end()) {
			set_vertex.insert(data[i].first.second);
			Vertex* new_vertex = new Vertex(index++, data[i].first.second);
			temp_index.insert({ data[i].first.second, new_vertex });
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

		int weight = (is_weighted) ? data[i].second : 1;
		from_vertex->_edges.push_back({ to_vertex, weight });
		if (!_is_oriented) {
			to_vertex->_edges.push_back({ from_vertex, weight });
		}
	}
}

template<class T>
LGraph<T>::LGraph(std::vector<std::pair<T, T>> data, bool is_oriented) : _is_oriented(is_oriented), _is_weighted(false) {
	std::unordered_set<T> set_vertex;
	std::unordered_map<T, Vertex*> temp_index;
	int index = 0;
	for (int i = 0; i < data.size(); i++) {
		if (set_vertex.find(data[i].first) == set_vertex.end()) {
			set_vertex.insert(data[i].first);
			Vertex* new_vertex = new Vertex(index++, data[i].first);
			temp_index.insert({ data[i].first, new_vertex });
		}
		if (set_vertex.find(data[i].second) == set_vertex.end()) {
			set_vertex.insert(data[i].second);
			Vertex* new_vertex = new Vertex(index++, data[i].second);
			temp_index.insert({ data[i].second, new_vertex });
		}
	}

	_graph.resize(set_vertex.size());

	for (auto it = temp_index.begin(); it != temp_index.end(); it++) {
		_graph[(*it).second->_index] = (*it).second;
	}

	for (int i = 0; i < data.size(); i++) {
		if (data[i].first == data[i].second) {
			throw std::logic_error("The edge must connect two different vertices");
		}
		Vertex* from_vertex = temp_index[data[i].first];
		Vertex* to_vertex = temp_index[data[i].second];

		from_vertex->_edges.push_back({ to_vertex, 1 });
		if (!_is_oriented) {
			to_vertex->_edges.push_back({ from_vertex, 1 });
		}
	}
}

template<class T>
LGraph<T>::~LGraph() {
	for (auto it = _graph.begin(); it != _graph.end(); it++) {
		delete (*it);
		*it = nullptr;
	}
	_graph.clear();
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

	int weight_ = (_is_weighted) ? weight : 1;
	_graph[first_index]->_edges.push_back({ _graph[second_index], weight_ });
	if (!_is_oriented) {
		_graph[second_index]->_edges.push_back({ _graph[first_index], weight_ });
	}
}

template <class T>
void LGraph<T>::add_vertex(const T& new_vertex_value) {
	// была ли такая вершина до этого
	for (auto it = _graph.begin(); it != _graph.end(); it++) {
		if ((*it)->_value == new_vertex_value) {
			throw std::logic_error("The vertex is already exist");
		}
	}
	Vertex* new_vertex = new Vertex(_graph.size(), new_vertex_value);
	_graph.push_back(new_vertex);
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

template <class T>
List<T> LGraph<T>::find_min_way(const T& first_vertex, const T& second_vertex) {
	int first_index = find_vertex_index(first_vertex);
	int second_index = find_vertex_index(second_vertex);

	std::vector<int> vertex_distance(_graph.size(), INT_MAX);
	std::unordered_set<int> viewed_vertex;
	std::vector<int> previous_vertex(_graph.size(), -1);

	PQueue<int> queue;

	vertex_distance[first_index] = 0;
	int count = 0;
	queue.insert(Pair<int>(0, first_index, count++));

	while (!queue.is_empty()) {
		int current_distance = vertex_distance[queue.top().value];

		for (auto it = _graph[queue.top().value]->_edges.begin(); it != _graph[queue.top().value]->_edges.end(); it++) {
			int neighbor_vertex = (*it).first->_index;
			int new_distance = current_distance + (*it).second;

			if (new_distance < vertex_distance[neighbor_vertex]) {
				vertex_distance[neighbor_vertex] = new_distance;
				previous_vertex[neighbor_vertex] = queue.top().value;

				if (viewed_vertex.find(neighbor_vertex) == viewed_vertex.end()) {
					queue.insert(Pair<int>(new_distance, neighbor_vertex, count++));
				}
			}
		}
		viewed_vertex.insert(queue.top().value);
		queue.pop();
	}

	List<T> answer;
	int i = second_index;
	while (i != first_index) {
		answer.push_front(_graph[i]->_value);
		i = previous_vertex[i];
		if (i == -1) throw std::logic_error("The path does not exist");
	}
	answer.push_front(_graph[i]->_value);

	return answer;
}

