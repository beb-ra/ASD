//#include "../lib_tvector/tvector.h"
#include "C://Users/Lelya/cc++/CMake/ASD/lib_tvector/tvector.h"

template <class T>
class MVector : private TVector<T> {
	size_t _start_index;

public:
	MVector(const size_t size, const T* data, const size_t start_index);
	MVector(const size_t size, const std::initializer_list<T> data, const size_t start_index);
	MVector(const MVector<T>& other);

	MVector<T>& operator+=(const MVector<T>& other);
	MVector<T>& operator-=(const MVector<T>& other);
	MVector<T>& operator*=(const T);

	friend MVector<T> operator+(const MVector<T>&, const MVector<T>&);
	friend MVector<T> operator-(const MVector<T>&, const MVector<T>&);
	friend T operator*(const MVector<T>&, const MVector<T>&);
	friend MVector<T> operator*(const MVector<T>&, const T);
	friend MVector<T> operator*(const T, const MVector<T>&);
};

template <class T>
MVector<T>::MVector(const size_t size, const T* data, const size_t start_index) : TVector<T>(size, data), _start_index(start_index) {}

template <class T>
MVector<T>::MVector(const size_t size, const std::initializer_list<T> data, const size_t start_index) : TVector<T>(size, data), _start_index(start_index) {}

