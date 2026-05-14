#pragma once
#include <iostream>
#include <algorithm>
#include "../lib_table/table.h"
#include "../lib_tvector/tvector.h"
#include "../lib_list/list.h"

#define SIZE 100
#define EXPANSION_COEFFICIENT 1
#define RESIZE_COEFFICIENT 2

template <class TValue>
struct HashPair {
    std::string key;
    TValue value;

    HashPair() : key("DEFAULT"), value() {}
    HashPair(std::string k, TValue v) : key(k), value(v) {}
};

template <class TValue>
struct HashCData {
    HashPair<TValue> _data;

    HashCData() : _data() {}
    HashCData(std::string key, TValue value) : _data(key, value) {}

    bool operator==(const HashCData& other) const noexcept {
        return _data == other._data;
    }
};

template <class TKey, class TValue>
class HashTableContainerC {
    static_assert(std::is_same_v<TKey, std::string>,
        "HashTableContainerC supports only std::string as key type");

    TVector<List<HashCData<TValue>>> _rows;
    size_t _count;
public:
    HashTableContainerC(size_t size = SIZE) : _rows(size), _count(0) {}

    void insert(const std::string&, const TValue&);
    void erase(const std::string&);
    HashCData<TValue>* find(const std::string&);

    bool is_empty() const noexcept;
    void print() const noexcept;

    size_t count() const noexcept;
    const TVector<List<HashCData<TValue>>> rows() const noexcept;
private:
    size_t h(const std::string&, size_t size) const noexcept;
    void resize_table();
};

template <class TKey, class TValue>
size_t HashTableContainerC<TKey, TValue>::h(const std::string& key, size_t size_) const noexcept {
    size_t hash = 0;
    for (int i = 0; i < key.size(); i++)
        hash += key[i];

    hash %= size_;
    return hash;
}

template <class TKey, class TValue>
void HashTableContainerC<TKey, TValue>::insert(const std::string& key, const TValue& value) {
    size_t hash = h(key, _rows.size());

    HashCData<TValue>* is_find = find(key);

    if (!is_find) {
        HashCData<TValue> h(key, value);
        _rows[hash].push_back(h);
        _count++;
    }
    else {
        throw std::logic_error("The key already exist");
    }

    if (_count > EXPANSION_COEFFICIENT * _rows.size()) {
        resize_table();
    }
}

template <class TKey, class TValue>
void HashTableContainerC<TKey, TValue>::resize_table() {
    size_t new_size = _rows.size() * RESIZE_COEFFICIENT;
    TVector<List<HashCData<TValue>>> new_rows(new_size);
    for (int i = 0; i < _rows.size(); i++) {
        for (auto it = _rows[i].begin(); it != _rows[i].end(); it++) {
            new_rows[h((*it)._data.key, new_size)].push_back(*it);
        }
    }
    _rows = new_rows;
}

template <class TKey, class TValue>
void HashTableContainerC<TKey, TValue>::erase(const std::string& key) {
    size_t hash = h(key, _rows.size());

    if (!_rows[hash].is_empty() && _rows[hash].head()->value._data.key == key) {
        _rows[hash].pop_front();
        _count--;
        return;
    }
    
    for (auto it = _rows[hash].begin(); it != _rows[hash].end(); it++) {
        auto it2 = it;
        it2++;
        if (it2 != _rows[hash].end() && (*it2)._data.key == key) {
            _rows[hash].erase(it.current());
            _count--;
            return;
        }
    }
    throw std::logic_error("The node not found");
}

template <class TKey, class TValue>
HashCData<TValue>* HashTableContainerC<TKey, TValue>::find(const std::string& key) {
    size_t hash = h(key, _rows.size());

    for (auto it = _rows[hash].begin(); it != _rows[hash].end(); it++) {
        if ((*it)._data.key == key) {
            return &(*it);
        }
    }
    return nullptr;
}

template <class TKey, class TValue>
bool HashTableContainerC<TKey, TValue>::is_empty() const noexcept {
    return _count == 0;
}

template <class TKey, class TValue>
void HashTableContainerC<TKey, TValue>::print() const noexcept {
    for (int i = 0; i < _rows.size(); i++) {
        for (auto it = _rows[i].begin(); it != _rows[i].end(); it++) {
            std::cout << (*it)._data.key << " : " << (*it)._data.value << std::endl;
        }
    }
}

template <class TKey, class TValue>
size_t HashTableContainerC<TKey, TValue>::count() const noexcept {
    return _count;
}

template <class TKey, class TValue>
const TVector<List<HashCData<TValue>>> HashTableContainerC<TKey, TValue>::rows() const noexcept {
    return _rows;
}
