#include "../lib_mvector/mvector.h"

template <class T>
class TriangleMatrix : public MVector<MVector<T>> {
	size_t N;
public:
	TriangleMatrix(const MVector<MVector<T>>&);
	TriangleMatrix(const TriangleMatrix<T>&);
	TriangleMatrix(const size_t rows = 2);
	TriangleMatrix(const size_t rows, const std::initializer_list<T> data);
	TriangleMatrix(const size_t rows, const T* data);

	size_t get_n() const noexcept;

	bool operator == (const TriangleMatrix<T>& other) const noexcept;
	bool operator != (const TriangleMatrix<T>& other) const noexcept;

	TriangleMatrix<T> operator+(const TriangleMatrix<T>&) const;
	TriangleMatrix<T>& operator+=(const TriangleMatrix<T>&);
	TriangleMatrix<T> operator-(const TriangleMatrix<T>&) const;
	TriangleMatrix<T>& operator-=(const TriangleMatrix<T>&);

	TriangleMatrix<T> operator*(const TriangleMatrix<T>&) const;
	TriangleMatrix<T>& operator*=(const TriangleMatrix<T>&);
	TriangleMatrix<T> operator*(const T) const;
	TriangleMatrix<T>& operator*=(const T);
	MVector<T> operator*(const MVector<T>&) const;

	friend MVector<T> operator*(const MVector<T>& vector, const TriangleMatrix<T>& matrix) {
		if (matrix.get_n() != vector.size()) {
			throw std::invalid_argument("Operations on matrices of different sizes aren't available");
		}

		MVector<T> result(matrix.get_n());
		for (int i = 0; i < matrix.get_n(); i++) {
			result[i] = T();
			for (int j = 0; j < i + 1; j++) {
				result[i] += vector[j] * matrix[j][i];
			}
		}
		return result;
	}

	friend TriangleMatrix<T> operator* (const T value, const TriangleMatrix<T>& matrix) {
		return matrix * value;
	}

	friend std::ostream& operator<<(std::ostream& os, const TriangleMatrix<T>& matrix) {
		for (size_t i = 0; i < matrix.get_n(); i++) {
			for (size_t j = 0; j < i; j++) {
				os << "0 ";
			}
			for (size_t j = i; j < matrix.get_n(); j++) {
				os << matrix[i][j] << " ";
			}
			os << std::endl;
		}
		return os;
	}

	friend std::istream& operator>>(std::istream& is, TriangleMatrix<T>& matrix) {
		for (size_t i = 0; i < matrix.get_n(); i++) {
			for (size_t j = i; j < matrix.get_n(); j++) {
				is >> matrix[i][j];
			}
		}
		return is;
	}

	void print() const noexcept;
};

template <class T>
TriangleMatrix<T>::TriangleMatrix(const MVector<MVector<T>>& other) : MVector<MVector<T>>(other), N(other.size()) {
	for (size_t i = 0; i < other.size(); i++) {
		(*this)[i] = MVector<T>(i, other.size() - i);
	}
}

template <class T>
TriangleMatrix<T>::TriangleMatrix(const TriangleMatrix<T>& other) : MVector<MVector<T>>(other), N(other.N) {}

template <class T>
TriangleMatrix<T>::TriangleMatrix(const size_t rows) : MVector<MVector<T>>(rows), N(rows) {
	for (size_t i = 0; i < rows; i++) {
		(*this)[i] = MVector<T>(rows - i, i);
	}
}

template <class T>
TriangleMatrix<T>::TriangleMatrix(const size_t rows, const std::initializer_list<T> data) : MVector<MVector<T>>(rows), N(rows) {
	for (size_t i = 0, count = 0; i < rows; i++) {
		(*this)[i] = MVector<T>(rows - i, i);

		for (size_t j = i; j < rows; j++) {
			(*this)[i][j] = *(data.begin() + count);
			count++;
		}
	}
}

template <class T>
TriangleMatrix<T>::TriangleMatrix(const size_t rows, const T* data) : MVector<MVector<T>>(rows), N(rows) {
	for (size_t i = 0, count = 0; i < rows; i++) {
		(*this)[i] = MVector<T>(rows - i, i);

		for (size_t j = i; j < rows; j++) {
			(*this)[i][j] = data[count];
			count++;
		}
	}
}

template <class T>
bool TriangleMatrix<T>::operator == (const TriangleMatrix<T>& other) const noexcept {
	if (N != other.N) return false;

	for (int i = 0; i < N; i++) {
		if ((*this)[i] != other[i])
			return false;
	}
	return true;
}

template <class T>
bool TriangleMatrix<T>::operator != (const TriangleMatrix<T>& other) const noexcept {
	if (N != other.N) return true;

	for (int i = 0; i < N; i++) {
		if ((*this)[i] != other[i])
			return true;
	}
	return false;
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator+(const TriangleMatrix<T>& other) const {
	if (N != other.N) {
		throw std::invalid_argument("Operations on matrices of different sizes aren't available");
	}

	TriangleMatrix<T> result(*this);
	result += other;
	return result;
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator+=(const TriangleMatrix<T>& other) {
	if (N != other.N) {
		throw std::invalid_argument("Operations on matrices of different sizes aren't available");
	}

	for (size_t i = 0; i < N; i++) {
		(*this)[i] += other[i];
	}
	return (*this);
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator-(const TriangleMatrix<T>& other) const {
	if (N != other.N) {
		throw std::invalid_argument("Operations on matrices of different sizes aren't available");
	}

	TriangleMatrix<T> result(*this);
	result -= other;
	return result;
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator-=(const TriangleMatrix<T>& other) {
	if (N != other.N) {
		throw std::invalid_argument("Operations on matrices of different sizes aren't available");
	}

	for (size_t i = 0; i < N; i++) {
		(*this)[i] -= other[i];
	}
	return (*this);
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(const TriangleMatrix<T>& other) const {
	if (N != other.N) {
		throw std::invalid_argument("Operations on matrices of different sizes aren't available");
	}

	TriangleMatrix<T> result(*this);
	result *= other;
	return result;
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator*=(const TriangleMatrix<T>& other) {
	if (N != other.N) {
		throw std::invalid_argument("Operations on matrices of different sizes aren't available");
	}

	TriangleMatrix<T> copy(*this);
	for (int i = 0; i < N; i++) {
		for (int j = i; j < N; j++) {
			T sum = T();
			for (int k = i; k <= j; k++) {
				sum += copy[i][k] * other[k][j];
			}
			(*this)[i][j] = sum;
		}
	}
	return (*this);
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(const T value) const {
	TriangleMatrix<T> result(*this);
	result *= value;
	return result;
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator*=(const T value) {
	for (int i = 0; i < N; i++) {
		(*this)[i] *= value;
	}
	return *this;
}

template <class T>
MVector<T> TriangleMatrix<T>::operator*(const MVector<T>& vector) const {
	if (N != vector.size()) {
		throw std::invalid_argument("Operations on matrices of inappropriate sizes aren't available");
	}
	MVector<T> result(N);
	for (int i = 0; i < N; i++) {
		result[i] = (*this)[i] * vector;
	}
	return result;
}

template <class T>
size_t TriangleMatrix<T>::get_n() const noexcept {
	return N;
}

template <class T>
void TriangleMatrix<T>::print() const noexcept {
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < i; j++) {
			std::cout << T() << " ";
		}
		for (size_t j = i; j < N; j++) {
			std::cout << (*this)[i][j] << " ";
		}
		std::cout << std::endl;
	}
}