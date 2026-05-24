#pragma once

template <class T>
class Stack {
	T* _data;
	size_t _size;
	int _top;
public:
	Stack(size_t size);
	Stack(const Stack&);
	~Stack();

	inline void push(const T value);
	inline void pop();
	inline T top() const;

	inline size_t size() const noexcept;
	
	bool is_empty() const noexcept;
	bool is_full() const noexcept;

	void clear() noexcept;
};

template <class T>
Stack<T>::Stack(size_t size) {
	_data = new T[size];
	_size = size;
	_top = -1;
}

template <class T>
Stack<T>::Stack(const Stack& other) {
	_size = other._size;
	_data = new T[_size];
	_top = other._top;

	if (_top >= 0) {
		for (size_t i = 0; i <= other._top; i++) {
			_data[i] = other._data[i];
		}
	}
}

template <class T>
Stack<T>::~Stack() {
	delete[] _data;
	_data = nullptr;
}

template <class T>
void Stack<T>::push(const T value) {
	if (is_full())
		throw std::logic_error("Stack is full\n");
	_top++;
	_data[_top] = value;
}

template <class T>
void Stack<T>::pop() {
	if (is_empty())
		throw std::logic_error("Stack is empty\n");
	_top--;
}

template <class T>
T Stack<T>::top() const {
	if (_top == -1) 
		return -1;
	return _data[_top];
}

template <class T>
size_t Stack<T>::size() const noexcept {
	return _size;
}

template <class T>
bool Stack<T>::is_empty() const noexcept {
	if (_top == -1)
		return true;
	return false;
}

template <class T>
bool Stack<T>::is_full() const noexcept {
	if (_top == _size - 1) 
		return true;
	return false;
}

template <class T>
void Stack<T>::clear() noexcept {
	_top = -1;
}