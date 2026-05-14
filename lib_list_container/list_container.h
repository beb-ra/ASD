#pragma once
#include <iostream>
#include "../lib_list/list.h"
#include "../lib_table/table.h"

template <class TKey, class TValue>
struct LContainerData {
    TPair<TKey, TValue> _data;

    LContainerData() : _data() {}
    LContainerData(TKey key, TValue value) : _data(key, value) {}

    ~LContainerData() {}

    friend std::ostream& operator<<(std::ostream& os, const LContainerData& node) {
        os << node._data.key << " : " << node._data.value;
        return os;
    }
};

template <class TKey, class TValue>
class ListContainer {
    List<LContainerData<TKey, TValue>> _data;
public:
    LContainerData<TKey, TValue>* find(const TKey& key) noexcept;
    void insert(const TKey& key, const TValue& value);
    void erase(const TKey& key);
    bool is_empty() const noexcept;
    void print() const noexcept;
};

template <class TKey, class TValue>
LContainerData<TKey, TValue>* ListContainer<TKey, TValue>::find(const TKey& key) noexcept {
    for (auto it = _data.begin(); it != _data.end(); it++) {
        if ((*it)._data.key == key) {
            return &(*it);
        }
    }
    return nullptr;
}

template <class TKey, class TValue>
void ListContainer<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    LContainerData<TKey, TValue>* is_find = find(key);
    if (is_find) {
        throw std::logic_error("The key already exist");
    }
    else {
        LContainerData<TKey, TValue> data(key, value);
        _data.push_back(data);
    }
}

template <class TKey, class TValue>
void ListContainer<TKey, TValue>::erase(const TKey& key) {
    auto it1 = _data.begin();
    if (it1 == _data.end()) throw std::logic_error("The list is empty");
    if ((*it1)._data.key == key) {
        _data.pop_front();
        return;
    }
    auto it2 = it1;
    it2++;
    while (it2 != _data.end()) {
        if ((*it2)._data.key == key) {
            _data.erase(it1.current());
            return;
        }
        it1++;
        it2++;
    }
    throw std::logic_error("The key not found");
}

template <class TKey, class TValue>
bool ListContainer<TKey, TValue>::is_empty() const noexcept {
    return _data.is_empty();
}

template <class TKey, class TValue>
void ListContainer<TKey, TValue>::print() const noexcept {
    _data.print();
}
