#pragma once
#include "../lib_list/list.h"

template <class T>
class LStack {
	List<T> _list;
	int _size;
public:
	LStack(int size = -1);
	LStack(const LStack&);
	inline void push(const T& value);
	inline void pop();
	inline T top() const;

	inline size_t size() const noexcept;
	inline size_t capacity() const noexcept;

	bool is_empty() const noexcept;
	bool is_full() const noexcept;

	void clear() noexcept;
};

template <class T>
LStack<T>::LStack(int size) : _list(), _size(size) {
	if (size < 0 && size != -1)
		throw std::invalid_argument("Size must be a positive");
}

template <class T>
LStack<T>::LStack(const LStack& other) : _list(other._list), _size(other._size) {}

template <class T>
void LStack<T>::push(const T& value) {
	if (is_full())
		throw std::logic_error("Stack is full\n");
	_list.push_front(value);
}

template <class T>
void LStack<T>::pop() {
	if (is_empty())
		throw std::logic_error("Stack is empty\n");
	_list.pop_front();
}

template <class T>
T LStack<T>::top() const {
	if (is_empty())
		return T();
	return _list.head()->value;
}

template <class T>
size_t LStack<T>::size() const noexcept {
	return _list.size();
}

template <class T>
size_t LStack<T>::capacity() const noexcept {
	return _size;
}

template <class T>
bool LStack<T>::is_empty() const noexcept {
	return _list.is_empty();
}

template <class T>
bool LStack<T>::is_full() const noexcept {
	return _list.size() == _size;
}

template <class T>
void LStack<T>::clear() noexcept {
	while (!_list.is_empty()) {
		_list.pop_front();
	}
}