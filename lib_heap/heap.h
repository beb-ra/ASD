#pragma once
#include <iostream>
//#include "../lib_tvector/tvector.h"
#include <vector>

template <class T>
class Heap {
    std::vector<T> _data;
public:
    void insert(T);
    void pop();
    void surfacing(int);
    void sinking(int);
    T& get_min();

    int size() const noexcept;
    bool is_empty() const noexcept;
};

template <class T>
void Heap<T>::insert(T elem) {
    _data.push_back(elem);
    surfacing(_data.size() - 1);
}

template <class T>
void Heap<T>::pop() {
    if (_data.empty()) {
        throw std::logic_error("The heap is empty");
    }
    int size = _data.size();
    _data[0] = _data[size - 1];
    _data.pop_back();
    sinking(0);
}

template <class T>
T& Heap<T>::get_min() {
    return _data[0];
}

template <class T>
void Heap<T>::surfacing(int ind) {
    int parent_ind = (ind - 1) / 2;
    while (ind > 0 && _data[parent_ind] > _data[ind]) {
        T temp = _data[ind];
        _data[ind] = _data[parent_ind];
        _data[parent_ind] = temp;

        ind = parent_ind;
        parent_ind = (ind - 1) / 2;
    }
}

template <class T>
void Heap<T>::sinking(int ind) {
    int left_ind, right_ind, small_ind;
    while (true) {
        left_ind = 2 * ind + 1;
        right_ind = 2 * ind + 2;
        small_ind = ind;

        if (left_ind < _data.size() && _data[left_ind] < _data[small_ind]) {
            small_ind = left_ind;
        }
        if (right_ind < _data.size() && _data[right_ind] < _data[small_ind]) {
            small_ind = right_ind;
        }
        if (small_ind == ind) break;

        T temp = _data[ind];
        _data[ind] = _data[small_ind];
        _data[small_ind] = temp;

        ind = small_ind;
    }
}

template <class T>
int Heap<T>::size() const noexcept {
    return _data.size();
}

template <class T>
bool Heap<T>::is_empty() const noexcept {
    return size() == 0;
}