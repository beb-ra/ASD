#pragma once
#include <iostream>

class DSU {
	int* _parent;
	int* _rank;
	size_t _size;
public:
	DSU(size_t size);
	~DSU();

	void dsu_union(int x, int y);
	int find(int x);
private:
	int find_rec(int x);
};