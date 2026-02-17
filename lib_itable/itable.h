#pragma once

template <class TKey, class TValue>
class ITable {
public:
	virtual ~ITable() {}
	virtual void insert(const TKey&, const TValue&) = 0;
	virtual void erase(const TKey&) = 0;
	virtual TValue& found(const TKey&) const noexcept = 0;
	virtual bool is_empty() const noexcept = 0;
	virtual friend std::ostream& operator <<(std::ostream& out, const ITable&) = 0;
};