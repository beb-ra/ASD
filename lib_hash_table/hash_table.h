#pragma once
#include <iostream>
#include <algorithm>
#include "../lib_table/table.h"
#include "../lib_tvector/tvector.h"

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
    std::string _key;
    TValue _value;

    HashData() : _state(_empty), _key("DEFAULT"), _value() {}
    HashData(std::string key, TValue value) : _state(_empty), _key(key), _value(value) {}

    bool operator==(const HashData& other) const noexcept {
        return _key == other._key;
    }
};

template <class TValue>
class HashTableOA : public Table<std::string, TValue> {
    TVector<HashData<TValue>> _rows;
    size_t _size;
    size_t _shift;
    size_t _count;

public:
    HashTableOA(size_t size = SIZE) : _rows(size), _size(size), _count(0) {
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

    void insert(const std::string&, const TValue&) override;
    void erase(const std::string&) override;
    TValue* found(const std::string&) override;

    bool is_empty() const noexcept override;
    void print() const noexcept;
private:
    size_t h(const std::string&) const noexcept;
    size_t hh(size_t) const noexcept;
};

template <class TValue>
size_t HashTableOA<TValue>::h(const std::string& key) const noexcept {
    size_t  hash = 0;
    for (int i = 0; i < key.size(); i++)
        hash += key[i];

    hash %= _size;
    return hash;
}

template <class TValue>
size_t HashTableOA<TValue>::hh(size_t hash) const noexcept {
    return (hash + _shift) % _size;
}

template <class TValue>
void HashTableOA<TValue>::insert(const std::string& key, const TValue& value) {
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
        else if (_rows[hash]._key == key)
            throw std::logic_error("The key already exist");

        hash = hh(hash);
    }
}

template <class TValue>
void HashTableOA<TValue>::erase(const std::string& key) {
    size_t hash = h(key);
    size_t first_hash = hash;

    while (true) {
        if (_rows[hash]._state == _empty)
            break;

        if (_rows[hash]._state == _busy && _rows[hash]._key == key) {
            _rows[hash]._state = _deleted;
            _count--;
            return;
        }

        if (first_hash == hash)
            break;

        hash = hh(hash);
    }

    throw std::logic_error("The key not found");
}

bool is_prime(size_t first, size_t second) noexcept {
    if (second == 0) return first == 1;
    return is_prime(second, first % second);
}

template <class TValue>
TValue* HashTableOA<TValue>::found(const std::string& key) {
    size_t hash = h(key);
    size_t first_hash = hash;
    while (true) {
        if (_rows[hash]._state == _busy && _rows[hash]._key == key)
            return &(_rows[hash]._value);

        if (first_hash == hash)
            return nullptr;
        hash = hh(hash);
    }
}

template <class TValue>
bool HashTableOA<TValue>::is_empty() const noexcept {
    return _count == 0;
}

template <class TValue>
void HashTableOA<TValue>::print() const noexcept {
    for (int i = 0; i < _size; i++) {
        if (_rows[i]._state == _busy) {
            std::cout << _rows[i]._key << " : " << _rows[i]._value << std::endl;
        }
    }
}
