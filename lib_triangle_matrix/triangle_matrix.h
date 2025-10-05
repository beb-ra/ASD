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

	size_t get_n() const;

	bool operator == (const TriangleMatrix<T>& other) const noexcept;
	bool operator != (const TriangleMatrix<T>& other) const noexcept;

	TriangleMatrix<T> operator+(const TriangleMatrix<T>&) const;
	TriangleMatrix<T>& operator+=(const TriangleMatrix<T>&);
	TriangleMatrix<T> operator-(const TriangleMatrix<T>&) const;
	TriangleMatrix<T>& operator-=(const TriangleMatrix<T>&);

	TriangleMatrix<T> operator*(const TriangleMatrix<T>&) const;
	TriangleMatrix<T> operator*(const T) const;
	TriangleMatrix<T>& operator*=(const T);
	MVector<T> operator*(const MVector<T>&) const;

	friend MVector<T> operator* (const MVector<T>& vector, const TriangleMatrix<T>& matrix) {
		return matrix * vector;
	}
	friend TriangleMatrix<T> operator* (const T value, const TriangleMatrix<T>& matrix) {
		return matrix * value;
	}

	void print() noexcept;
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
	/*
	for (size_t i = 0, count = 0; i < rows; i++) {
		(*this)[i] = MVector<T>(i, rows - i);

		for (size_t j = 0; j < rows - i; j++) {
			(*this)[i][j] = *(data.begin() + count);
			count++;
		}
	}
	*/
	for (size_t i = 0, count = 0; i < rows; i++) {
		(*this)[i] = MVector<T>(rows - i, i);

		for (size_t j = i; j < rows; j++) {
			(*this)[i][j] = *(data.begin() + count);
			std::cout << (*this)[i][j] << " ";
			std::cout << "(" << *(data.begin() + count) << ")" << " ";
			count++;
		}
		std::cout << "\t" << count;
		std::cout << std::endl;
	}
}

template <class T>
TriangleMatrix<T>::TriangleMatrix(const size_t rows, const T* data) : MVector<MVector<T>>(rows), N(rows) {
	/*
	for (size_t i = 0, count = 0; i < rows; i++) {
		(*this)[i] = MVector<T>(i, rows - i);

		for (size_t j = 0; j < rows - i; j++) {
			(*this)[i][j] = data[count];
			count++;
		}
	}
	*/
	for (size_t i = 0, count = 0; i < rows; i++) {
		(*this)[i] = MVector<T>(rows - i, i);

		for (size_t j = i; j < rows; j++) {
			(*this)[i][j] = data[count];
			count++;
		}
	}
}

template <class T>
size_t TriangleMatrix<T>::get_n() const {
	return N;
}

template <class T>
void TriangleMatrix<T>::print() noexcept {
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