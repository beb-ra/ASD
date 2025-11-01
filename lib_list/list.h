#pragma once
#include "../lib_node/node.h"

template <class T>
class List {
	Node<T>* _head;
	Node<T>* _tail;
	size_t _count;
public:
	List();
	List(const List<T>&);
	~List();

	inline bool is_empty() const noexcept;

	void push_front(const T&) noexcept;
	void push_back(const T&) noexcept;
	void insert(size_t, const T&);
	void insert(Node<T>*, const T&);

	void pop_front();
	void pop_back();
	void erase(size_t);
	void erase(Node<T>*);

	inline const Node<T>* head() const noexcept;
	inline const Node<T>* tail() const noexcept;
	inline const size_t size() const noexcept;
	inline Node<T>* head() noexcept;
	inline Node<T>* tail() noexcept;
	inline size_t size() noexcept;

	void print() noexcept;

	class Iterator {
		Node<T>* _current;
	public:
		Iterator() : _current(nullptr) {}
		Iterator(Node<T>* node) : _current(node) {}

		bool operator == (const Iterator& other) const noexcept {
			return this->_current == other._current;
		}
		bool operator != (const Iterator& other) const noexcept {
			return !((*this) == other);
		}

		T& operator*() const {
			return _current->value();
		}

		Iterator& operator=(const Iterator& other) {
			if (this == &other) {
				return *this;
			}
			this->_current = other._current;
			return *this;
		}
		Iterator& operator++() {
			_current = _current->next();
			return *this;
		}
		Iterator operator++(int) {
			Iterator temp = *this;
			++(*this);
			return temp;
		}

		const Node<T>* current() noexcept {
			return _current;
		}

	};
	Iterator begin() {
		return Iterator(_head);
	}
	Iterator end() {
		return Iterator(nullptr);
	}
};

template <class T>
bool List<T>::is_empty() const noexcept {
	return _head == nullptr;
}

template <class T>
List<T>::List() : _head(nullptr), _tail(nullptr), _count(0) {}

template <class T>
List<T>::List(const List<T>& other) : _head(nullptr), _tail(nullptr), _count(0) {
	Node<T>* node = other._head;
	while (node != nullptr) {
		push_back(node->value());
		node = node->next();
	}
}

template <class T>
List<T>::~List() {
	while (_head != nullptr) {
		Node<T>* node = _head;
		_head = _head->next();
		delete node;
	}
}

template <class T>
void List<T>::push_front(const T& value) noexcept {
	Node<T>* node = new Node<T>(value, _head);
	if (is_empty()) {
		_tail = node;
	}
	_head = node;
	_count++;
}

template <class T>
void List<T>::push_back(const T& value) noexcept {
	Node<T>* node = new Node<T>(value);
	if (is_empty()) {
		_head = node;
	}
	else {
		_tail->set_next(node);
	}
	_tail = node;
	_count++;
}

template <class T>
void List<T>::insert(size_t pos, const T& value) {
	if (is_empty() && pos != 0) throw std::invalid_argument("The list is empty");
	if (pos == 0) {
		push_front(value);
		return;
	}
	else if (pos == _count) {
		push_back(value);
		return;
	}
	Node<T>* cur = _head;
	size_t cur_pos = 0;
	while (cur != nullptr) {
		if (cur_pos == pos - 1) break;
		cur_pos++;
		cur = cur->next();
	}
	if (cur == nullptr) throw std::invalid_argument("The position not found");
	insert(cur, value);
}

template <class T>
void List<T>::insert(Node<T>* node, const T& value) {
	if (is_empty()) throw std::invalid_argument("The list is empty");
	if (node == nullptr) throw std::invalid_argument("The node not found");

	Node<T>* new_node = new Node<T>(value, node->next());
	node->set_next(new_node);
	if (node == _tail) {
		_tail = new_node;
	}
	_count++;
}

template <class T>
void List<T>::pop_front() {
	if (is_empty()) throw std::invalid_argument("The list is empty");
	if (_head == _tail) {
		delete _head;
		_head = nullptr;
		_tail = nullptr;
		_count--;
		return;
	}
	Node<T>* cur = _head->next();
	delete _head;
	_head = cur;
	_count--;
}

template <class T>
void List<T>::pop_back() {
	if (is_empty()) throw std::invalid_argument("The list is empty");
	if (_head == _tail) {
		delete _head;
		_head = nullptr;
		_tail = nullptr;
		_count--;
		return;
	}
	Node<T>* cur = _head;
	while (cur->next() != _tail) {
		cur = cur->next();
	}
	delete _tail;
	_tail = cur;
	cur->set_next(nullptr);
	_count--;
}

template <class T>
void List<T>::erase(size_t pos) {
	if (is_empty()) throw std::invalid_argument("The list is empty");
	if (pos == 0) {
		pop_front();
		return;
	}
	else if (pos == _count) {
		pop_back();
		return;
	}
	Node<T>* cur = _head;
	size_t cur_pos = 0;
	while (cur != nullptr) {
		if (cur_pos == pos - 1) break;
		cur_pos++;
		cur = cur->next();
	}
	if (cur == nullptr) throw std::invalid_argument("The position not found");
	erase(cur);
}

template <class T>
void List<T>::erase(Node<T>* node) {
	if (is_empty()) throw std::invalid_argument("The list is empty");
	if (node == nullptr) throw std::invalid_argument("The node not found");
	if (node == _tail) throw std::logic_error("You can't delete a node after the last one");

	Node<T>* cur = node->next()->next();
	if (node->next() == _tail) {
		_tail = node;
	}
	delete node->next();
	node->set_next(cur);
	_count--;
}

template <class T>
inline const Node<T>* List<T>::head() const noexcept {
	return _head;
}

template <class T>
inline const Node<T>* List<T>::tail() const noexcept {
	return _tail;
}

template <class T>
inline const size_t List<T>::size() const noexcept {
	return _count;
}

template <class T>
inline Node<T>* List<T>::head() noexcept {
	return _head;
}

template <class T>
inline Node<T>* List<T>::tail() noexcept {
	return _tail;
}

template <class T>
inline size_t List<T>::size() noexcept {
	return _count;
}

template <class T>
void List<T>::print() noexcept {
	Node<int>* node = _head;
	std::cout << "values: ";
	for (size_t i = 0; i < _count; i++) {
		std::cout << node->value() << " ";
		node = node->next();
	}
	std::cout << "\n";
}
