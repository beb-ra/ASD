#pragma once

template <class T>
class Queue {
	T* _data;
	size_t _size;
	size_t _head;
	size_t _count;

public:
	Queue(size_t size);
	Queue(const Queue&);
	~Queue();

	void push(const T value);
	void pop();

	inline T head() const;
	inline T tail() const; //head + count
	inline T count() const;
	inline size_t size() const noexcept;

	inline bool is_empty() const noexcept;
	inline bool is_full() const noexcept;

	void clear() noexcept;
};

template <class T>
Queue<T>::Queue(size_t size) {
	_data = new T[size];
	_size = size;
	_head = 0;
	_count = 0;
}

template <class T>
Queue<T>::Queue(const Queue& other) {
	_size = other._size;
	_count = other._count;
	_data = new T[_size];
	_head = 0;

	if (_count > 0) {
		for (size_t i = 0; i < _count; i++) {
			size_t index = (other._head + i) % other._size;
			_data[i] = other._data[index];
		}
	}
}

template <class T>
Queue<T>::~Queue() {
	delete[] _data;
	_data = nullptr;
}

template <class T>
void Queue<T>::push(const T value) {
	if (is_full())
		throw std::logic_error("The queue is full");

	_data[(_head + _count) % _size] = value;
	_count++;
}

template <class T>
void Queue<T>::pop() {
	if (is_empty())
		throw std::logic_error("The queue is full");

	_head = (_head + 1) % _size;
	_count--;
}

template <class T>
inline T Queue<T>::head() const {
	//if (_count == 0) return _head;
	return _data[_head];
}

template <class T>
inline T Queue<T>::tail() const { 
	return _data[(_head + _count - 1) % _size];
}

template <class T>
inline T Queue<T>::count() const { 
	return _count; 
}

template <class T>
inline size_t Queue<T>::size() const noexcept { 
	return _size; 
}

template <class T>
bool Queue<T>::is_empty() const noexcept {
	return _count == 0;
}

template <class T>
bool Queue<T>::is_full() const noexcept {
	return _count == _size;
}

template <class T>
void Queue<T>::clear() noexcept {
	_head = 0;
	_count = 0;
}
