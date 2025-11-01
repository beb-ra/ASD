#include "../lib_tvector/tvector.h"
/*
template <class T>
class MVector;

template <class T> MVector<T> operator* <T>(const T value, const MVector<T>& other);
template <class T> std::ostream& operator<< <T>(std::ostream& os, const MVector<T>& vector);
template <class T> std::istream& operator>> <T>(std::istream& is, MVector<T>& vector);
*/
template <class T>
class MVector : private TVector<T> {
protected:
	size_t _start_index;

public:
	explicit MVector(size_t size = 0);
	MVector(size_t size, size_t start_index);
	MVector(const size_t size, const T* data, const size_t start_index);
	MVector(const size_t size, const std::initializer_list<T> data, const size_t start_index);
	MVector(const MVector<T>& other);

	const size_t start_index() const noexcept;
	const size_t size() const noexcept;

	bool operator == (const MVector<T>& other) const noexcept;
	bool operator != (const MVector<T>& other) const noexcept;
	bool is_empty() const noexcept;

	MVector<T>& operator=(const MVector<T>& other);
	T& operator[](const int);
	const T& operator[](const int) const;
	const T& at(size_t) const;
	T& at(size_t);

	MVector<T>& operator+=(const MVector<T>& other);
	MVector<T>& operator-=(const MVector<T>& other);
	MVector<T>& operator*=(const T);

	MVector<T> operator+(const MVector<T>&) const;
	MVector<T> operator-(const MVector<T>&) const;
	MVector<T> operator*(const T value) const;
	T operator* (const MVector<T>&) const;

	friend MVector<T> operator* (const T value, const MVector<T>& other) {
		return other * value;
	}

	friend std::ostream& operator<<(std::ostream& os, const MVector<T>& vector) {
		for (size_t i = 0; i < vector.size(); i++) {
			os << vector[i] << " ";
		}
		return os;
	}

	friend std::istream& operator>>(std::istream& is, MVector<T>& vector) {
		for (size_t i = 0; i < vector.size(); i++) {
			is >> vector[i];
		}
		return is;
	}

//private:
	void print() const noexcept;
};

template <class T>
MVector<T>::MVector(size_t size) : TVector<T>(size), _start_index(0) {}

template <class T>
MVector<T>::MVector(size_t size, size_t start_index) : TVector<T>(size), _start_index(start_index) {}

template <class T>
MVector<T>::MVector(const size_t size, const T* data, const size_t start_index) : TVector<T>(size, data), _start_index(start_index) {}

template <class T>
MVector<T>::MVector(const size_t size, const std::initializer_list<T> data, const size_t start_index) : TVector<T>(size, data), _start_index(start_index) {}

/*
template <class T>
MVector<T>::MVector(const MVector<T>& other) : TVector<T>(other.TVector<T>::size()), _start_index(other._start_index) {
	for (size_t i = 0; i < TVector<T>::size(); i++) {
		TVector<T>::operator[](i) = other.TVector<T>::operator[](i);
	}
}
*/

/*
template <class T>
MVector<T>::MVector(const MVector<T>& other) : TVector<T>(other.TVector<T>::size()), _start_index(other._start_index) {
	for (size_t i = 0; i < TVector<T>::size(); i++) {
		_data[i] = other._data[i];
	}
}
*/

template <class T>
MVector<T>::MVector(const MVector<T>& other) : TVector<T>(other), _start_index(other._start_index) {}

template <class T>
const size_t MVector<T>::size() const noexcept {
	return TVector<T>::size() + _start_index;
}

template <class T>
bool MVector<T>::operator == (const MVector<T>& other) const noexcept {
	/*
	if (size() != other.size()) return false;

	return static_cast<const TVector<T>&>(*this).operator==(
		static_cast<const TVector<T>&>(other));
	*/
	if (size() != other.size()) return false;
	size_t min_start_index = (_start_index < other._start_index) ? _start_index : other._start_index;

	for (size_t i = min_start_index; i < size(); i++) {
		if (_data[i] != other._data[i]) {
			return false;
		}
	}
	return true;
}

template <class T>
bool MVector<T>::operator != (const MVector<T>& other) const noexcept {
	return !((*this) == other);
}

template <class T>
bool MVector<T>::is_empty() const noexcept {
	return TVector<T>::size() == 0;
}

template <class T>
MVector<T>& MVector<T>::operator=(const MVector<T>& other) {
	if (this == &other) {
		return *this;
	}
	TVector<T>::operator=(other);
	_start_index = other._start_index;

	return *this;
}

template <class T>
T& MVector<T>::operator[](const int index) {
	static T element = T();
	if (index >= 0 && index < _start_index) return element;
	return TVector<T>::operator[](index - _start_index);
}

template <class T>
const T& MVector<T>::operator[](const int index) const {
	static T element = T();
	if (index >= 0 && index < _start_index) return element;
	return TVector<T>::operator[](index - _start_index);
}

template <class T>
const T& MVector<T>::at(size_t index) const {
	if (index >= size() || index < 0) 
		throw std::invalid_argument("Index out of range");

	if (index >= 0 && index < _start_index) {
		static T element = T();
		return element;
	}
	return TVector<T>::operator[](index - _start_index);
}

template <class T>
T& MVector<T>::at(size_t index) {
	if (index >= size() || index < 0) 
		throw std::invalid_argument("Index out of range");

	if (index >= 0 && index < _start_index) {
		static T element = T();
		return element;
	}
	return TVector<T>::operator[](index - _start_index);
}

template <class T>
MVector<T>& MVector<T>::operator+=(const MVector<T>& other) {
	if (this->is_empty() || other.is_empty())
		throw std::invalid_argument("The math vector is empty");

	if (this->size() != other.size())
		throw std::invalid_argument("Operations on vectors of different sizes aren't available");

	size_t min_start_index = (_start_index < other._start_index) ? _start_index : other._start_index;

	if (min_start_index != _start_index) {
		MVector<T> result(size() - min_start_index, min_start_index);
		for (size_t i = min_start_index; i < size(); i++) {
			result[i] = (*this)[i] + other[i];
		}
		*this = result;
	}
	else {
		for (size_t i = min_start_index; i < size(); i++) {
			(*this)[i] += other[i];
		}
	}
	return *this;
}

template <class T>
MVector<T>& MVector<T>::operator-=(const MVector<T>& other) {
	if (this->is_empty() || other.is_empty())
		throw std::invalid_argument("The math vector is empty");

	if (this->size() != other.size())
		throw std::invalid_argument("Operations on vectors of different sizes aren't available");

	size_t min_start_index = (_start_index < other._start_index) ? _start_index : other._start_index;

	if (min_start_index != _start_index) {
		MVector<T> result(size() - min_start_index, min_start_index);
		for (size_t i = min_start_index; i < size(); i++) {
			result[i] = (*this)[i] - other[i];
		}
		*this = result;
	}
	else {
		for (size_t i = min_start_index; i < size(); i++) {
			(*this)[i] -= other[i];
		}
	}
	return *this;
}

template <class T>
MVector<T>& MVector<T>::operator*=(const T value) {
	if (this->is_empty())
		throw std::invalid_argument("The math vector is empty");

	for (int i = _start_index; i < size(); i++) {
		(*this)[i] *= value;
	}
	return *this;
}

template <class T>
MVector<T> MVector<T>::operator*(const T value) const {
	if (this->is_empty())
		throw std::invalid_argument("The math vector is empty");

	MVector<T> result(*this);
	result *= value;
	return result;
}

template <class T>
T MVector<T>::operator*(const MVector<T>& other) const {
	if (this->is_empty() || other.is_empty())
		throw std::invalid_argument("The math vector is empty");

	if (this->size() != other.size())
		throw std::invalid_argument("Operations on vectors of different sizes aren't available");

	T result = 0;
	size_t max_start_index = (_start_index > other._start_index) ? _start_index : other._start_index;
	for (size_t i = max_start_index; i < size(); i++)
		result += (*this)[i] * other[i];
	return result;
}

template <class T>
MVector<T> MVector<T>::operator+(const MVector<T>& other) const {
	if (this->is_empty() || other.is_empty())
		throw std::invalid_argument("The math vector is empty");

	if (this->size() != other.size())
		throw std::invalid_argument("Operations on vectors of different sizes aren't available");

	MVector<T> result(*this);
	result += other;
	return result;
}

template <class T>
MVector<T> MVector<T>::operator-(const MVector<T>& other) const {
	if (this->is_empty() || other.is_empty())
		throw std::invalid_argument("The math vector is empty");

	if (this->size() != other.size())
		throw std::invalid_argument("Operations on vectors of different sizes aren't available");

	MVector<T> result(*this);
	result -= other;
	return result;
}

template <class T>
const size_t MVector<T>::start_index() const noexcept {
	return _start_index;
}

template <class T>
void MVector<T>::print() const noexcept {
	std::cout << "\nsize: " << size() << std::endl;
	for (int i = 0; i < size(); i++) {
		std::cout << (*this)[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "start_index: " << _start_index << std::endl;
}

/*
template <class T>
MVector<T> operator*(const T value, const MVector<T>& other) {
	return other * value;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const MVector<T>& vector) {
	for (size_t i = 0; i < vector.size(); i++) {
		os << vector[i] << " ";
	}
	return os;
}

template <class T>
std::istream& operator>>(std::istream& is, MVector<T>& vector) {
	for (size_t i = 0; i < vector.size(); i++) {
		is >> vector[i];
	}
	return is;
}
*/