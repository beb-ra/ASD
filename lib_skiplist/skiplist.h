#pragma once
#include <cstdlib>
#include <ctime>
#include "../lib_list/list.h"

template <class T>
struct Node {
	//std::pair<TKey, TValue> _data;
	T key;
	Node** next;
	size_t size;

	Node(T val, size_t level) : key(val), size(level) {
		next = new Node * [size];
		for (int i = 0; i < size; i++) {
			next[i] = nullptr;
		}
	}
	/*
	Node(T val, size_t, level, Node** nxt) : key(val), size(level) {
		next = new Node*[size];
		for (int i = 0; i < size; i++) {
			next[i] = nullptr;
		}
	}
	*/
	Node(const Node& other)
		: key(other.key), size(other.size) {
		next = new Node * [size];
		for (size_t i = 0; i < size; i++) {
			next[i] = other.next[i];
		}
	}
	~Node() {
		//delete[] next;
		for (int i = 0; i < size; i++) {
			delete next[i];
		}
		delete[] next;
	}

	//Node& operator=(const Node&) = delete;
};

template <class T>
class Skiplist {
	size_t _MAX_LVLS;
	size_t _lvls;
	List<Node*> _heads;

	Skiplist() : _MAX_LVLS(5), _lvls(1), _heads() {
		for (size_t i = 0; i < _MAX_LVLS; ++i) {
			_heads.push_back(nullptr);
		}
	}
	Skiplist(size_t MAX, size_t lvl, const List<Node*>& heads)
		: _MAX_LVLS(MAX), _lvls(lvl), _heads(heads) {
	}

	void insert(const T& key);
	void print() const noexcept;
	size_t flip_coin() const noexcept;
	Node* find_nearest(const T& key) const;
};

template <class T>
size_t Skiplist<T>::flip_coin() const noexcept {
	srand(static_cast<unsigned int>(time(0)));
	return rand() % 2;
}

template <class T>
Node<T>* Skiplist<T>::find_nearest(const T& key) const { // Node* ?
}

template <class T>
void Skiplist<T>::insert(const T& key) {

}