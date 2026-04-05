#pragma once
#include <iostream>

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
        AVLNode<TKey, TValue>* right = nullptr, AVLNode<TKey, TValue>* prent = nullptr,
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
    void insert(const TKey& key, const TValue& value);
    void erase(const TKey&);
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
    int calc_height(AVLNode<TKey, TValue>*);
};

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
    if (G->_parent->_right == G) {
        G->_parent->_right = P;
    }
    else if (G->_parent->_left == G) {
        G->_parent->_left = P;
    }

    // 2) P -> T | G -> T
    G->_right = P->_left;
    P->_left->_parent = G;
    P->_left = G;
    G->_parent = P;
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
    if (G->_parent->_right == G) {
        G->_parent->_right = P;
    }
    else if (G->_parent->_left == G) {
        G->_parent->_left = P;
    }

    // 2) P -> T | G -> T
    G->_left = P->_right;
    P->_right->_parent = G;
    P->_right = G;
    G->_parent = P;
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
void AVLTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    AVLNode<TKey, TValue>* node = BSTree::insert(key, value); // хуита

    if (node == _root)
        return;

    AVLNode<TKey, TValue>* P = node->_parent, * G = P->_parent;
    recalc_height(P);
    if (!G)
        return;

    int balance = recalc_balance(G);
    if (abs(balance) > 1) {
        recover_balance(G);  // внутри пересчитываем высоты
        return;
    }

    // если баланс не нарушился, пересчитываем высоты
    AVLNode<TKey, TValue>* curr = G;
    int prev_height;

    while (curr) {
        prev_height = curr->_height;
        recalc_height(curr);
        if (prev_height == curr->_height)
            break;

        curr = curr->_parent;
    }
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::erase(const TKey&) {
    // удалить, как из BSTree

    // начиная с фактически удалённого элемента:
    // 1) пересчитываем высоты
    // 2) пересчитываем баланс
    // 2.1) восстанавливаем баланс, если он был нарушен
    // 2.2) если что-то изменилось-> 1)

    AVLNode<TKey, TValue>* node = BSTree::erase(key);  // возвращается родитель фактически удалённого элемента (не ключ)

    while (node) {
        int balance = recalc_balance(node);

        if (abs(balance) > 1)
            recover_balance(node);

        int old_height = node->_height;
        recalc_height(node);
        if (old_height == node->_height)
            break;

        node = node->_parent;
    }
}