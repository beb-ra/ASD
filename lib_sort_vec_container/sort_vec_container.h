#pragma once
#include <iostream>
#include "../lib_tvector/tvector.h"
#include "../lib_table/table.h"

template <class TKey, class TValue>
struct VecContainerData {
    TPair<TKey, TValue> _data;

    VecContainerData() : _data() {}
    VecContainerData(TKey key, TValue value) : _data(key, value) {}

    ~VecContainerData() {}

    friend std::ostream& operator<<(std::ostream& os, const VecContainerData& node) {
        os << node._data.key << " : " << node._data.value;
        return os;
    }
};

template <class TKey, class TValue>
class SortVecContainer {
    TVector<VecContainerData<TKey, TValue>> _data;
public:
    VecContainerData<TKey, TValue>* find(const TKey& key) noexcept;
    void insert(const TKey& key, const TValue& value);
    void erase(const TKey& key);
    bool is_empty() const noexcept;
    void print() const noexcept;

private:
    int bin_find(const TKey& key) const;
};

template <class TKey, class TValue>
VecContainerData<TKey, TValue>* SortVecContainer<TKey, TValue>::find(const TKey& key) noexcept {
    int pos = bin_find(key);
    if (pos < _data.size() && _data[pos]._data.key == key) 
        return &(_data[pos]);
    return nullptr;
}

template <class TKey, class TValue>
void SortVecContainer<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    int pos = bin_find(key);
    if (pos < _data.size() && _data[pos]._data.key == key) {
        throw std::logic_error("The key already exist");
    }
    else {
        VecContainerData<TKey, TValue> data(key, value);
        _data.insert(pos, data);
    }
}

template <class TKey, class TValue>
void SortVecContainer<TKey, TValue>::erase(const TKey& key) {
    int pos = bin_find(key);

    if (pos < _data.size() && _data[pos]._data.key == key) {
        _data.erase(pos);
    }
    else {
        throw std::logic_error("The key not found");
    }
}

template <class TKey, class TValue>
bool SortVecContainer<TKey, TValue>::is_empty() const noexcept {
    return _data.is_empty();
}

template <class TKey, class TValue>
void SortVecContainer<TKey, TValue>::print() const noexcept {
    _data.print();
}

template <class TKey, class TValue>
int SortVecContainer<TKey, TValue>::bin_find(const TKey& key) const {
    int left = 0, right = _data.size() - 1, mid;

    while (left <= right) {
        mid = (left + right) / 2;
        if (_data[mid]._data.key == key) {
            return mid;
        }
        else if (_data[mid]._data.key < key) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return left;
}
