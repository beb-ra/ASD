#pragma once
#include <iostream>
#include <algorithm>
#include "../lib_table/table.h"
#include "../lib_tvector/tvector.h"
#include "../lib_list/list.h"

#define SIZE 100

template <class TValue>
struct HashCData {
    std::string _key;
    TValue _value;

    HashCData() : _key("DEFAULT"), _value() {}
    HashCData(std::string key, TValue value) :_key(key), _value(value) {}

    bool operator==(const HashCData& other) const noexcept {
        return _key == other._key;
    }
};

template <class TValue>
class HashTableC : public Table<std::string, TValue> {
    TVector<List<HashCData<TValue>>> _rows;

public:
    HashTableC(size_t size = SIZE) : _rows(size) {}

    void insert(const std::string&, const TValue&) override;
    void erase(const std::string&) override;
    TValue* found(const std::string&) override;

    bool is_empty() const noexcept override;
    void print() const noexcept;
private:
    size_t h(const std::string&) const noexcept;
};

template <class TValue>
size_t HashTableC<TValue>::h(const std::string& key) const noexcept {
    size_t hash = 0;
    for (int i = 0; i < key.size(); i++)
        hash += key[i];

    hash %= _rows.size();
    return hash;
}

template <class TValue>
void HashTableC<TValue>::insert(const std::string& key, const TValue& value) {
    size_t hash = h(key);

    TValue* is_find = found(key);

    if (!is_find) {
        HashCData<TValue> h(key, value);
        _rows[hash].push_back(h);
    }
    else {
        throw std::logic_error("The key already exist");
    }
}

template <class TValue>
void HashTableC<TValue>::erase(const std::string& key) {
    size_t hash = h(key);
    
    for (auto it = _rows[hash].begin(); it != _rows[hash].end(); it++) {
        auto it2 = it;
        it2++;
        if ((*it2)._key == key) {
            _rows[hash].erase(it.current());
            return;
        }
    }
    throw std::logic_error("The node not found");
}

template <class TValue>
TValue* HashTableC<TValue>::found(const std::string& key) {
    size_t hash = h(key);

    for (auto it = _rows[hash].begin(); it != _rows[hash].end(); it++) {
        if (it != nullptr && (*it)._key == key) {
            return &((*it)._value);
        }
    }
    return nullptr;
}

template <class TValue>
bool HashTableC<TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TValue>
void HashTableC<TValue>::print() const noexcept {
    for (int i = 0; i < _rows.size(); i++) {
        for (auto it = _rows[i].begin(); it != _rows[i].end(); it++) {
            std::cout << (*it)._key << " : " << (*it)._value << std::endl;
        }
    }
}
