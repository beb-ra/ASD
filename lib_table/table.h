#pragma once
#include <iostream>
#include "../lib_itable/itable.h"

template <class TKey, class TValue>
class Table : public ITable<TKey, TValue> {
public:
	~Table() override {}
	void insert(const TKey&, const TValue&) override {}
	void erase(const TKey&) override {}
	TValue* found(const TKey&) override { return nullptr; }
	bool is_empty() const noexcept override { return true; }
	virtual void print() const noexcept {}

	friend std::ostream& operator <<(std::ostream& out, const ITable& table) {
		table.print();
		return out;
	}
};