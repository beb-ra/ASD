#pragma once
#include <iostream>
#include <algorithm>
#include "../lib_table/table.h"
#include "../lib_tvector/tvector.h"
#include "../lib_hash_pair/hash_pair.h"

#define SIZE 100
//#define SHIFT 7

enum status {
    _busy,
    _empty,
    _deleted
};

bool is_prime(size_t, size_t) noexcept;

template <class TValue>
struct HashData {
    status _state;
    HashPair<TValue> _data;

    HashData() : _state(_empty), _data() {}
    HashData(std::string key, TValue value) : _state(_empty), _data(key, value) {}

    bool operator==(const HashData& other) const noexcept {
        return _data == other._data;
    }
};

template <class TKey, class TValue>
class HashTableContainerOA {
    static_assert(std::is_same_v<TKey, std::string>,
        "HashTableContainerC supports only std::string as key type");

    TVector<HashData<TValue>> _rows;
    size_t _size;
    size_t _shift;
    size_t _count;

public:
    HashTableContainerOA(size_t size = SIZE) : _rows(size), _size(size), _count(0) {
        _rows.shrink_to_fit();
        for (size_t i = std::max((size_t)2, size / 15); i < size; i++) {
            if (is_prime(i, size)) {
                _shift = i;
                return;
            }
        }
    }
    bool is_full() const noexcept {
        return _count == _size;
    }

    void insert(const std::string&, const TValue&);
    void erase(const std::string&);
    HashData<TValue>* find(const std::string&);

    bool is_empty() const noexcept;
    void print() const noexcept;
private:
    size_t h(const std::string&) const noexcept;
    size_t hh(size_t) const noexcept;
};

template <class TKey, class TValue>
size_t HashTableContainerOA<TKey, TValue>::h(const std::string& key) const noexcept {
    size_t  hash = 0;
    for (int i = 0; i < key.size(); i++)
        hash += key[i];

    hash %= _size;
    return hash;
}

template <class TKey, class TValue>
size_t HashTableContainerOA<TKey, TValue>::hh(size_t hash) const noexcept {
    return (hash + _shift) % _size;
}

template <class TKey, class TValue>
void HashTableContainerOA<TKey, TValue>::insert(const std::string& key, const TValue& value) {
    if (is_full())
        throw std::logic_error("The table is full");

    size_t hash = h(key);

    while (true) {
        if (_rows[hash]._state != _busy) {
            _rows[hash] = HashData<TValue>(key, value);  // busy default
            _count++;
            _rows[hash]._state = _busy;
            return;
        }
        else if (_rows[hash]._data.key == key)
            throw std::logic_error("The key already exist");

        hash = hh(hash);
    }
}

template <class TKey, class TValue>
void HashTableContainerOA<TKey, TValue>::erase(const std::string& key) {
    size_t hash = h(key);
    size_t first_hash = hash;

    auto _state_ = _rows[hash]._state;
    auto _key_ = _rows[hash]._data.key;

    while (true) {
        if (_rows[hash]._state == _empty)
            break;

        if (_rows[hash]._state == _busy && _rows[hash]._data.key == key) {
            _rows[hash]._state = _deleted;
            _count--;
            return;
        }

        hash = hh(hash);

        if (first_hash == hash)
            break;
    }

    throw std::logic_error("The key not found");
}

bool is_prime(size_t first, size_t second) noexcept {
    if (second == 0) return first == 1;
    return is_prime(second, first % second);
}

template <class TKey, class TValue>
HashData<TValue>* HashTableContainerOA<TKey, TValue>::find(const std::string& key) {
    size_t hash = h(key);
    size_t first_hash = hash;
    while (true) {
        if (_rows[hash]._state == _busy && _rows[hash]._data.key == key)
            return &(_rows[hash]);

        if (first_hash == hash)
            return nullptr;
        hash = hh(hash);
    }
}

template <class TKey, class TValue>
bool HashTableContainerOA<TKey, TValue>::is_empty() const noexcept {
    return _count == 0;
}

template <class TKey, class TValue>
void HashTableContainerOA<TKey, TValue>::print() const noexcept {
    for (int i = 0; i < _size; i++) {
        if (_rows[i]._state == _busy) {
            std::cout << _rows[i]._data.key << " : " << _rows[i]._data.value << std::endl;
        }
    }
}
