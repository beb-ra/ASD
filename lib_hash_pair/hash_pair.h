#pragma once
#include <iostream>
#include <algorithm>

template <class TValue>
struct HashPair {
    std::string key;
    TValue value;

    HashPair() : key("DEFAULT"), value() {}
    HashPair(std::string k, TValue v) : key(k), value(v) {}
};
