#pragma once
#include <iostream>
#include "../lib_itable/itable.h"

template <class TKey, class TValue>
class Table : public ITable<TKey, TValue> {
public:
    ~Table() override {}
    
    virtual void insert(const TKey&, const TValue&) = 0;
    virtual void erase(const TKey&) = 0;
    virtual TValue* found(const TKey&) = 0;
    virtual bool is_empty() const noexcept = 0;
    virtual void print() const noexcept = 0;
    
    friend std::ostream& operator <<(std::ostream& out, const Table& table) {
        table.print();
        return out;
    }
};