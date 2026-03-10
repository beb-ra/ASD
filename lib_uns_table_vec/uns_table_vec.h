#pragma once
#include "../lib_tvector/tvector.h"
#include "../lib_table/table.h"

template <class TKey, class TValue>
class UnsortedTableV : public Table<TKey, TValue> {
	TVector<TPair<TKey, TValue>> _rows;
public:
	UnsortedTableV();
	UnsortedTableV(TVector<TPair<TKey, TValue>>);
	~UnsortedTableV() {}

	void insert(const TKey&, const TValue&) override;
	void erase(const TKey&) override;
	TValue* found(const TKey&) override;

	bool is_empty() const noexcept override;
	void print() const noexcept;
	TVector<TPair<TKey, TValue>> rows();
private:
    int find(const TKey&) const;
};

template <class TKey, class TValue>
UnsortedTableV<TKey, TValue>::UnsortedTableV() : _rows() {}

template <class TKey, class TValue>
UnsortedTableV<TKey, TValue>::UnsortedTableV(TVector<TPair<TKey, TValue>> rows)
    : _rows(rows) {}

template <class TKey, class TValue>
void UnsortedTableV<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    TValue* found_value = found(key);

    if (found_value) {
        *found_value = value;
    }
    else {
        TPair<TKey, TValue> pair(key, value);
        _rows.push_back(pair);
    }
}

template <class TKey, class TValue>
TValue* UnsortedTableV<TKey, TValue>::found(const TKey& key) {
    int pos = find(key);
    if (pos != -1 && _rows[pos].key == key) {
        return &_rows[pos].value;
    }
    return nullptr;
}

template <class TKey, class TValue>
void UnsortedTableV<TKey, TValue>::erase(const TKey& key) {
    int pos = find(key);
    if (pos != -1 && _rows[pos].key == key) {
        _rows.erase(pos);
        return;
    }
    throw std::logic_error("Key not found");
}

template <class TKey, class TValue>
int UnsortedTableV<TKey, TValue>::find(const TKey& key) const {
    for (size_t i = 0; i < _rows.size(); i++) {
        if (_rows[i].key == key) {
            return i;
        }
    }
    return -1;
}

template <class TKey, class TValue>
bool UnsortedTableV<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void UnsortedTableV<TKey, TValue>::print() const noexcept {
    std::cout << "TABLE:" << std::endl;
    for (size_t i = 0; i < _rows.size(); i++) {
        std::cout << "{ " << _rows[i].key << " : " << _rows[i].value << " }" << std::endl;
    }
}

template <class TKey, class TValue>
TVector<TPair<TKey, TValue>> UnsortedTableV<TKey, TValue>::rows() {
    return _rows;
}
