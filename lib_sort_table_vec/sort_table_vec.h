#pragma once
#include "../lib_tvector/tvector.h"
#include "../lib_table/table.h"

template <class TKey, class TValue>
class SortedTableV : public Table<TKey, TValue> {
    TVector<TPair<TKey, TValue>> _rows;
public:
    SortedTableV();
    SortedTableV(TVector<TPair<TKey, TValue>>);
    ~SortedTableV() {}

    void insert(const TKey&, const TValue&) override;
    void erase(const TKey&) override;
    TValue* found(const TKey&) override;
    int found_for_insert(const TKey& key); // private?

    bool is_empty() const noexcept override;
    void print() const noexcept;
    TVector<TPair<TKey, TValue>> rows();
};

template <class TKey, class TValue>
SortedTableV<TKey, TValue>::SortedTableV() : _rows() {}

template <class TKey, class TValue>
SortedTableV<TKey, TValue>::SortedTableV(TVector<TPair<TKey, TValue>> rows)
    : _rows(rows) {}

template <class TKey, class TValue>
void SortedTableV<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    int found_index = found_for_insert(key);

    if (found_index != -1) {
        _rows[found_index].value = value;
    }
    else {
        TPair<TKey, TValue> pair(key, value);
        _rows.push_back(pair);
    }
}

template <class TKey, class TValue>
int SortedTableV<TKey, TValue>::found_for_insert(const TKey& key) {
    int i = 0, j = _rows.size() - 1, c;

    while (i <= j) {
        c = i + j / 2;
        if (_rows[c].key == key) {
            return c;
        }
        else if (_rows[c].key < key) {
            i = c + 1;
        }
        else {
            j = c - 1;
        }
    }
    return -1;
}

template <class TKey, class TValue>
TValue* SortedTableV<TKey, TValue>::found(const TKey& key) {
    int i = 0, j = _rows.size() - 1, c;

    while (i <= j) {
        c = i + j / 2;
        if (_rows[c].key == key) {
            return &_rows[c].value;
        }
        else if (_rows[c].key < key) {
            i = c + 1;
        }
        else {
            j = c - 1;
        }
    }
    return nullptr;
}

template <class TKey, class TValue>
void SortedTableV<TKey, TValue>::erase(const TKey& key) { ////
    int found_index = found_for_insert(key);

    if (found_index != -1) {
        _rows.erase(found_index);
    }
    else {
        throw std::logic_error("Key not found");
    }
}

template <class TKey, class TValue>
bool SortedTableV<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void SortedTableV<TKey, TValue>::print() const noexcept {
    std::cout << "TABLE:" << std::endl;
    for (size_t i = 0; i < _rows.size(); i++) {
        std::cout << "{ " << _rows[i].key << " : " << _rows[i].value << " }" << std::endl;
    }
}

template <class TKey, class TValue>
TVector<TPair<TKey, TValue>> SortedTableV<TKey, TValue>::rows() {
    return _rows;
}