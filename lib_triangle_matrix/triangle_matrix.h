#include "../lib_matrix/matrix.h"

template <class T>
class TriangleMatrix : public Matrix<T> {
public:
	TriangleMatrix(const MVector<MVector<T>>&);
	TriangleMatrix(const TriangleMatrix<T>&);
	TriangleMatrix(const Matrix<T>& matrix);
	TriangleMatrix(const size_t rows = 2);
	TriangleMatrix(const size_t rows, const std::initializer_list<T> data);
	TriangleMatrix(const size_t rows, const T* data);

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
TriangleMatrix<T>::TriangleMatrix(const MVector<MVector<T>>& other) : Matrix<T>(other) {
	for (size_t i = 0; i < other.size(); i++) {
		(*this)[i] = MVector<T>(i, other.size() - i);
	}
}

template <class T>
TriangleMatrix<T>::TriangleMatrix(const TriangleMatrix<T>& other) : Matrix<T>(other) {}

template <class T>
TriangleMatrix<T>::TriangleMatrix(const Matrix<T>& matrix) : Matrix<T>(matrix) {
	if (this->get_n() != this->get_m()) {
		throw std::invalid_argument("Matrix must be square for triangular form");
	}

	for (size_t i = 0; i < this->get_n(); i++) {
		if ((*this)[i].size() != this->get_n() - i) {
			throw std::invalid_argument("Matrix is not triangular");
		}
	}
}

template <class T>
TriangleMatrix<T>::TriangleMatrix(const size_t rows) : Matrix<T>(rows, rows) {
	for (size_t i = 0; i < rows; i++) {
		(*this)[i] = MVector<T>(rows - i, i);
	}
}

template <class T>
TriangleMatrix<T>::TriangleMatrix(const size_t rows, const std::initializer_list<T> data) : Matrix<T>(rows, rows) {
	for (size_t i = 0, count = 0; i < rows; i++) {
		(*this)[i] = MVector<T>(rows - i, i);

		for (size_t j = i; j < rows; j++) {
			(*this)[i][j] = *(data.begin() + count);
			count++;
		}
	}
}

template <class T>
TriangleMatrix<T>::TriangleMatrix(const size_t rows, const T* data) : Matrix<T>(rows, rows) {
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
	return this->Matrix<T>::operator==(other);
}

template <class T>
bool TriangleMatrix<T>::operator != (const TriangleMatrix<T>& other) const noexcept {
	return !(*this == other);
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator+(const TriangleMatrix<T>& other) const {
	TriangleMatrix<T> result(*this);
	result += other;
	return result;
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator+=(const TriangleMatrix<T>& other) {
	Matrix<T>::operator+=(other);
	return *this;
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator-(const TriangleMatrix<T>& other) const {
	TriangleMatrix<T> result(*this);
	result -= other;
	return result;
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator-=(const TriangleMatrix<T>& other) {
	Matrix<T>::operator-=(other);
	return *this;
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(const TriangleMatrix<T>& other) const {
	TriangleMatrix<T> res(*this);
	res *= other;
	return res;
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator*=(const TriangleMatrix<T>& other) {
	if (get_n() != other.get_n()) {
		throw std::invalid_argument("Operations on matrices of different sizes aren't available");
	}

	TriangleMatrix<T> copy(*this);
	for (int i = 0; i < get_n(); i++) {
		for (int j = i; j < get_n(); j++) {
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
	Matrix<T>::operator*=(value);
	return *this;
}

template <class T>
MVector<T> TriangleMatrix<T>::operator*(const MVector<T>& vector) const {
	/*
	if (N != vector.size()) {
		throw std::invalid_argument("Operations on matrices of inappropriate sizes aren't available");
	}
	MVector<T> result(N);
	for (int i = 0; i < N; i++) {
		result[i] = (*this)[i] * vector;
	}
	return result;
	*/
	return this->Matrix<T>::operator*(vector);
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