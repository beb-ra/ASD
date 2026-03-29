#pragma once
#include "../lib_bstree/bstree.h"
#include "../lib_table/table.h"

template <class TKey, class TValue>
class SortedTableBST : public Table<TKey, TValue> {
    BSTree<TKey, TValue> _rows;
public:
    SortedTableBST();
    SortedTableBST(BSTree<TKey, TValue>);
    ~SortedTableBST() {}

    void insert(const TKey&, const TValue&) override;
    void erase(const TKey&) override;
    TValue* found(const TKey&) override;

    bool is_empty() const noexcept override;
    void print() const noexcept;
    BSTree<TKey, TValue>& rows() noexcept;
};

template <class TKey, class TValue>
SortedTableBST<TKey, TValue>::SortedTableBST() : _rows() {}

template <class TKey, class TValue>
SortedTableBST<TKey, TValue>::SortedTableBST(BSTree<TKey, TValue> rows)
    : _rows(rows) {}

template <class TKey, class TValue>
void SortedTableBST<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    try {
        _rows.insert(key, value);
    }
    catch (const std::exception& e) {
        throw;
    }
}

template <class TKey, class TValue>
TValue* SortedTableBST<TKey, TValue>::found(const TKey& key) {
    TreeNode<TKey, TValue>* node = _rows.find(key);
    if (node && node->_data.key == key) {
        return &node->_data.value;
    }
    return nullptr;
}

template <class TKey, class TValue>
void SortedTableBST<TKey, TValue>::erase(const TKey& key) {
    try {
        _rows.erase(key);
    }
    catch (const std::exception& e) {
        throw;
    }
}

template <class TKey, class TValue>
bool SortedTableBST<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void SortedTableBST<TKey, TValue>::print() const noexcept {
    std::cout << "TABLE:" << std::endl;
    std::cout << _rows;
}

template <class TKey, class TValue>
BSTree<TKey, TValue>& SortedTableBST<TKey, TValue>::rows() noexcept {
    return _rows;
}