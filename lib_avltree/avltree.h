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
struct AVLNode {
    TreePair<TKey, TValue> _data;
    AVLNode<TKey, TValue>* _left;
    AVLNode<TKey, TValue>* _right;
    AVLNode<TKey, TValue>* _parent;
    int _height;

    AVLNode(TreePair<TKey, TValue> data, AVLNode<TKey, TValue>* left = nullptr,
        AVLNode<TKey, TValue>* right = nullptr, AVLNode<TKey, TValue>* parent = nullptr,
        int height = 1) : _data(data), _left(left), _right(right), _parent(parent), 
        _height(height) {}

    ~AVLNode() {}

    friend std::ostream& operator<<(std::ostream& os, const AVLNode& node) {
        os << node._data.key << " : " << node._data.value;
        return os;
    }
};

template <class TKey, class TValue>
class AVLTree {
    AVLNode<TKey, TValue>* _root;
public:
    AVLTree(AVLNode<TKey, TValue>* root = nullptr);
    //AVLTree(const AVLTree& other);
    ~AVLTree();

    AVLNode<TKey, TValue>* find(const TKey& key) const;
    void insert(const TKey& key, const TValue& value);
    void erase(const TKey&);
    bool is_empty() const noexcept;

    friend std::ostream& operator <<(std::ostream& os, const AVLTree& tree) {
        tree.print_visual_rec(tree._root, 0);
        os << "\n\n";
        return os;
    }
private:
    void left_rotate(AVLNode<TKey, TValue>*);
    void right_rotate(AVLNode<TKey, TValue>*);
    void RR(AVLNode<TKey, TValue>*);
    void LL(AVLNode<TKey, TValue>*);
    void RL(AVLNode<TKey, TValue>*);
    void LR(AVLNode<TKey, TValue>*);
    int recalc_balance(AVLNode<TKey, TValue>*);
    void recover_balance(AVLNode<TKey, TValue>*);
    void recalc_height(AVLNode<TKey, TValue>*);

    void delete_node(AVLNode<TKey, TValue>*&);
    AVLNode<TKey, TValue>* find_min_right_parent(AVLNode<TKey, TValue>* node) const noexcept;
    void replace_child(AVLNode<TKey, TValue>*& parent, AVLNode<TKey, TValue>*& erase_node,
        AVLNode<TKey, TValue>* new_child);
    AVLNode<TKey, TValue>* find_parent(const TKey& key) const;

    void print_visual_rec(const AVLNode<TKey, TValue>* node, int level) const;
};
template <class TKey, class TValue>
AVLTree<TKey, TValue>::AVLTree(AVLNode<TKey, TValue>* root) : _root(root) {}

template <class TKey, class TValue>
AVLTree<TKey, TValue>::~AVLTree() {
    if (!_root) return;

    LQueue<AVLNode<TKey, TValue>*> q;
    AVLNode<TKey, TValue>* current = nullptr;
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
void AVLTree<TKey, TValue>::left_rotate(AVLNode<TKey, TValue>* node) {
    AVLNode<TKey, TValue>* G = node, * P = G->_right;
    //
    // G                  P
    //   \              /   \
    //    P     --->   G     C
    //  /   \            \
    // T    C             T
    //

    // 1) GG -> G | GG -> P
    P->_parent = G->_parent;
    if (_root != G) {
        if (G->_parent->_right == G) {
            G->_parent->_right = P;
        }
        else if (G->_parent->_left == G) {
            G->_parent->_left = P;
        }
    }
    else {
        _root = P;
    }

    // 2) P -> T | G -> T
    G->_right = P->_left;
    if (P->_left) {
        P->_left->_parent = G;
    }
    P->_left = G;
    G->_parent = P;

    recalc_height(G);
    recalc_height(P);
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::right_rotate(AVLNode<TKey, TValue>* node) {
    AVLNode<TKey, TValue>* G = node, * P = G->_left;
    //             G             P
    //           /             /   \
    //          P      --->   C     G
    //         / \                 /
    //        C   T               T
    //
    //
    // 1) GG -> G | GG -> P
    P->_parent = G->_parent;
    if (_root != G) {
        if (G->_parent->_right == G) {
            G->_parent->_right = P;
        }
        else if (G->_parent->_left == G) {
            G->_parent->_left = P;
        }
    }
    else {
        _root = P;
    }

    // 2) P -> T | G -> T
    G->_left = P->_right;
    if (P->_right) {
        P->_right->_parent = G;
    }
    P->_right = G;
    G->_parent = P;

    recalc_height(G);
    recalc_height(P);
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::RR(AVLNode<TKey, TValue>* node) {  // передаётся дед (он сломал баланс)
    left_rotate(node);
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::LL(AVLNode<TKey, TValue>* node) {
    right_rotate(node);
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::RL(AVLNode<TKey, TValue>* node) {
    // G                G                 C
    //  \                \              /   \
    //   P     --->       C     --->   G     P
    //  /                  \
    // C                    P
    //
    AVLNode<TKey, TValue>* G = node, *P = G->_right;
    right_rotate(P);
    left_rotate(G);
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::LR(AVLNode<TKey, TValue>* node) {
    //   G                G               C
    //  /                /              /   \
    // P       --->     C     --->     P     G
    //  \              /
    //   C            P
    //
    AVLNode<TKey, TValue>* G = node, * P = G->_left;
    left_rotate(P);
    right_rotate(G);
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    //AVLNode<TKey, TValue>* node = BSTree::insert(key, value); // 
    AVLNode<TKey, TValue>* parent = find_parent(key);
    AVLNode<TKey, TValue>* node = nullptr;
    if (!parent && !_root) {
        _root = new AVLNode<TKey, TValue>(TreePair<TKey, TValue>(key, value), nullptr, nullptr, parent);
        return;
    }
    else if (!parent && _root) {
        throw std::invalid_argument("This key already exists");
    }
    else if (parent->_data.key < key && !parent->_right) {
        parent->_right = new AVLNode<TKey, TValue>(TreePair<TKey, TValue>(key, value), nullptr, nullptr, parent);
        node = parent->_right;
    }
    else if (parent->_data.key > key && !parent->_left) {
        parent->_left = new AVLNode<TKey, TValue>(TreePair<TKey, TValue>(key, value), nullptr, nullptr, parent);
        node = parent->_left;
    }
    else {
        throw std::invalid_argument("This key already exists");
    }
    //
    AVLNode<TKey, TValue>* P = node->_parent, *G = P->_parent;
    recalc_height(P);
    if (!G)
        return;

    int balance = recalc_balance(G);
    if (abs(balance) > 1) {
        recover_balance(G);  // внутри пересчитываем высоты
        return;
    }

    AVLNode<TKey, TValue>* curr = G;
    while (curr) {
        int old_height = curr->_height;
        recalc_height(curr);

        if (abs(recalc_balance(curr)) > 1) {
            recover_balance(curr);
            recalc_height(curr);
        }
        if (old_height == curr->_height)
            break;

        curr = curr->_parent;
    }
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::find(const TKey& key) const {
    if (_root && _root->_data.key == key)
        return _root;
    AVLNode<TKey, TValue>* parent = find_parent(key);
    if (!parent)
        return nullptr;

    if (parent->_left && parent->_left->_data.key == key)
        return parent->_left;
    if (parent->_right && parent->_right->_data.key == key)
        return parent->_right;

    return nullptr;
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::find_parent(const TKey& key) const {
    if (is_empty()) return nullptr;
    if (_root->_data.key == key) return nullptr;

    AVLNode<TKey, TValue>* node = _root;
    while (true) {
        if (node->_data.key > key) {
            if (!node->_left)  // parent for insert
                return node;
            if (node->_left->_data.key == key)  // parent for find
                return node;
            else node = node->_left;
        }
        else {
            if (!node->_right)
                return node;
            if (node->_right->_data.key == key)
                return node;
            else node = node->_right;
        }
    }
    return nullptr;
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::erase(const TKey& key) {
    // удалить, как из BSTree

    // начиная с фактически удалённого элемента:
    // 1) пересчитываем высоты
    // 2) пересчитываем баланс
    // 2.1) восстанавливаем баланс, если он был нарушен
    // 2.2) если что-то изменилось-> 1)

    //AVLNode<TKey, TValue>* node = BSTree::erase(key);  // возвращается родитель фактически удалённого элемента (не ключ)
    if (is_empty()) {
        throw std::logic_error("The tree is empty");
    }
    AVLNode<TKey, TValue>* node = find(key);
    if (node == nullptr || node->_data.key != key) {
        throw std::logic_error("The key not found");
    }
    AVLNode<TKey, TValue>* parent = node->_parent;
    delete_node(node);
    //
    if (!parent) parent = _root;
    while (parent) {
        int old_height = parent->_height;
        recalc_height(parent);

        if (abs(recalc_balance(parent)) > 1) {
            recover_balance(parent);
            recalc_height(parent);
        }
        if (old_height == parent->_height)
            break;

        parent = parent->_parent;
    }
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::delete_node(AVLNode<TKey, TValue>*& erase_node) {
    if (!erase_node->_left && !erase_node->_right) {
        replace_child(erase_node->_parent, erase_node, nullptr);
        delete erase_node;
    }
    else if (!erase_node->_right) {
        replace_child(erase_node->_parent, erase_node, erase_node->_left);
        delete erase_node;
    }
    else if (!erase_node->_left) {
        replace_child(erase_node->_parent, erase_node, erase_node->_right);
        delete erase_node;
    }
    else {
        AVLNode<TKey, TValue>* found_parent_node = find_min_right_parent(erase_node);
        AVLNode<TKey, TValue>* found_node;
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
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::find_min_right_parent(AVLNode<TKey, TValue>* node) const noexcept {
    if (!node) return nullptr;
    if (node->_right) {
        AVLNode<TKey, TValue>* parent = node;
        AVLNode<TKey, TValue>* tmp = node->_right;
        while (tmp->_left) {
            parent = tmp;
            tmp = tmp->_left;
        }
        return parent;
    }
    return nullptr;
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::replace_child(AVLNode<TKey, TValue>*& parent, AVLNode<TKey, TValue>*& erase_node,
    AVLNode<TKey, TValue>* new_child) {
    if (!parent) {
        _root = new_child;
        if (new_child) {
            new_child->_parent = parent;
        }
    }
    else if (parent->_data.key < erase_node->_data.key) {
        parent->_right = new_child;
        if (new_child) {
            new_child->_parent = parent;
        }
    }
    else {
        parent->_left = new_child;
        if (new_child) {
            new_child->_parent = parent;
        }
    }
}

template <class TKey, class TValue>
int AVLTree<TKey, TValue>::recalc_balance(AVLNode<TKey, TValue>* node) {
    if (!node) return 0;

    int left_height = (node->_left) ? node->_left->_height : 0;
    int right_height = (node->_right) ? node->_right->_height : 0;

    return right_height - left_height;
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::recover_balance(AVLNode<TKey, TValue>* node) {
    int balance = recalc_balance(node);
    if (balance > 1) {
        int right_balance = recalc_balance(node->_right);
        if (right_balance < 0) {
            RL(node);
        }
        else {
            RR(node);
        }
    }
    else if (balance < -1) {
        int left_balance = recalc_balance(node->_left);
        if (left_balance > 0) {
            LR(node);
        }
        else {
            LL(node);
        }
    }
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::recalc_height(AVLNode<TKey, TValue>* node) {
    if (!node) return;

    int left_height = (node->_left) ? node->_left->_height : 0;
    int right_height = (node->_right) ? node->_right->_height : 0;

    node->_height = (left_height > right_height ? left_height : right_height) + 1;
}

template <class TKey, class TValue>
bool AVLTree<TKey, TValue>::is_empty() const noexcept {
    return _root == nullptr;
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::print_visual_rec(const AVLNode<TKey, TValue>* node, int level) const {
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