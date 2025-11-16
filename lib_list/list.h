#pragma once

template <class T>
class List {
public:
	struct Node {
		T value;
		Node* next;

		Node(T val, Node* nxt = nullptr) : value(val), next(nxt) {}
	};
protected:
	Node* _head;
	Node* _tail;
	size_t _count;
public:
	List();
	List(const List<T>&);
	~List();

	inline bool is_empty() const noexcept;

	void push_front(const T&) noexcept;
	void push_back(const T&) noexcept;
	void insert(size_t, const T&);
	void insert(Node*, const T&);

	void pop_front();
	void pop_back();
	void erase(size_t);
	void erase(Node*);

	const Node* head() const noexcept { return _head; }
	const Node* tail() const noexcept { return _tail; }
	const size_t size() const noexcept { return _count; }
	Node* head() noexcept { return _head; }
	Node* tail() noexcept { return _tail; }
	size_t size() noexcept { return _count; }

	void print() noexcept;

	class Iterator {
		Node* _current;
	public:
		Iterator() : _current(nullptr) {}
		Iterator(Node* node) : _current(node) {}

		bool operator == (const Iterator& other) const noexcept {
			return this->_current == other._current;
		}
		bool operator != (const Iterator& other) const noexcept {
			return !((*this) == other);
		}

		T& operator*() const {
			return _current->value;
		}

		Iterator& operator=(const Iterator& other) {
			if (this == &other) {
				return *this;
			}
			this->_current = other._current;
			return *this;
		}
		Iterator& operator++() {
			_current = _current->next;
			return *this;
		}
		Iterator operator++(int) {
			Iterator temp = *this;
			++(*this);
			return temp;
		}
		Iterator operator+=(int x) {
			Iterator temp = *this;
			for (int i = 0; i < x; i++) {
				++(*this);
			}
			return temp;
		}

		const Node* current() noexcept {
			return _current;
		}

	};
	Iterator begin() {
		return Iterator(_head);
	}
	Iterator end() {
		return Iterator(nullptr);
	}

	List<T>& operator=(const List<T>& other) {
		if (this != &other) {
			while (!is_empty()) {
				pop_front();
			}

			Node* current = other._head;
			while (current != nullptr) {
				push_back(current->value);
				current = current->next;
			}
		}
		return *this;
	}

	bool operator==(const List<T>& other) const noexcept {
		if (size() != other.size()) {
			return false;
		}

		List<T>::Node* current1 = _head;
		List<T>::Node* current2 = other._head;

		while (current1 != nullptr && current2 != nullptr) {
			if (current1->value != current2->value) {
				return false;
			}
			current1 = current1->next;
			current2 = current2->next;
		}

		return true;
	}

	bool operator!=(const List<T>& other) const noexcept {
		return !(*this == other);
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
	Node* node = other._head;
	
	while (node != nullptr) {
		push_back(node->value);
		node = node->next;
	}
	/*
	for (int i = 0; i < other._count; i++) {
		push_back(node->value);
		node = node->next;
	}
	*/
}

template <class T>
List<T>::~List() {
	while (_head != nullptr) {
		Node* node = _head;
		_head = _head->next;
		delete node;
	}
}

template <class T>
void List<T>::push_front(const T& val) noexcept {
	Node* node = new Node(val, _head);
	if (is_empty()) {
		_tail = node;
	}
	_head = node;
	_count++;
}

template <class T>
void List<T>::push_back(const T& val) noexcept {
	Node* node = new Node(val);
	if (is_empty()) {
		_head = node;
	}
	else {
		_tail->next = node;
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
	Node* cur = _head;
	size_t cur_pos = 0;
	while (cur != nullptr) {
		if (cur_pos == pos - 1) break;
		cur_pos++;
		cur = cur->next;
	}
	if (cur == nullptr) throw std::invalid_argument("The position not found");
	insert(cur, value);
}

template <class T>
void List<T>::insert(Node* node, const T& value) {
	if (is_empty()) throw std::invalid_argument("The list is empty");
	if (node == nullptr) throw std::invalid_argument("The node not found");

	Node* new_node = new Node(value, node->next);
	node->next = new_node;
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
	Node* cur = _head->next;
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
	Node* cur = _head;
	while (cur->next != _tail) {
		cur = cur->next;
	}
	delete _tail;
	_tail = cur;
	cur->next = nullptr;
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
	Node* cur = _head;
	size_t cur_pos = 0;
	while (cur != nullptr) {
		if (cur_pos == pos - 1) break;
		cur_pos++;
		cur = cur->next;
	}
	if (cur == nullptr) throw std::invalid_argument("The position not found");
	erase(cur);
}

template <class T>
void List<T>::erase(Node* node) {
	if (is_empty()) throw std::invalid_argument("The list is empty");
	if (node == nullptr) throw std::invalid_argument("The node not found");
	if (node == _tail) throw std::logic_error("You can't delete a node after the last one");

	Node* cur = node->next->next;
	if (node->next == _tail) {
		_tail = node;
	}
	delete node->next;
	node->next = cur;
	_count--;
}

template <class T>
void List<T>::print() noexcept {
	Node* node = _head;
	std::cout << "values: ";
	for (size_t i = 0; i < _count; i++) {
		std::cout << node->value << " ";
		node = node->next;
	}
	std::cout << "\n";
}
