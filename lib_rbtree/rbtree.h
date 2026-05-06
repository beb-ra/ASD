#pragma once
#include <iostream>
#include "../lib_lqueue/lqueue.h"
#include "../lib_bstree/bstree.h"

enum Color {
    red,        // ()
    black,      // []
    blackblack  // {}
};

template <class TKey, class TValue>
struct RBNode {
    TreePair<TKey, TValue> _data;
    Color _color;
    RBNode<TKey, TValue>* _left;
    RBNode<TKey, TValue>* _right;
    RBNode<TKey, TValue>* _parent;
    int _height;

    RBNode(TreePair<TKey, TValue> data, Color color = red, RBNode<TKey, TValue>* left = nullptr,
        RBNode<TKey, TValue>* right = nullptr, RBNode<TKey, TValue>* parent = nullptr,
        int height = 1) : _data(data), _color(color), _left(left), _right(right), _parent(parent),
        _height(height) {}

    ~RBNode() {}

    friend std::ostream& operator<<(std::ostream& os, const RBNode& node) {
        if (node._color == Color::red) {
            os << "(" << node._data.key << " : " << node._data.value << ")";
        }
        else if (node._color == Color::black) {
            os << "[" << node._data.key << " : " << node._data.value << "]";
        }
        else {
            os << "{" << node._data.key << " : " << node._data.value << "}";
        }
        return os;
    }
};

template <class TKey, class TValue>
class RBTree : public BSTree<TKey, TValue, RBNode<TKey, TValue>> {
public:
    RBTree(RBNode<TKey, TValue>* root = nullptr);
    RBTree(const RBTree& other);
    ~RBTree();

    RBNode<TKey, TValue>* find(const TKey& key) const;
    void insert(const TKey& key, const TValue& value);
    void erase(const TKey&);
    bool is_empty() const noexcept;

    friend std::ostream& operator <<(std::ostream& os, const RBTree& tree) {
        os << static_cast<const BSTree<TKey, TValue, RBNode<TKey, TValue>>&>(tree);
        return os;
    }
private:
    void left_rotate(RBNode<TKey, TValue>*);
    void right_rotate(RBNode<TKey, TValue>*);
    void swap_colors(RBNode<TKey, TValue>*, RBNode<TKey, TValue>*);
    void recover_balance(RBNode<TKey, TValue>*);
    RBNode<TKey, TValue>* copy_rec(RBNode<TKey, TValue>*);
};

template <class TKey, class TValue>
RBTree<TKey, TValue>::RBTree(RBNode<TKey, TValue>* root) : BSTree<TKey, TValue, RBNode<TKey, TValue>>(root) {}

template <class TKey, class TValue>
RBTree<TKey, TValue>::RBTree(const RBTree& other) {
    if (other._root) {
        _root = copy_rec(other._root);
    }
}

template <class TKey, class TValue>
RBTree<TKey, TValue>::~RBTree() {
    if (!_root) return;

    LQueue<RBNode<TKey, TValue>*> q;
    RBNode<TKey, TValue>* current = nullptr;
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
void RBTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    RBNode<TKey, TValue>* parent = BSTree::insert_and_return_node(key, value);
    if (parent == nullptr) {
        _root->_color = black;
        return;
    }

    RBNode<TKey, TValue>* node;
    if (parent->_left && parent->_left->_data.key == key) {
        parent->_left->_parent = parent;
        node = parent->_left;
    }
    else if (parent->_right && parent->_right->_data.key == key) {
        parent->_right->_parent = parent;
        node = parent->_right;
    }

    if (parent == _root) return;

    if (parent->_color == red) { // вынести в отдельную функцию
        recover_balance(node);
    }
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::recover_balance(RBNode<TKey, TValue>* C) {
    RBNode<TKey, TValue>* P = C->_parent;
    RBNode<TKey, TValue>* G = P->_parent;
    RBNode<TKey, TValue>* U = nullptr;
    if (G->_left && G->_left == P) {
        U = G->_right;
    }
    else {
        U = G->_left;
    }

    if (U && U->_color == red && !U->_left && !U->_right) {
        while (U->_color == red && P->_color == red) {
            U->_color = black;
            P->_color = black;
            if (_root == G) break;
            G->_color = red;
            C = G;
            P = C->_parent;
            G = P->_parent;
            if (G && G->_left && G->_left == P) {
                U = G->_right;
            }
            else if (G) {
                U = G->_left;
            }
        }
    }
    if (P->_color == black) return;
    // U is black
    if (G->_right && G->_right == P && P->_right && P->_right == C) {
        left_rotate(G);
        swap_colors(G, P);
    }
    else if (G->_left && G->_left == P && P->_left && P->_left == C) {
        right_rotate(G);
        swap_colors(G, P);
    }
    else if (G->_right && G->_right == P && P->_left && P->_left == C) {
        right_rotate(P);
        left_rotate(G);
        swap_colors(G, C);
    }
    else if (G->_left && G->_left == P && P->_right && P->_right == C) {
        left_rotate(P);
        right_rotate(G);
        swap_colors(G, C);
    }
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::left_rotate(RBNode<TKey, TValue>* node) {
    RBNode<TKey, TValue>* G = node, *P = G->_right;
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
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::right_rotate(RBNode<TKey, TValue>* node) {
    RBNode<TKey, TValue>* G = node, * P = G->_left;
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
}

template <class TKey, class TValue>
RBNode<TKey, TValue>* RBTree<TKey, TValue>::find(const TKey& key) const {
    return BSTree<TKey, TValue, RBNode<TKey, TValue>>::find(key);
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::erase(const TKey& key) {
    RBNode<TKey, TValue>* parent = BSTree::erase_and_return_node(key);
    //...
}

template <class TKey, class TValue>
bool RBTree<TKey, TValue>::is_empty() const noexcept {
    return BSTree<TKey, TValue, RBNode<TKey, TValue>>::is_empty();
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::swap_colors(RBNode<TKey, TValue>* first, 
    RBNode<TKey, TValue>* second) {
    Color temp = first->_color;
    first->_color = second->_color;
    second->_color = temp;
}

template <class TKey, class TValue>
RBNode<TKey, TValue>* RBTree<TKey, TValue>::copy_rec(RBNode<TKey, TValue>* node) {
    if (!node) return nullptr;

    RBNode<TKey, TValue>* new_node = new RBNode<TKey, TValue>(node->_data,
        node->_color, node->_left, node->_right, node->_parent);
    new_node->_left = copy_rec(node->_left);
    new_node->_right = copy_rec(node->_right);

    return new_node;
}