#include "../lib_mvector/mvector.h"

template <class T>
class Matrix : public MVector<MVector<T>> {
	size_t N, M;
public:
	Matrix(const MVector<MVector<T>>&);
	Matrix(const Matrix<T>&);
	Matrix(const size_t rows = 2, const size_t cols = 2);
	Matrix(const size_t rows, const size_t cols, const std::initializer_list<T> data);
	Matrix(const size_t rows, const size_t cols, const T* data);

	size_t get_n() const noexcept;
	size_t get_m() const noexcept;

	Matrix<T> transpose() const;

	bool operator == (const Matrix<T>& other) const noexcept;
	bool operator != (const Matrix<T>& other) const noexcept;
	Matrix<T>& operator =(const Matrix<T>&);

	const T& at(size_t, size_t) const;
	T& at(size_t, size_t);

	Matrix<T> operator+(const Matrix<T>&) const;
	Matrix<T>& operator+=(const Matrix<T>&);
	Matrix<T> operator-(const Matrix<T>&) const;
	Matrix<T>& operator-=(const Matrix<T>&);

	Matrix<T> operator*(const Matrix<T>&) const;
	Matrix<T> operator*(const T) const;
	Matrix<T>& operator*=(const T);
	MVector<T> operator*(const MVector<T>&) const;

	friend MVector<T> operator* (const MVector<T>& vector, const Matrix<T>& matrix) {
		if (matrix.N != vector.size()) {
			throw std::invalid_argument("Operations on matrices of inappropriate sizes aren't available");
		}
		MVector<T> result(matrix.M);
		Matrix<T> tmatrix = matrix.transpose();

		for (int i = 0; i < matrix.M; i++) {
			result[i] = vector * tmatrix[i];
		}
		return result;
	}

	friend Matrix<T> operator* (const T value, const Matrix<T>& matrix) {
		return matrix * value;
	}

	friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
		for (size_t i = 0; i < matrix.get_n(); i++) {
			os << matrix[i];
			if (i < matrix.get_n() - 1)
				os << "\n";
		}
		return os;
	}

	friend std::istream& operator>>(std::istream& is, Matrix<T>& matrix) {
		for (size_t i = 0; i < matrix.get_n(); i++) {
			is >> matrix[i];
		}
		return is;
	}
//private:
	void print() const noexcept;
};

template <class T>
Matrix<T>::Matrix(size_t rows, size_t cols) : MVector<MVector<T>>(rows), 
    N(rows), M(cols) {
	for (size_t i = 0; i < rows; i++) {
		(*this)[i] = MVector<T>(cols);
	}
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& other) : MVector<MVector<T>>(other.N), N(other.N), M(other.M) {
	for (int i = 0; i < N; i++) {
		(*this)[i] = MVector<T>(other[i]);
	}
}

template <class T>
Matrix<T>::Matrix(const MVector<MVector<T>>& other) : MVector<MVector<T>>(other.size()), N(other.size()), M(other[0].size()) {
	for (int i = 0; i < N; i++) {
		(*this)[i] = MVector<T>(other[i]);
	}
}

/*
template <class T>
Matrix<T>::Matrix(const MVector<MVector<T>>& other) : MVector<MVector<T>>(other), 
    N(other.size() - other.start_index()), M(other[0].size()) {}
*/
/*
template <class T>
Matrix<T>::Matrix(const MVector<MVector<T>>& other) : MVector<MVector<T>>(other),
    N(other.size()), M(other[0].size()) {
	for (int i = 0; i < N; i++) {
		(*this)[i] = MVector<T>(other[i]);
	}
}
*/

template <class T>
Matrix<T>::Matrix(const size_t rows, const size_t cols, const std::initializer_list<T> data) 
	: MVector<MVector<T>>(rows), N(rows), M(cols) {
	for (size_t i = 0; i < rows; i++) {
		(*this)[i] = MVector<T>(cols);

		for (size_t j = 0; j < cols; j++) {
			(*this)[i][j] = *(data.begin() + i * cols + j);
		}
	}
}

template <class T>
Matrix<T>::Matrix(const size_t rows, const size_t cols, const T* data)
	: MVector<MVector<T>>(rows), N(rows), M(cols) {
	for (size_t i = 0; i < rows; i++) {
		(*this)[i] = MVector<T>(cols);

		for (size_t j = 0; j < cols; j++) {
			(*this)[i][j] = data[i * cols + j];
		}
	}
}

template <class T>
Matrix<T> Matrix<T>::transpose() const {
	Matrix<T> result(M, N);
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			result[i][j] = (*this)[j][i];
		}
	}

	return result;
}

template <class T>
bool Matrix<T>::operator == (const Matrix<T>& other) const noexcept {
	/*
	if (N != other.N || M != other.M) return false;
	
	for (int i = 0; i < N; i++) {
		if ((*this)[i] != other[i])
			return false;
	}
	return true;
	*/
	if (N != other.N || M != other.M) return false;
	return this->MVector<MVector<T>>::operator==(other);
}


template <class T>
bool Matrix<T>::operator != (const Matrix<T>& other) const noexcept {
	return !((*this) == other);
}

template <class T>
Matrix<T>& Matrix<T>::operator =(const Matrix<T>& other) {
	if (&other == this)
		return *this;
	N = other.N;
	M = other.M;

	this->MVector<MVector<T>>::operator=(other);
	return *this;
}

template <class T>
const T& Matrix<T>::at(size_t rows, size_t cols) const {
	return this->MVector<MVector<T>>::at(rows).at(cols);
}

template <class T>
T& Matrix<T>::at(size_t rows, size_t cols) {
	return this->MVector<MVector<T>>::at(rows).at(cols);
}

template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const {
	if (N != other.N || M != other.M) {
		throw std::invalid_argument("Operations on matrices of different sizes aren't available");
	}

	Matrix<T> result(*this);
	result += other;
	return result;
}

template <class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other) {
	if (N != other.N || M != other.M) {
		throw std::invalid_argument("Operations on matrices of different sizes aren't available");
	}

	this->MVector<MVector<T>>::operator+=(other);
	return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const {
	if (N != other.N || M != other.M) {
		throw std::invalid_argument("Operations on matrices of different sizes aren't available");
	}

	Matrix<T> result(*this);
	result -= other;
	return result;
}

template <class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other) {
	if (N != other.N || M != other.M) {
		throw std::invalid_argument("Operations on matrices of different sizes aren't available");
	}
	
	this->MVector<MVector<T>>::operator-=(other);
	return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const T value) const {
	Matrix<T> result(*this);
	result *= value;
	return result;
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(const T value) {
	for (int i = 0; i < N; i++) {
		(*this)[i] *= value;
	}
	return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {
	if (M != other.N) {
		throw std::invalid_argument("Operations on matrices of inappropriate sizes aren't available");
	}
	Matrix<T> result(N, other.M);
	Matrix<T> tmatrix = other.transpose();

	for (int i = 0; i < this->get_n(); i++) {
		for (int j = 0; j < other.get_m(); j++) {
			result[i][j] = (*this)[i] * tmatrix[j];
		}
	}

	return result;
}

template <class T>
MVector<T> Matrix<T>::operator*(const MVector<T>& vector) const { // vector Mx1
	if (M != vector.size()) {
		throw std::invalid_argument("Operations on matrices of inappropriate sizes aren't available");
	}
	MVector<T> result(N);
	for (int i = 0; i < N; i++) {
		result[i] = (*this)[i] * vector;
	}

	return result;
}

template <class T>
size_t Matrix<T>::get_n() const noexcept {
	return N;
}

template <class T>
size_t Matrix<T>::get_m() const noexcept {
	return M;
}

template <class T>
void Matrix<T>::print() const noexcept {
	std::cout << "Matrix " << N << "x" << M << ":" << std::endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			std::cout << (*this)[i][j] << " ";
		}
		std::cout << std::endl;
	}
}