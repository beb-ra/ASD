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
class UnsortVecContainer {
    TVector<VecContainerData<TKey, TValue>> _data;
public:
    VecContainerData<TKey, TValue>* find(const TKey& key) noexcept;
    void insert(const TKey& key, const TValue& value);
    void erase(const TKey& key);
    bool is_empty() const noexcept;
    void print() const noexcept;
private:
    int find_index(const TKey&) const;
};

template <class TKey, class TValue>
VecContainerData<TKey, TValue>* UnsortVecContainer<TKey, TValue>::find(const TKey& key) noexcept {
    for (auto it = _data.begin(); it != _data.end(); it++) {
        if ((*it)._data.key == key) {
            return &(*it);
        }
    }
    return nullptr;
}

template <class TKey, class TValue>
void UnsortVecContainer<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    VecContainerData<TKey, TValue>* is_find = find(key);
    if (is_find) {
        throw std::logic_error("The key already exist");
    }
    else {
        VecContainerData<TKey, TValue> data(key, value);
        _data.push_back(data);
    }
}

template <class TKey, class TValue>
void UnsortVecContainer<TKey, TValue>::erase(const TKey& key) {
    int pos = find_index(key);

    if (pos < _data.size() && _data[pos]._data.key == key) {
        _data.erase(pos);
    }
    else {
        throw std::logic_error("The key not found");
    }
}

template <class TKey, class TValue>
int UnsortVecContainer<TKey, TValue>::find_index(const TKey& key) const {
    for (size_t i = 0; i < _data.size(); i++) {
        if (_data[i]._data.key == key) {
            return i;
        }
    }
    return -1;
}

template <class TKey, class TValue>
bool UnsortVecContainer<TKey, TValue>::is_empty() const noexcept {
    return _data.is_empty();
}

template <class TKey, class TValue>
void UnsortVecContainer<TKey, TValue>::print() const noexcept {
    _data.print();
}
