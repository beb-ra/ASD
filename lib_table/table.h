#pragma once
#include <iostream>
#include "../lib_itable/itable.h"

template <template <class, class> class Container, class TKey, class TValue>
class Table : public ITable<TKey, TValue> {
    Container<TKey, TValue> _data;
public:
    void insert(const TKey& key, const TValue& value) {
        try {
            _data.insert(key, value);
        }
        catch (const std::exception& e) {
            throw;
        }
    }
    void erase(const TKey& key) {
        try {
            _data.erase(key);
        }
        catch (const std::exception& e) {
            throw;
        }
    }
    TValue* found(const TKey& key) {
        auto node = _data.find(key);
        if (node && node->_data.key == key) {
            return &node->_data.value;
        }
        return nullptr;
    }
    bool is_empty() const noexcept {
        return _data.is_empty();
    }
    void print() const noexcept {
        std::cout << "TABLE:" << std::endl;
        _data.print();
    }

    friend std::ostream& operator <<(std::ostream& out, const Table& table) {
        table.print();
        return out;
    }

    const Container<TKey, TValue>& rows() const noexcept {
        return _data;
    }
};