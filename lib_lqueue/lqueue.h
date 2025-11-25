#pragma once
#include "../lib_list/list.h"

template <class T>
class LQueue {
	List<T> _list;
	int _size;
public:
	LQueue(int size = -1);
	LQueue(const LQueue&);

	void push(const T& value);
	void pop();

	inline T head() const;
	inline T tail() const;
	inline size_t size() const noexcept;

	inline bool is_empty() const noexcept;
	inline bool is_full() const noexcept;

	void clear() noexcept;
};

template <class T>
LQueue<T>::LQueue(int size) : _list(), _size(size) {
	if (size < 0 && size != -1)
		throw std::invalid_argument("Size must be a positive");
}

template <class T>
LQueue<T>::LQueue(const LQueue& other) : _list(other._list), _size(other._size) {}

template <class T>
void LQueue<T>::push(const T& value) {
	if (is_full())
		throw std::logic_error("Queue is full\n");
	_list.push_back(value);
}

template <class T>
void LQueue<T>::pop() {
	if (is_empty())
		throw std::logic_error("Queue is empty\n");
	_list.pop_front();
}

template <class T>
T LQueue<T>::head() const {
	if (is_empty())
		return T();
	return _list.dhead()->value;
}

template <class T>
T LQueue<T>::tail() const {
	if (is_empty())
		return T();
	return _list.dtail()->value;
}

template <class T>
size_t LQueue<T>::size() const noexcept {
	return _size != -1 ? _size : _list.size();
}

template <class T>
bool LQueue<T>::is_empty() const noexcept {
	return _list.is_empty();
}

template <class T>
bool LQueue<T>::is_full() const noexcept {
	return _list.size() == _size;
}

template <class T>
void LQueue<T>::clear() noexcept {
	while (!_list.is_empty()) {
		_list.pop_front();
	}
}