#pragma once
#include "../lib_list/list.h"
#include "../lib_table/table.h"

template <class TKey, class TValue>
class UnsortedTableList : public Table<TKey, TValue> {
	List<TPair<TKey, TValue>> _rows;
public:
	UnsortedTableList();
	UnsortedTableList(List<TPair<TKey, TValue>>);
	~UnsortedTableList() {}

	void insert(const TKey&, const TValue&) override;
	void erase(const TKey&) override;
	TValue* found(const TKey&) override;

	bool is_empty() const noexcept override;
	void print() const noexcept;
	List<TPair<TKey, TValue>> rows();
};

template <class TKey, class TValue>
UnsortedTableList<TKey, TValue>::UnsortedTableList() : _rows() {}

template <class TKey, class TValue>
UnsortedTableList<TKey, TValue>::UnsortedTableList(List<TPair<TKey, TValue>> rows) 
	: _rows(rows) {}

template <class TKey, class TValue>
void UnsortedTableList<TKey, TValue>::insert(const TKey& key, const TValue& value) {
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
TValue* UnsortedTableList<TKey, TValue>::found(const TKey& key) {
	for (auto it = _rows.begin(); it != _rows.end(); it++) {
		if ((*it).key == key) {
			return &(*it).value;
		}
	}
	return nullptr;
}

template <class TKey, class TValue>
void UnsortedTableList<TKey, TValue>::erase(const TKey& key) {
	List<TPair<TKey, TValue>>::Iterator prev = nullptr;
	auto curr = _rows.begin();

	while (curr != _rows.end()) {
		if ((*curr).key == key) {
			if (prev != nullptr) {
				_rows.erase(prev.current());
			}
			else {
				_rows.pop_front();
			}
			return;
		}
		prev = curr;
		curr++;
	}

	throw std::logic_error("Key not found");
}

template <class TKey, class TValue>
bool UnsortedTableList<TKey, TValue>::is_empty() const noexcept {
	return _rows.is_empty();
}

template <class TKey, class TValue>
void UnsortedTableList<TKey, TValue>::print() const noexcept {
	std::cout << "TABLE:" << std::endl;
	for (auto it = _rows.begin(); it != _rows.end(); it++) {
		std::cout << "{ " << (*it).key << " : " << (*it).value << " }" << std::endl;
	}
}

template <class TKey, class TValue>
List<TPair<TKey, TValue>> UnsortedTableList<TKey, TValue>::rows() {
	return _rows;
}