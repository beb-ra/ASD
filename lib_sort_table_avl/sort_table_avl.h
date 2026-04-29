#pragma once
#include "../lib_avltree/avltree.h"
#include "../lib_table/table.h"

template <class TKey, class TValue>
class SortedTableAVL : public Table<TKey, TValue> {
    AVLTree<TKey, TValue> _rows;
public:
    SortedTableAVL();
    SortedTableAVL(AVLTree<TKey, TValue>);
    ~SortedTableAVL() {}

    void insert(const TKey&, const TValue&) override;
    void erase(const TKey&) override;
    TValue* found(const TKey&) override;

    bool is_empty() const noexcept override;
    void print() const noexcept;
    const AVLTree<TKey, TValue>& rows() const noexcept;

    friend std::ostream& operator<<(std::ostream& os, const SortedTableAVL& node) {
        node.rows().print_lcr();
        return os;
    }
};

template <class TKey, class TValue>
SortedTableAVL<TKey, TValue>::SortedTableAVL() : _rows() {}

template <class TKey, class TValue>
SortedTableAVL<TKey, TValue>::SortedTableAVL(AVLTree<TKey, TValue> rows)
    : _rows(rows) {}

template <class TKey, class TValue>
void SortedTableAVL<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    try {
        _rows.insert(key, value);
    }
    catch (const std::exception& e) {
        throw;
    }
}

template <class TKey, class TValue>
TValue* SortedTableAVL<TKey, TValue>::found(const TKey& key) {
    AVLNode<TKey, TValue>* node = _rows.find(key);
    if (node && node->_data.key == key) {
        return &node->_data.value;
    }
    return nullptr;
}

template <class TKey, class TValue>
void SortedTableAVL<TKey, TValue>::erase(const TKey& key) {
    try {
        _rows.erase(key);
    }
    catch (const std::exception& e) {
        throw;
    }
}

template <class TKey, class TValue>
bool SortedTableAVL<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void SortedTableAVL<TKey, TValue>::print() const noexcept {
    std::cout << "TABLE:" << std::endl;
    _rows.print_lcr();
}

template <class TKey, class TValue>
const AVLTree<TKey, TValue>& SortedTableAVL<TKey, TValue>::rows() const noexcept {
    return _rows;
}