#pragma once
#include <iostream>

class DSU {
	int* _parent;
	int* _rank;
	size_t _size;
public:
	DSU(size_t size);
	~DSU();
	// конструктор копирования

	void unite(int x, int y);
	int find(int x);
	void clear();
private:
	int find_rec(int x);
};