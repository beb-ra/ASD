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

    friend std::ostream& operator <<(std::ostream& os, const Tree& tree) {
        tree.print_visual_rec(tree._root, 0);
        os << "\n\n";
        return os;
    }

private:
    void print_lcr_rec(TreeNode<TKey, TValue>*) const noexcept; 
    void print_clr_rec(TreeNode<TKey, TValue>*) const noexcept;
    void print_lrc_rec(TreeNode<TKey, TValue>*) const noexcept;
    void clear_rec(TreeNode<TKey, TValue>* node);

    TreeNode<TKey, TValue>* find_last_node_parent() const;
    void print_visual_rec(const TreeNode<TKey, TValue>* node, int level) const;
};

template <class TKey, class TValue>
Tree<TKey, TValue>::Tree(TreeNode<TKey, TValue>* root) : _root(root) {}

template <class TKey, class TValue>
Tree<TKey, TValue>::~Tree() {
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
void Tree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    TreePair<TKey, TValue> pair = TreePair<TKey, TValue>(key, value);
    TreeNode<TKey, TValue>* node = new TreeNode<TKey, TValue>(pair);
    if (is_empty()) {
        _root = node;
        return;
    }

    TreeNode<TKey, TValue>* cur = nullptr;
    LQueue<TreeNode<TKey, TValue>*> q;
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
    LQueue<TreeNode<TKey, TValue>*> q;
    q.push(_root);
    while (!q.is_empty()) {
        cur = q.head();
        q.pop();
        if (cur != nullptr && cur->_data.key == key) {
            return cur;
        }

        if (cur->_left) q.push(cur->_left);
        if (cur->_right) q.push(cur->_right);
    }
    return nullptr;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::erase(const TKey& key) {
    TreeNode<TKey, TValue>* node = find(key);
    if (node == nullptr) {
        throw std::logic_error("The key not found");
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
        delete _root;
        _root = nullptr;
        return;
    }
    node->_data = last->_data;

    last->_left = nullptr;
    last->_right = nullptr;
    delete last;
}

template <class TKey, class TValue>
TreeNode<TKey, TValue>* Tree<TKey, TValue>::find_last_node_parent() const {
    if (is_empty()) {
        return nullptr;
    }

    LQueue<TreeNode<TKey, TValue>*> q;
    q.push(_root);
    TreeNode<TKey, TValue>* parent = nullptr;

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
    }
    return parent;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::clear() noexcept {
    clear_rec(_root);
    _root = nullptr;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::clear_rec(TreeNode<TKey, TValue>* node) {
    if (node == nullptr) return;

    clear_rec(node->_left);
    clear_rec(node->_right);

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
    LQueue<TreeNode<TKey, TValue>*> q;
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

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_visual_rec(const TreeNode<TKey, TValue>* node, int level) const {
    if (!node) return;

    print_visual_rec(node->_right, level + 1);

    for (int i = 0; i < level; i++) {
        std::cout << "          ";
    }
    std::cout << node->_data.key << " : " << node->_data.value;

    int num_length = std::to_string(node->_data.key).length()
        + std::to_string(node->_data.value).length();
    for (int j = 0; j < num_length; j++) {
        std::cout << "  ";
    }
    std::cout << std::endl;

    print_visual_rec(node->_left, level + 1);
}