#pragma once
#include <iostream>
#include "../lib_queue/queue.h"

template <class TKey, class TValue>
struct TPair {
    TKey key;
    TValue value;

    TPair() : key(), value() {}
    TPair(TKey k, TValue v) : key(k), value(v) {}
};

template <class TKey, class TValue>
struct TreeNode {
    TPair<TKey, TValue> _data;
    TreeNode<TKey, TValue>* _left;
    TreeNode<TKey, TValue>* _right;

    TreeNode(TPair<TKey, TValue> data, TreeNode<TKey, TValue>* left = nullptr,
        TreeNode<TKey, TValue>* right = nullptr) : _data(data), _left(left), _right(right) {}

    ~TreeNode() {
        if (_left) delete _left;
        if (_right) delete _right;
    }

    friend std::ostream& operator<<(std::ostream& os, const TreeNode& node) {
        os << node._data.key << " : " << node._data.value;
        return os;
    }
};

template <class TKey, class TValue>
class Tree {
    TreeNode<TKey, TValue>* _root;
public:
    Tree(TreeNode<TKey, TValue>* root = nullptr);
    ~Tree();

    void insert(const TKey&, const TValue&);
    TreeNode<TKey, TValue>* find(const TKey&) const noexcept;
    void erase(const TKey&);
    bool is_empty() const noexcept;
    void clear() noexcept;

    void print_w() const noexcept;
    void print_lcr() const noexcept;
    void print_lrc() const noexcept;
    void print_clr() const noexcept;

private:
    void print_lcr_rec(TreeNode<TKey, TValue>*) const noexcept; 
    void print_clr_rec(TreeNode<TKey, TValue>*) const noexcept;
    void print_lrc_rec(TreeNode<TKey, TValue>*) const noexcept;
    void clear_rec(TreeNode<TKey, TValue>* node);

    TreeNode<TKey, TValue>* find_last_node_parent();
};

template <class TKey, class TValue>
Tree<TKey, TValue>::Tree(TreeNode<TKey, TValue>* root) : _root(root) {}

template <class TKey, class TValue>
Tree<TKey, TValue>::~Tree() {
    if (_root) delete _root;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    TPair<TKey, TValue> pair = TPair<TKey, TValue>(key, value);
    TreeNode<TKey, TValue>* node = new TreeNode<TKey, TValue>(pair);

    if (is_empty()) {
        _root = node;
        return;
    }

    TreeNode<TKey, TValue>* cur = nullptr;
    Queue<TreeNode<TKey, TValue>*> q(10000);
    q.push(_root);
    while (true) {
        cur = q.head();
        q.pop();
        if (!cur->_left) {
            cur->_left = node;
            return;
        }
        if (!cur->_right) {
            cur->_right = node;
            return;
        }

        q.push(cur->_left);
        q.push(cur->_right);
    }
}

template <class TKey, class TValue>
TreeNode<TKey, TValue>* Tree<TKey, TValue>::find(const TKey& key) const noexcept {
    if (is_empty()) {
        return nullptr;
    }
    TreeNode<TKey, TValue>* cur = nullptr;
    Queue<TreeNode<TKey, TValue>*> q(10000);
    q.push(_root);
    while (true) {
        cur = q.head();
        if (cur != nullptr && cur->_data.key == key) {
            return cur;
        }
        if (cur == nullptr) {
            return nullptr;
        }
        q.pop();

        q.push(cur->_left);
        q.push(cur->_right);
    }
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::erase(const TKey& key) {
    TreeNode<TKey, TValue>* node = find(key);
    if (node == nullptr) {
        throw std::logic_error("The tree is empty");
    }
    TreeNode<TKey, TValue>* last_parent = find_last_node_parent();
    TreeNode<TKey, TValue>* last = nullptr;
    
    if (last_parent != nullptr) {
        if (last_parent->_right) {
            last = last_parent->_right;
            last_parent->_right = nullptr;
        }
        else if (last_parent->_left) {
            last = last_parent->_left;
            last_parent->_left = nullptr;
        }
    }
    else {
        _root = nullptr;
        return;
    }
    node->_data = last->_data;

    last->_left = nullptr;
    last->_right = nullptr;
    delete last;
}

template <class TKey, class TValue>
TreeNode<TKey, TValue>* Tree<TKey, TValue>::find_last_node_parent() {
    if (is_empty()) {
        return nullptr;
    }

    Queue<TreeNode<TKey, TValue>*> q(10000);
    q.push(_root);
    TreeNode<TKey, TValue>* parent = nullptr;
    TreeNode<TKey, TValue>* last = _root;

    while (!q.is_empty()) {
        TreeNode<TKey, TValue>* cur = q.head();
        q.pop();

        if (cur->_left) {
            parent = cur;
            q.push(cur->_left);
        }
        if (cur->_right) {
            parent = cur;
            q.push(cur->_right);
        }

        last = cur;
    }
    return parent;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::clear() noexcept {
    clear_rec(_root);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::clear_rec(TreeNode<TKey, TValue>* node) {
    if (node->left != nullptr) clear_rec(node->_left);
    if (node->right != nullptr) clear_rec(node->_right);

    delete node;
}

template <class TKey, class TValue>
bool Tree<TKey, TValue>::is_empty() const noexcept {
    return _root == nullptr;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_w() const noexcept {
    if (is_empty()) {
        std::cout << "\n";
        return;
    }
    TreeNode<TKey, TValue>* cur = nullptr;
    Queue<TreeNode<TKey, TValue>*> q(10000);
    q.push(_root);

    while (!q.is_empty()) {
        cur = q.head();
        std::cout << *cur << " ";
        q.pop();
        if (cur->_left)
            q.push(cur->_left);
        if (cur->_right)
            q.push(cur->_right);
    }
    std::cout << std::endl;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_lcr() const noexcept {
    print_lcr_rec(_root);
    std::cout << std::endl;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_lrc() const noexcept {
    print_lrc_rec(_root);
    std::cout << std::endl;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_clr() const noexcept {
    print_clr_rec(_root);
    std::cout << std::endl;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_clr_rec(TreeNode<TKey, TValue>* node) const noexcept {
    if (node == nullptr) return;

    std::cout << node->_data.value << " ";
    print_clr_rec(node->_left);
    print_clr_rec(node->_right);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_lcr_rec(TreeNode<TKey, TValue>* node) const noexcept {
    if (node == nullptr) return;

    print_lcr_rec(node->_left);
    std::cout << node->_data.value << " ";
    print_lcr_rec(node->_right);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_lrc_rec(TreeNode<TKey, TValue>* node) const noexcept {
    if (node == nullptr) return;

    print_lrc_rec(node->_left);
    print_lrc_rec(node->_right);
    std::cout << node->_data.value << " ";
}