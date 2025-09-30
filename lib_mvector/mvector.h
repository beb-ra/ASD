//#include "../lib_tvector/tvector.h"
#include "C://Users/Lelya/cc++/CMake/ASD/lib_tvector/tvector.h"

template <class T> class MVector;
template <class T>
MVector<T> operator+(const MVector<T>&, const MVector<T>&);
template <class T>
MVector<T> operator-(const MVector<T>&, const MVector<T>&);
template <class T>
T operator*(const MVector<T>&, const MVector<T>&);
template <class T>
MVector<T> operator*(const MVector<T>&, const T);
template <class T>
MVector<T> operator*(const T, const MVector<T>&);

template <class T>
class MVector : private TVector<T> {
protected:
	size_t _start_index;

public:
	explicit MVector(size_t size = 0);
	MVector(size_t start_index, size_t size);
	MVector(const size_t size, const T* data, const size_t start_index);
	MVector(const size_t size, const std::initializer_list<T> data, const size_t start_index);
	MVector(const MVector<T>& other);

	const size_t start_index() const noexcept;
	void set_start_index(const size_t);

	const size_t size() const noexcept;
	//const size_t capacity() const noexcept;

	bool operator == (const MVector<T>& other) const noexcept;
	bool operator != (const MVector<T>& other) const noexcept;

	MVector<T>& operator=(const MVector<T>& other);
	T& operator[](const int);
	const T& operator[](const int) const;

	MVector<T>& operator+=(const MVector<T>& other);
	MVector<T>& operator-=(const MVector<T>& other);
	MVector<T>& operator*=(const T);

	friend MVector<T> operator+ <T>(const MVector<T>&, const MVector<T>&);
	friend MVector<T> operator- <T>(const MVector<T>&, const MVector<T>&);
	friend T operator* <T>(const MVector<T>&, const MVector<T>&);
	friend MVector<T> operator* <T>(const MVector<T>& other, const T value);
	friend MVector<T> operator* <T>(const T, const MVector<T>&);
};

template <class T>
MVector<T>::MVector(size_t size) : TVector<T>(size), _start_index(0) {}

template <class T>
MVector<T>::MVector(size_t size, size_t start_index) : TVector<T>(size), _start_index(start_index) {}

template <class T>
MVector<T>::MVector(const size_t size, const T* data, const size_t start_index) : TVector<T>(size, data), _start_index(start_index) {}

template <class T>
MVector<T>::MVector(const size_t size, const std::initializer_list<T> data, const size_t start_index) : TVector<T>(size, data), _start_index(start_index) {}

template <class T>
MVector<T>::MVector(const MVector<T>& other) : TVector<T>(other), _start_index(other._start_index) {}

template <class T>
const size_t MVector<T>::size() const noexcept {
	return TVector<T>::size();
}
/*
template <class T>
const size_t MVector<T>::capacity() const noexcept {
	return TVector<T>::capacity();
}
*/

template <class T>
bool MVector<T>::operator == (const MVector<T>& other) const noexcept {
	if (!static_cast<const TVector<T>&>(*this).operator==(static_cast<const TVector<T>&>(other))) {
		return false;
	}
	
	return _start_index == other._start_index;
}

template <class T>
bool MVector<T>::operator != (const MVector<T>& other) const noexcept {
	if (static_cast<const TVector<T>&>(*this).operator!=(static_cast<const TVector<T>&>(other))) {
		return true;
	}

	return _start_index != other._start_index;
}

template <class T>
MVector<T>& MVector<T>::operator=(const MVector<T>& other) {
	if (this == &other) {
		return *this;
	}
	(*this).TVector<T>::operator=(other);
	_start_index = other._start_index;
}

template <class T>
T& MVector<T>::operator[](const int index) {
	return (*this).TVector<T>::operator[](index);
}

template <class T>
const T& MVector<T>::operator[](const int index) const {
	return (*this).TVector<T>::operator[](index);
}

template <class T>
MVector<T>& MVector<T>::operator+=(const MVector<T>& other) {
	if (is_empty() || other.is_empty())
		throw std::invalid_argument("The math vector is empty");

	if (size() != other.size())
		throw std::invalid_argument("Operations on vectors of different sizes aren't available");

	for (int i = 0; i < size(); i++) {
		(*this)[i] += other[i];
	}
	return *this;
}

template <class T>
MVector<T>& MVector<T>::operator-=(const MVector<T>& other) {
	if (is_empty() || other.is_empty())
		throw std::invalid_argument("The math vector is empty");

	if (size() != other.size())
		throw std::invalid_argument("Operations on vectors of different sizes aren't available");

	for (int i = 0; i < size(); i++) {
		(*this)[i] -= other[i];
	}
	return *this;
}

template <class T>
MVector<T>& MVector<T>::operator*=(const T value) {
	if (is_empty())
		throw std::invalid_argument("The math vector is empty");

	for (int i = 0; i < size(); i++) {
		(*this)[i] *= value;
	}
	return *this;
}

template <class T>
MVector<T> operator*(const MVector<T>& other, const T value) {
	if (other.is_empty())
		throw std::invalid_argument("The math vector is empty");

	MVector<T> result(other);
	result *= value;
	return result;
}

template <class T>
MVector<T> operator*(const T value, const MVector<T>& other) {
	if (other.is_empty())
		throw std::invalid_argument("The math vector is empty");

	MVector<T> result(other);
	result *= value;
	return result;
}

template <class T>
T operator*(const MVector<T>& first, const MVector<T>& second) {
	if (first.is_empty() || second.is_empty())
		throw std::invalid_argument("The math vector is empty");

	if (first.size() != second.size())
		throw std::invalid_argument("Operations on vectors of different sizes aren't available");

	T result = T();
	for (int i = 0; i < first.size(); i++) {
		result += first[i] * second[i];
	}
	return result;
}

template <class T>
MVector<T> operator+(const MVector<T>& first, const MVector<T>& second) {
	if (first.is_empty() || second.is_empty())
		throw std::invalid_argument("The math vector is empty");

	if (first.size() != second.size())
		throw std::invalid_argument("Operations on vectors of different sizes aren't available");

	MVector<T> result(first);
	result += second;
	return result;
}

template <class T>
MVector<T> operator-(const MVector<T>& first, const MVector<T>& second) {
	if (first.is_empty() || second.is_empty())
		throw std::invalid_argument("The math vector is empty");

	if (first.size() != second.size())
		throw std::invalid_argument("Operations on vectors of different sizes aren't available");

	MVector<T> result(first);
	result -= second;
	return result;
}

template <class T>
const size_t MVector<T>::start_index() const noexcept {
	return _start_index;
}

template <class T>
void MVector<T>::set_start_index(const size_t index) {
	_start_index = index;
}