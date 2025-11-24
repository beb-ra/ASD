#pragma once
//#include "../lib_list/list.h"
#include <iostream>

template <class T>
class DList {
public:
    struct DNode {
        T value;
        DNode* next;
        DNode* prev;

        DNode(T val, DNode* nxt = nullptr, DNode* prv = nullptr)
            : value(val), next(nxt), prev(prv) {}
    };

private:
    DNode* _head;
    DNode* _tail;
    size_t _count;

public:
    DList() : _head(nullptr), _tail(nullptr), _count(0) {}
    DList(std::initializer_list<T> init);
    DList(const DList<T>& other);
    ~DList();

    inline bool is_empty() const noexcept;
    DNode* dhead() noexcept { return _head; }
    DNode* dtail() noexcept { return _tail; }
    const DNode* dhead() const noexcept { return _head; }
    const DNode* dtail() const noexcept { return _tail; }
    const size_t size() const noexcept { return _count; }

    void push_front(const T& val) noexcept;
    void push_back(const T& val) noexcept;
    void insert(size_t pos, const T& value);
    void insert(DNode* node, const T& value);
    void pop_front();
    void pop_back();
    void erase(size_t pos);
    void erase(DNode* node);

    class Iterator {
        DNode* _current;
    public:
        Iterator() : _current(nullptr) {}
        Iterator(DNode* node) : _current(node) {}

        bool operator == (const Iterator& other) const noexcept {
            return this->_current == other._current;
        }
        bool operator != (const Iterator& other) const noexcept {
            return !((*this) == other);
        }

        T& operator*() const {
            if (_current == nullptr)
                throw std::logic_error("Node was nullptr");
            return _current->value;
        }

        Iterator& operator=(const Iterator& other) {
            if (this == &other) {
                return *this;
            }
            this->_current = other._current;
            return *this;
        }
        Iterator& operator++() {
            if (_current == nullptr) 
                throw std::logic_error("Node was nullptr");
            _current = _current->next;
            return *this;
        }
        Iterator& operator--() {
            if (_current == nullptr)
                throw std::logic_error("Node was nullptr");
            _current = _current->prev;
            return *this;
        }
        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }
        Iterator operator--(int) {
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        const DNode* current() noexcept {
            return _current;
        }

    };
    Iterator begin() {
        return Iterator(_head);
    }
    Iterator end() {
        return Iterator(nullptr);
    }
    Iterator rbegin() {
        return Iterator(_tail);
    }
    Iterator rend() {
        return Iterator(nullptr);
    }

    DList<T>& operator=(const DList<T>& other);
    bool operator==(const DList<T>& other) const noexcept;
    bool operator!=(const DList<T>& other) const noexcept;

private:
    void print() noexcept;
};

template <class T>
DList<T>::DList(const DList<T>& other) : _head(nullptr), _tail(nullptr), _count(0) {
    DNode* node = other._head;
    while (node != nullptr) {
        push_back(node->value);
        node = node->next;
    }
}

template <class T>
DList<T>::DList(std::initializer_list<T> init) : _head(nullptr), _tail(nullptr), _count(0) {
    for (auto it = init.begin(); it != init.end(); it++) {
        push_back(*it);
    }
}

template <class T>
DList<T>::~DList() {
    while (_head != nullptr) {
        DNode* node = _head;
        _head = _head->next;
        delete node;
    }
}

template <class T>
void DList<T>::push_front(const T& val) noexcept {
    DNode* new_node = new DNode(val, _head, nullptr);
    if (is_empty()) {
        _tail = new_node;
    }
    else {
        _head->prev = new_node;
    }
    _head = new_node;
    _count++;
}

template <class T>
void DList<T>::push_back(const T& val) noexcept {
    DNode* new_node = new DNode(val, nullptr, _tail);
    if (is_empty()) {
        _head = new_node;
    }
    else {
        _tail->next = new_node;
    }
    _tail = new_node;
    _count++;
}

template <class T>
void DList<T>::insert(size_t pos, const T& value) { // вставляет по позиции
    if (is_empty() && pos != 0) throw std::invalid_argument("The list is empty");
    if (pos > _count) throw std::invalid_argument("Position out of range");
    if (pos == 0) {
        push_front(value);
        return;
    }
    else if (pos == _count) {
        push_back(value);
        return;
    }

    DNode* cur = _head;
    size_t cur_pos = 0;
    while (cur != nullptr) {
        if (cur_pos == pos - 1) break;
        cur_pos++;
        cur = cur->next;
    }
    if (cur == nullptr) throw std::invalid_argument("The position not found");
    insert(cur, value);
}

template <class T>
void DList<T>::insert(DNode* node, const T& value) { // вставка после переданной ноды
    if (is_empty()) throw std::invalid_argument("The list is empty");
    if (node == nullptr) throw std::invalid_argument("The node not found");

    DNode* new_node = new DNode(value, node->next, node);
    if (node->next != nullptr) {
        node->next->prev = new_node;
    }
    node->next = new_node;

    if (node == _tail) {
        _tail = new_node;
    }
    _count++;
}

template <class T>
void DList<T>::pop_front() {
    if (is_empty()) throw std::invalid_argument("The list is empty");

    DNode* old_head = _head;
    _head = _head->next;

    if (_head != nullptr) {
        _head->prev = nullptr;
    }
    else {
        _tail = nullptr;
    }

    delete old_head;
    _count--;
}

template <class T>
void DList<T>::pop_back() {
    if (is_empty()) throw std::invalid_argument("The list is empty");

    DNode* old_tail = _tail;
    _tail = _tail->prev;

    if (_tail != nullptr) {
        _tail->next = nullptr;
    }
    else {
        _head = nullptr;
    }

    delete old_tail;
    _count--;
}

template <class T>
void DList<T>::erase(size_t pos) { // удаляет по позиции
    if (is_empty()) throw std::invalid_argument("The list is empty");
    if (pos >= _count) throw std::invalid_argument("Position out of range");
    if (pos == 0) {
        pop_front();
        return;
    }
    else if (pos == _count - 1) {
        pop_back();
        return;
    }

    DNode* cur = _head;
    size_t cur_pos = 0;
    while (cur != nullptr) {
        if (cur_pos == pos) break;
        cur_pos++;
        cur = cur->next;
    }
    if (cur == nullptr) throw std::invalid_argument("The position not found");
    erase(cur);
}

template <class T>
void DList<T>::erase(DNode* node) { // удаляет переданную ноду
    if (is_empty()) throw std::invalid_argument("The list is empty");
    if (node == nullptr) throw std::invalid_argument("The node not found");
    if (node == _head) {
        pop_front();
        return;
    }
    if (node == _tail) {
        pop_back();
        return;
    }

    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
    _count--;
}

template <class T>
DList<T>& DList<T>::operator=(const DList<T>& other) {
    if (this != &other) {
        while (_head != nullptr) {
            DNode* node = _head;
            _head = _head->next;
            delete node;
        }
        _tail = nullptr;
        _count = 0;

        DNode* current = other._head;
        while (current != nullptr) {
            push_back(current->value);
            current = current->next;
        }
    }
    return *this;
}

template <class T>
bool DList<T>::operator==(const DList<T>& other) const noexcept {
    if (size() != other.size()) {
        return false;
    }
    const DList<T>::DNode* current1 = _head;
    const DList<T>::DNode* current2 = other._head;

    while (current1 != nullptr) {
        if (current1->value != current2->value) {
            return false;
        }
        current1 = current1->next;
        current2 = current2->next;
    }
    return true;
}

template <class T>
bool DList<T>::operator!=(const DList<T>& other) const noexcept {
    return !(*this == other);
}

template <class T>
void DList<T>::print() noexcept {
    DNode* node = _head;
    std::cout << "values: ";
    for (size_t i = 0; i < _count; i++) {
        std::cout << node->value << " ";
        node = node->next;
    }
    std::cout << "\n";
}

template <class T>
bool DList<T>::is_empty() const noexcept { return _head == nullptr; }