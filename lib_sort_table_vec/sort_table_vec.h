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

    bool is_empty() const noexcept override;
    void print() const noexcept;
    TVector<TPair<TKey, TValue>> rows();
private:
    int bin_find(const TKey& key) const;
};

template <class TKey, class TValue>
SortedTableV<TKey, TValue>::SortedTableV() : _rows() {}

template <class TKey, class TValue>
SortedTableV<TKey, TValue>::SortedTableV(TVector<TPair<TKey, TValue>> rows)
    : _rows(rows) {}

template <class TKey, class TValue>
void SortedTableV<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    int pos = bin_find(key);
    if (pos < _rows.size() && _rows[pos].key == key) {
        _rows[pos].value = value;
    }
    else {
        TPair<TKey, TValue> pair(key, value);
        _rows.insert(pos, pair);
    }
}

template <class TKey, class TValue>
TValue* SortedTableV<TKey, TValue>::found(const TKey& key) {  // проверка на совпадение по ключу в erase и found
    int pos = bin_find(key);
    if (pos < _rows.size() && _rows[pos].key == key) {
        return &_rows[pos].value;
    }
    return nullptr;
}

template <class TKey, class TValue>
void SortedTableV<TKey, TValue>::erase(const TKey& key) {
    int pos = bin_find(key);

    if (pos < _rows.size() && _rows[pos].key == key) {
        _rows.erase(pos);
    }
    else {
        throw std::logic_error("Key not found");
    }
}

template <class TKey, class TValue>
int SortedTableV<TKey, TValue>::bin_find(const TKey& key) const {
    int left = 0, right = _rows.size() - 1, mid;

    while (left <= right) {
        mid = (left + right) / 2;
        if (_rows[mid].key == key) {
            return mid;
        }
        else if (_rows[mid].key < key) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return left;
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