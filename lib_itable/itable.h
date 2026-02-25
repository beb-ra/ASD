#pragma once

template <class TKey, class TValue>
struct TPair {
	TKey key;
	TValue value;

	TPair() : key(), value() {}
	TPair(TKey k, TValue v) : key(k), value(v) {}

	bool operator==(const TPair& other) const noexcept {
		return key == other.key;
	}
};

template <class TKey, class TValue>
class ITable {
public:
	virtual ~ITable() {}
	virtual void insert(const TKey&, const TValue&) = 0;
	virtual void erase(const TKey&) = 0;
	virtual TValue* found(const TKey&) = 0;
	virtual bool is_empty() const noexcept = 0;
	virtual void print() const noexcept = 0;
};