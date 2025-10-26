#pragma once

template <class T>
struct Node {
private:
    T _value;
    Node<T>* _next;
public:
    Node(T value, Node<T>* next = nullptr) : _value(value), _next(next) {}

    const T& value() const { return _value; }
    const Node<T>* next() const { return _next; }
    T& value() { return _value; }
    Node<T>* next() { return _next; }

    void set_value(const T& value) { _value = value; }
    void set_next(Node<T>* next) { _next = next; }
};