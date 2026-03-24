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

    bool is_leaf() const noexcept {
        return (_left || _right);
    }
};

template <class TKey, class TValue>
class BSTree {
    TreeNode<TKey, TValue>* _root;
public:
    BSTree(TreeNode<TKey, TValue>* root = nullptr);
    ~BSTree();

    TreeNode<TKey, TValue>* find(const TKey&) const noexcept;
    void insert(const TKey&, const TValue&);
    void erase(const TKey&);

    bool is_empty() const noexcept;
    void print_lcr() const noexcept;
    friend std::ostream& operator <<(std::ostream& os, const BSTree& tree) {
        tree.print_visual_rec(tree._root, 0);
        os << "\n\n";
        return os;
    }
private:
    TreeNode<TKey, TValue>* find_parent(const TKey&) const noexcept;
    void print_lcr_rec(TreeNode<TKey, TValue>*) const noexcept;
    TreeNode<TKey, TValue>* find_min_right_parent(TreeNode<TKey, TValue>*) const noexcept;
    void print_visual_rec(const TreeNode<TKey, TValue>* node, int level) const;

    void delete_node(TreeNode<TKey, TValue>*&, TreeNode<TKey, TValue>*&);
};

template <class TKey, class TValue>
BSTree<TKey, TValue>::BSTree(TreeNode<TKey, TValue>* root) : _root(root) {}

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
TreeNode<TKey, TValue>* BSTree<TKey, TValue>::find(const TKey& key) const noexcept {
    if (_root && _root->_data.key == key)
        return _root;
    TreeNode<TKey, TValue>* parent = find_parent(key);
    if (!parent)
        return nullptr;

    if (parent->_left && parent->_left->_data.key == key)
        return parent->_left;
    if (parent->_right && parent->_right->_data.key == key)
        return parent->_right;

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

template <class TKey, class TValue>
TreeNode<TKey, TValue>* BSTree<TKey, TValue>::find_min_right_parent(TreeNode<TKey, TValue>* node) const noexcept {
    if (!node) return nullptr;
    if (node->_right) {
        TreeNode<TKey, TValue>* parent = node;
        TreeNode<TKey, TValue>* tmp = node->_right; /////
        while (tmp->_left) {
            parent = tmp;
            tmp = tmp->_left;
        }
        return parent;
    }
    return nullptr;
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::erase(const TKey& key) {
    if (is_empty()) {
        throw std::logic_error("The tree is empty");
    }
    TreeNode<TKey, TValue>* parent = find_parent(key);
    TreeNode<TKey, TValue>* erase_node = nullptr;
    if (!parent) {
        erase_node = _root;
    }
    else if (parent->_data.key < key && parent->_right) {
        erase_node = parent->_right;
    }
    else if (parent->_data.key > key && parent->_left) {
        erase_node = parent->_left;
    }

    if (!erase_node) {
        throw std::logic_error("NODE IS WTF");
    }
    delete_node(parent, erase_node);
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::delete_node(TreeNode<TKey, TValue>*& parent, TreeNode<TKey, TValue>*& erase_node) {
    if (!erase_node->_left && !erase_node->_right) {  // лист
        if (!parent) {
            _root = nullptr;
        }
        else if (parent->_data.key < erase_node->_data.key) {
            parent->_right = nullptr;
        }
        else {
            parent->_left = nullptr;
        }
        delete erase_node;
        return;
    }
    else if (!erase_node->_right) {
        if (!parent) {
            _root = erase_node->_left;
        }
        else if (parent->_data.key < erase_node->_data.key) {
            parent->_right = erase_node->_left;
        }
        else {
            parent->_left = erase_node->_left;
        }
        delete erase_node;
    }
    else if (!erase_node->_left) {
        if (!parent) {
            _root = erase_node->_right;
        }
        else if (parent->_data.key < erase_node->_data.key) {
            parent->_right = erase_node->_right;
        }
        else {
            parent->_left = erase_node->_right;
        }
        delete erase_node;
    }
    else {
        TreeNode<TKey, TValue>* found_parent_node = find_min_right_parent(erase_node);
        TreeNode<TKey, TValue>* found_node;
        TreePair<TKey, TValue> replacement_data;
        if (found_parent_node == erase_node) {
            found_node = found_parent_node->_right;
            replacement_data = found_node->_data;
            found_parent_node->_right = found_node->_right;
        }
        else {
            found_node = found_parent_node->_left;
            replacement_data = found_node->_data;
            found_parent_node->_left = found_node->_right;
        }
        erase_node->_data = replacement_data;
        delete found_node;
    }
}

template <class TKey, class TValue>
TreeNode<TKey, TValue>* BSTree<TKey, TValue>::find_parent(const TKey& key) const noexcept {
    if (is_empty()) return nullptr;
    if (_root->_data.key == key) return nullptr;

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

template <class TKey, class TValue>
void BSTree<TKey, TValue>::print_visual_rec(const TreeNode<TKey, TValue>* node, int level) const {
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