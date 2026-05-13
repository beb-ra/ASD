#pragma once
#include "../lib_rbtree/rbtree.h"
#include "../lib_table/table.h"

template <class TKey, class TValue>
class SortedTableRBT : public Table<TKey, TValue> {
    RBTree<TKey, TValue> _rows;
public:
    SortedTableRBT();
    SortedTableRBT(RBTree<TKey, TValue>);
    ~SortedTableRBT() {}

    void insert(const TKey&, const TValue&) override;
    void erase(const TKey&) override;
    TValue* found(const TKey&) override;

    bool is_empty() const noexcept override;
    void print() const noexcept;
    const RBTree<TKey, TValue>& rows() const noexcept;

    friend std::ostream& operator<<(std::ostream& os, const SortedTableRBT& table) {
        table.rows().print_lcr();
        return os;
    }
};

template <class TKey, class TValue>
SortedTableRBT<TKey, TValue>::SortedTableRBT() : _rows() {}

template <class TKey, class TValue>
SortedTableRBT<TKey, TValue>::SortedTableRBT(RBTree<TKey, TValue> rows)
    : _rows(rows) {}

template <class TKey, class TValue>
void SortedTableRBT<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    try {
        _rows.insert(key, value);
    }
    catch (const std::exception& e) {
        throw;
    }
}

template <class TKey, class TValue>
TValue* SortedTableRBT<TKey, TValue>::found(const TKey& key) {
    RBNode<TKey, TValue>* node = _rows.find(key);
    if (node && node->_data.key == key) {
        return &node->_data.value;
    }
    return nullptr;
}

template <class TKey, class TValue>
void SortedTableRBT<TKey, TValue>::erase(const TKey& key) {
    try {
        _rows.erase(key);
    }
    catch (const std::exception& e) {
        throw;
    }
}

template <class TKey, class TValue>
bool SortedTableRBT<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void SortedTableRBT<TKey, TValue>::print() const noexcept {
    std::cout << "TABLE:" << std::endl;
    _rows.print_lcr();
}

template <class TKey, class TValue>
const RBTree<TKey, TValue>& SortedTableRBT<TKey, TValue>::rows() const noexcept {
    return _rows;
}