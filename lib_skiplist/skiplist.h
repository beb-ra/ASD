#pragma once
#include <cstdlib>
#include <ctime>
#include "../lib_list/list.h"
#include <string>

//#define DEBUG

template <class TKey, class TValue>
struct TPair {
	TKey key;
	TValue value;

	TPair() : key(), value() {}
	TPair(TKey k, TValue v) : key(k), value(v) {}

	/*
	bool operator==(const TPair& other) const noexcept {
		return key == other.key;
	}
	*/
};

template <class TKey, class TValue>
struct SNode {
	TPair<TKey, TValue> data;
	SNode** next;
	size_t size;

	SNode(size_t level) : data(), size(level) {
		next = new SNode*[level];
		for (int i = 0; i < level; i++) {
			next[i] = nullptr;
		}
	}

	SNode(TPair<TKey, TValue> dat, size_t level) : data(dat), size(level) {
		next = new SNode*[level];
		for (int i = 0; i < level; i++) {
			next[i] = nullptr;
		}
	}

	SNode(const SNode& other)
		: data(other.data), size(other.size) {
		next = new SNode*[size];
		for (size_t i = 0; i < size; i++) {
			next[i] = other.next[i];
		}
	}
	~SNode() {
		delete[] next;
	}

	//SNode& operator=(const Node&) = delete;
};

template <class TKey, class TValue>
class Skiplist {
	size_t _MAX_LVL;
	size_t _lvl;
	//List<SNode<TKey, TValue>*> _head;
	SNode<TKey, TValue>* _head;

public:
	Skiplist() : _MAX_LVL(15), _lvl(1), _head(nullptr) {
		srand(static_cast<unsigned int>(time(0)));
		_head = new SNode<TKey, TValue>(_MAX_LVL);
		/*
		for (size_t i = 0; i < _MAX_LVL; i++) {
			_head->next[i] = nullptr;
		}
		*/
		//SNode<TKey, TValue>* new_node = new SNode<TKey, TValue>(1);
		//_head.push_back(nullptr);
	}

	~Skiplist() {
		if (_head) {
			SNode<TKey, TValue>* current = _head->next[0];
			while (current != nullptr) {
				SNode<TKey, TValue>* temp = current;
				current = current->next[0];
				delete temp;
			}
			delete _head;
		}
	}

	void insert(const TKey& key, const TValue& value);
	void print() const noexcept;
	size_t flip_coin() const noexcept;
	SNode<TKey, TValue>** find_nearest(const TKey& key) const;
};

template <class TKey, class TValue>
size_t Skiplist<TKey, TValue>::flip_coin() const noexcept {
	size_t lvl = 1;
	while (lvl < _MAX_LVL && (rand() % 2) == 1) {
		lvl++;
	}
	return lvl;
}

template <class TKey, class TValue>
SNode<TKey, TValue>** Skiplist<TKey, TValue>::find_nearest(const TKey& key) const {
	SNode<TKey, TValue>** update = new SNode<TKey, TValue>*[_MAX_LVL];
	for (size_t i = 0; i < _MAX_LVL; i++) {
		update[i] = nullptr;
	}
	SNode<TKey, TValue>* current = _head;
	for (int i = _lvl - 1; i >= 0; i--)
	{
		while (current->next[i] != nullptr &&
			current->next[i]->data.key < key) {
			current = current->next[i];
		}
		update[i] = current;
	}
	return update;
}

template <class TKey, class TValue>
void Skiplist<TKey, TValue>::insert(const TKey& key, const TValue& value) {
	SNode<TKey, TValue>** update = find_nearest(key);
	SNode<TKey, TValue>* current = update[0]->next[0];

	if (current == nullptr || current->data.key != key)
	{
		int new_level = flip_coin();
		if (new_level > _lvl)
		{
			for (int i = _lvl; i < new_level; i++) {
				if (i < _MAX_LVL) {
					update[i] = _head;
				}
			}
			_lvl = new_level;
		}

		TPair<TKey, TValue> pair(key, value);
		SNode<TKey, TValue>* new_node = new SNode<TKey, TValue>(pair, new_level);

		for (int i = 0; i < new_level; i++)
		{
			new_node->next[i] = update[i]->next[i];
			update[i]->next[i] = new_node;
		}
#ifdef DEBUG
		std::cout << "Successfully Inserted key " << key << "\n";
#endif
	}
	else { // обновляем
		current->data.value = value;
#ifdef DEBUG
		std::cout << "Updated key " << key << "\n";
#endif
	}

	delete[] update;
}

template <class TKey, class TValue>
void Skiplist<TKey, TValue>::print() const noexcept {
	List<TKey> keys_zero_lvl;
	std::cout << "+-----------------Skip List-----------------+\n\n";
	for (int i = 0; i < _lvl; i++)
	{
		SNode<TKey, TValue>* node = _head->next[i];
		std::cout << "Level " << i + 1 << ": ";
		while (node != nullptr)
		{
			if (i == 0) {
				keys_zero_lvl.push_back(node->data.key);
			    std::cout << "[" << node->data.key << "]" << "--";
				node = node->next[i];
			}
			else {
				for (auto it = keys_zero_lvl.begin(); it != keys_zero_lvl.end(); it++) {
					if (node != nullptr && node->data.key == (*it)) {
						std::cout << "[" << node->data.key << "]" << "--";
						node = node->next[i];
					}
					else {
						int key_length = std::to_string(*it).length();
						std::cout << "----";
						for (int d = 0; d < key_length; d++) {
							std::cout << "-";
						}
					}
				}
			}
		}
		std::cout << "\n";
	}
	std::cout << "\n+-------------------------------------------+";
}