#pragma once
#include "../lib_tree/tree.h"
#include "../lib_table/table.h"

template <class TKey, class TValue>
class UnsortedTableTree : public Table<TKey, TValue> {
	Tree<TKey, TValue> _rows;
public:
	UnsortedTableTree();
	UnsortedTableTree(Tree<TKey, TValue>);
	~UnsortedTableTree() {}

	void insert(const TKey&, const TValue&) override;
	void erase(const TKey&) override;
	TValue* found(const TKey&) override;

	bool is_empty() const noexcept override;
	void print() const noexcept;
	const Tree<TKey, TValue>& rows() const noexcept;
};

template <class TKey, class TValue>
UnsortedTableTree<TKey, TValue>::UnsortedTableTree() : _rows() {}

template <class TKey, class TValue>
UnsortedTableTree<TKey, TValue>::UnsortedTableTree(Tree<TKey, TValue> rows)
    : _rows(rows) {}

template <class TKey, class TValue>
void UnsortedTableTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    TValue* found_value = found(key);

    if (found_value) {
        throw std::logic_error("This key already exists");
    }
    else {
        _rows.insert(key, value);
    }
}

template <class TKey, class TValue>
TValue* UnsortedTableTree<TKey, TValue>::found(const TKey& key) {
    auto node = _rows.find(key);
    if (node) {
        return &(node->_data.value);
    }
    return nullptr;
}

template <class TKey, class TValue>
void UnsortedTableTree<TKey, TValue>::erase(const TKey& key) {
    try {
        _rows.erase(key);
    }
    catch (const std::exception& e) {
        throw;
    }
}

template <class TKey, class TValue>
bool UnsortedTableTree<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void UnsortedTableTree<TKey, TValue>::print() const noexcept {
    std::cout << "TABLE:\n\n" << std::endl;
    std::cout << _rows;
}

template <class TKey, class TValue>
const Tree<TKey, TValue>& UnsortedTableTree<TKey, TValue>::rows() const noexcept {
    return _rows;
}
