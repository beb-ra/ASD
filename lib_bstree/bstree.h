#pragma once
#include <iostream>
#include "../lib_lqueue/lqueue.h"

template <class TKey, class TValue>
struct TreePair {
    TKey key;
    TValue value;

    TreePair() : key(), value() {}
    TreePair(TKey k, TValue v) : key(k), value(v) {}
};

template <class TKey, class TValue>
struct TreeNode {
    TreePair<TKey, TValue> _data;
    TreeNode<TKey, TValue>* _left;
    TreeNode<TKey, TValue>* _right;

    TreeNode(TreePair<TKey, TValue> data, TreeNode<TKey, TValue>* left = nullptr,
        TreeNode<TKey, TValue>* right = nullptr) : _data(data), _left(left), _right(right) {}

    ~TreeNode() {}

    friend std::ostream& operator<<(std::ostream& os, const TreeNode& node) {
        os << node._data.key << " : " << node._data.value;
        return os;
    }
};

template <class TKey, class TValue>
class BSTree {
    TreeNode<TKey, TValue>* _root;
public:
    BSTree(TreeNode<TKey, TValue>* root = nullptr);
    ~BSTree();

    TValue* find(const TKey&) const noexcept;
    void insert(const TKey&, const TValue&);
    //void erase(const TKey&);

    friend std::ostream& operator <<(std::ostream& os, const BSTree& tree) {
        tree.print_visual_rec(tree._root, 0);
        os << "\n\n";
        return os;
    }
    bool is_empty() const noexcept;
    void print_lcr() const noexcept;

private:
    TreeNode<TKey, TValue>* find_parent(const TKey&) const noexcept;
    void print_lcr_rec(TreeNode<TKey, TValue>*) const noexcept;
};

template <class TKey, class TValue>
BSTree<TKey, TValue>::BSTree(TreeNode<TKey, TValue>* root = nullptr) : _root(root) {}

template <class TKey, class TValue>
BSTree<TKey, TValue>::~BSTree() {
    if (!_root) return;

    LQueue<TreeNode<TKey, TValue>*> q;
    TreeNode<TKey, TValue>* current = nullptr;
    q.push(_root);

    while (!q.is_empty()) {
        current = q.head();
        q.pop();
        if (current->_left) {
            q.push(current->_left);
        }
        if (current->_right) {
            q.push(current->_right);
        }
        delete current;
    }
    _root = nullptr;
}

template <class TKey, class TValue>
bool BSTree<TKey, TValue>::is_empty() const noexcept {
    return _root == nullptr;
}

template <class TKey, class TValue>
TValue* BSTree<TKey, TValue>::find(const TKey& key) const noexcept {
    TreeNode<TKey, TValue>* parent = find_parent(key);

    if (!parent)
        return nullptr;
    if (parent->_left&& parent->_left->_data.key = key)
        return &parent->_left->_data.second;
    if (parent->_right&& parent->_right->_data.key = key)
        return &parent->_right->_data.value;
    if (parent == _root)
        return &_root->_data.value;
    return nullptr;
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    TreeNode<TKey, TValue>* parent = find_parent(key);
    if (!parent) {
        _root = new TreeNode<TKey, TValue>(TreePair<TKey, TValue>(key, value));
        return;
    }
    if (parent->_data.key < key && !parent->_right) {
        parent->_right = new TreeNode<TKey, TValue>(TreePair<TKey, TValue>(key, value));
        return;
    }
    if (parent->_data.key > key && !parent->_left) {
        parent->_left = new TreeNode<TKey, TValue>(TreePair<TKey, TValue>(key, value));
        return;
    }

    throw std::invalid_argument("This key already exists");
}

/*
template <class TKey, class TValue>
void BSTree<TKey, TValue>::erase(const TKey& key) {
    TreeNode<TKey, TValue>* parent = find_parent(key);
    // нужна вспомогательная переменная
    if (parent->_data.first < key && parent->_right) {
        if (!parent->_right->_left && !parent->_right->_left) {  // лист (ничего дальше нет)
            delete parent->_right;
            parent->_right = nullptr;
            return;
        }
        if (!parent->_right->_left) {
            TreeNode<TKey, TValue>* node = parent->_right;
            parent->_right = parent->_right->_right;
            delete node;
        }
        // то же самое с другой стороной
    }
    // если есть оба звена, то перецепляем либо максимальный слева, либо минимальный справа (find_max_left, find_min_right)
}
*/

template <class TKey, class TValue>
TreeNode<TKey, TValue>* BSTree<TKey, TValue>::find_parent(const TKey& key) const noexcept {
    if (is_empty()) return nullptr;

    if (_root->_data.key == key) return _root;

    TreeNode<TKey, TValue>* curr = _root;

    while (true) {
        if (curr->_data.key > key) {
            if (!curr->_left)  // parent for insert
                return curr;
            if (curr->_left->_data.key == key)  // parent for find
                return curr;
            else curr = curr->_left;
        }
        else {
            if (!curr->_right)
                return curr;
            if (curr->_right->_data.key == key)
                return curr;
            else curr = curr->_right;
        }
    }

}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::print_lcr() const noexcept {
    print_lcr_rec(_root);
    std::cout << std::endl;
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::print_lcr_rec(TreeNode<TKey, TValue>* node) const noexcept {
    if (node == nullptr) return;

    print_lcr_rec(node->_left);
    std::cout << node->_data.value << " ";
    print_lcr_rec(node->_right);
}