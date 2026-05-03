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
struct BSTNode {
    TreePair<TKey, TValue> _data;
    BSTNode<TKey, TValue>* _left;
    BSTNode<TKey, TValue>* _right;

    BSTNode(TreePair<TKey, TValue> data, BSTNode<TKey, TValue>* left = nullptr,
        BSTNode<TKey, TValue>* right = nullptr) : _data(data), _left(left), _right(right) {}

    ~BSTNode() {}

    friend std::ostream& operator<<(std::ostream& os, const BSTNode& node) {
        os << node._data.key << " : " << node._data.value;
        return os;
    }
};

template <class TKey, class TValue, typename Node = BSTNode<TKey, TValue>>
class BSTree {
protected:
    Node* _root;
public:
    BSTree(Node* root = nullptr);
    BSTree(const BSTree& other);
    ~BSTree();
    BSTree& operator=(const BSTree& other);

    Node* find(const TKey& key) const noexcept;
    void insert(const TKey& key, const TValue& value);
    void erase(const TKey& key);
    void clear() noexcept;
    bool is_empty() const noexcept;

    void print_lcr() const noexcept;
    void print_lrc() const noexcept;
    void print_clr() const noexcept;

    friend std::ostream& operator <<(std::ostream& os, const BSTree& tree) {
        tree.print_visual_rec(tree._root, 0);
        os << "\n\n";
        return os;
    }
protected:
    Node* insert_and_return_node(const TKey& key, const TValue& value);
    Node* erase_and_return_node(const TKey& key);
private:
    Node* find_parent(const TKey& key) const noexcept;
    Node* find_min_right_parent(Node* node) const noexcept;

    void print_visual_rec(const Node* node, int level) const;
    void print_lcr_rec(Node* node) const noexcept;
    void print_clr_rec(Node* node) const noexcept;
    void print_lrc_rec(Node* node) const noexcept;

    void delete_node(Node*& parent, Node*& erase_node);
    void replace_child(Node*& parent, Node*& erase_node, Node* new_child);

    Node* copy_rec(Node* node);
    void clear_rec(Node* node);
};

template <class TKey, class TValue, class Node>
BSTree<TKey, TValue, Node>::BSTree(Node* root) : _root(root) {}

template <class TKey, class TValue, class Node>
BSTree<TKey, TValue, Node>::BSTree(const BSTree& other) : _root(nullptr) {
    if (other._root) {
        _root = copy_rec(other._root);
    }
}

template <class TKey, class TValue, class Node>
BSTree<TKey, TValue, Node>::~BSTree() {
    if (!_root) return;

    LQueue<Node*> q;
    Node* current = nullptr;
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

template <class TKey, class TValue, class Node>
BSTree<TKey, TValue, Node>& BSTree<TKey, TValue, Node>::operator=(const BSTree& other) {
    if (this != &other) {
        clear();
        if (other._root) {
            _root = copy_rec(other._root);
        }
    }
    return *this;
}

template <class TKey, class TValue, class Node>
Node* BSTree<TKey, TValue, Node>::find(const TKey& key) const noexcept {
    if (_root && _root->_data.key == key)
        return _root;
    Node* parent = find_parent(key);
    if (!parent)
        return nullptr;

    if (parent->_left && parent->_left->_data.key == key)
        return parent->_left;
    if (parent->_right && parent->_right->_data.key == key)
        return parent->_right;

    return nullptr;
}

template <class TKey, class TValue, class Node>
void BSTree<TKey, TValue, Node>::insert(const TKey& key, const TValue& value) {
    insert_and_return_node(key, value);
    /*
    Node* parent = find_parent(key);
    if (!parent && !_root) {
        _root = new Node(TreePair<TKey, TValue>(key, value));
        return;
    }
    if (!parent && _root) {
        throw std::invalid_argument("This key already exists");
    }
    if (parent->_data.key < key && !parent->_right) {
        parent->_right = new Node(TreePair<TKey, TValue>(key, value));
        return;
    }
    if (parent->_data.key > key && !parent->_left) {
        parent->_left = new Node(TreePair<TKey, TValue>(key, value));
        return;
    }

    throw std::invalid_argument("This key already exists");
    */
}

template <class TKey, class TValue, class Node>
void BSTree<TKey, TValue, Node>::erase(const TKey& key) {
    erase_and_return_node(key);
    /*
    if (is_empty()) {
        throw std::logic_error("The tree is empty");
    }
    Node* parent = find_parent(key);
    Node* erase_node = nullptr;
    if (!parent) {
        erase_node = _root;
    }
    else if (parent->_data.key < key && parent->_right) {
        erase_node = parent->_right;
    }
    else if (parent->_data.key > key && parent->_left) {
        erase_node = parent->_left;
    }

    if (erase_node == nullptr || erase_node->_data.key != key) {
        throw std::logic_error("The key not found");
    }

    delete_node(parent, erase_node);
    */
}

template <class TKey, class TValue, class Node>
void BSTree<TKey, TValue, Node>::clear() noexcept {
    if (node == nullptr) return;

    clear_rec(node->_left);
    clear_rec(node->_right);

    delete node;
}

template <class TKey, class TValue, class Node>
bool BSTree<TKey, TValue, Node>::is_empty() const noexcept {
    return _root == nullptr;
}

template <class TKey, class TValue, class Node>
void BSTree<TKey, TValue, Node>::print_lcr() const noexcept {
    print_lcr_rec(_root);
    std::cout << std::endl;
}

template <class TKey, class TValue, class Node>
void BSTree<TKey, TValue, Node>::print_lrc() const noexcept {
    print_lrc_rec(_root);
    std::cout << std::endl;
}

template <class TKey, class TValue, class Node>
void BSTree<TKey, TValue, Node>::print_clr() const noexcept {
    print_clr_rec(_root);
    std::cout << std::endl;
}

template <class TKey, class TValue, class Node>
Node* BSTree<TKey, TValue, Node>::insert_and_return_node(const TKey& key, const TValue& value) {
    Node* parent = find_parent(key);
    if (!parent && !_root) {
        _root = new Node(TreePair<TKey, TValue>(key, value));
        return parent;
    }
    if (!parent && _root) {
        throw std::invalid_argument("This key already exists");
    }
    if (parent->_data.key < key && !parent->_right) {
        parent->_right = new Node(TreePair<TKey, TValue>(key, value));
        return parent;
    }
    if (parent->_data.key > key && !parent->_left) {
        parent->_left = new Node(TreePair<TKey, TValue>(key, value));
        return parent;
    }

    throw std::invalid_argument("This key already exists");
}

template <class TKey, class TValue, class Node>
Node* BSTree<TKey, TValue, Node>::erase_and_return_node(const TKey& key) {
    if (is_empty()) {
        throw std::logic_error("The tree is empty");
    }
    Node* parent = find_parent(key);
    Node* erase_node = nullptr;
    if (!parent) {
        erase_node = _root;
    }
    else if (parent->_data.key < key && parent->_right) {
        erase_node = parent->_right;
    }
    else if (parent->_data.key > key && parent->_left) {
        erase_node = parent->_left;
    }

    if (erase_node == nullptr || erase_node->_data.key != key) {
        throw std::logic_error("The key not found");
    }

    delete_node(parent, erase_node);

    return parent;
}

template <class TKey, class TValue, class Node>
Node* BSTree<TKey, TValue, Node>::find_parent(const TKey& key) const noexcept {
    if (is_empty()) return nullptr;
    if (_root->_data.key == key) return nullptr;

    Node* curr = _root;
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

template <class TKey, class TValue, class Node>
Node* BSTree<TKey, TValue, Node>::find_min_right_parent(Node* node) const noexcept {
    if (!node) return nullptr;
    if (node->_right) {
        Node* parent = node;
        Node* tmp = node->_right;
        while (tmp->_left) {
            parent = tmp;
            tmp = tmp->_left;
        }
        return parent;
    }
    return nullptr;
}

template <class TKey, class TValue, class Node>
void BSTree<TKey, TValue, Node>::print_visual_rec(const Node* node, int level) const {
    if (!node) return;

    print_visual_rec(node->_right, level + 1);

    for (int i = 0; i < level; i++) {
        std::cout << "          ";
    }
    //std::cout << node->_data.key << " : " << node->_data.value;
    std::cout << *node;

    int num_length = std::to_string(node->_data.key).length()
        + std::to_string(node->_data.value).length();
    for (int j = 0; j < num_length; j++) {
        std::cout << "  ";
    }
    std::cout << std::endl;

    print_visual_rec(node->_left, level + 1);
}

template <class TKey, class TValue, class Node>
void BSTree<TKey, TValue, Node>::print_lcr_rec(Node* node) const noexcept {
    if (node == nullptr) return;

    print_lcr_rec(node->_left);
    std::cout << node->_data.key << " : " << node->_data.value << " ";
    print_lcr_rec(node->_right);
}

template <class TKey, class TValue, class Node>
void BSTree<TKey, TValue, Node>::print_clr_rec(Node* node) const noexcept {
    if (node == nullptr) return;

    std::cout << node->_data.key << " : " << node->_data.value << " ";
    print_clr_rec(node->_left);
    print_clr_rec(node->_right);
}

template <class TKey, class TValue, class Node>
void BSTree<TKey, TValue, Node>::print_lrc_rec(Node* node) const noexcept {
    if (node == nullptr) return;

    print_lrc_rec(node->_left);
    print_lrc_rec(node->_right);
    std::cout << node->_data.key << " : " << node->_data.value << " ";
}

template <class TKey, class TValue, class Node>
void BSTree<TKey, TValue, Node>::delete_node(Node*& parent, Node*& erase_node) {
    if (!erase_node->_left && !erase_node->_right) {
        replace_child(parent, erase_node, nullptr);
        delete erase_node;
    }
    else if (!erase_node->_right) {
        replace_child(parent, erase_node, erase_node->_left);
        delete erase_node;
    }
    else if (!erase_node->_left) {
        replace_child(parent, erase_node, erase_node->_right);
        delete erase_node;
    }
    else {
        Node* found_parent_node = find_min_right_parent(erase_node);
        Node* found_node;
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

template <class TKey, class TValue, class Node>
void BSTree<TKey, TValue, Node>::replace_child(Node*& parent, Node*& erase_node, Node* new_child) {
    if (!parent) {
        _root = new_child;
    }
    else if (parent->_data.key < erase_node->_data.key) {
        parent->_right = new_child;
    }
    else {
        parent->_left = new_child;
    }
}

template <class TKey, class TValue, class Node>
Node* BSTree<TKey, TValue, Node>::copy_rec(Node* node) {
    if (!node) return nullptr;

    Node* new_node = new Node(node->_data);
    new_node->_left = copy_rec(node->_left);
    new_node->_right = copy_rec(node->_right);

    return new_node;
}

template <class TKey, class TValue, class Node>
void BSTree<TKey, TValue, Node>::clear_rec(Node* node) {
    clear_rec(_root);
    _root = nullptr;
}
