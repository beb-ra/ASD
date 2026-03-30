#pragma once
#include <iostream>
//#include "../lib_tvector/tvector.h"
#include "../lib_heap/heap.h"

template <class TValue>
struct Pair {
    int priority;
    TValue value;
    int order;

    Pair(int k, TValue v, int o) : priority(k), value(v), order(o) {}

    bool operator<(const Pair& other) const noexcept {
        if (priority == other.priority) {
            return order < other.order;
        }
        return priority < other.priority;
    }
    bool operator>(const Pair& other) const noexcept {
        if (priority == other.priority) {
            return order > other.order;
        }
        return priority > other.priority;
    }
};

template <class TValue>
class PQueue {
    Heap<Pair<TValue>> _data;
public:
    void insert(const Pair<TValue>&);
    void pop();
    Pair<TValue>& top();
};

template <class TValue>
void PQueue<TValue>::insert(const Pair<TValue>& pair) {
    _data.insert(pair);
}

template <class TValue>
void PQueue<TValue>::pop() {
    _data.pop();
}

template <class TValue>
Pair<TValue>& PQueue<TValue>::top() {
    return _data.get_min();
}