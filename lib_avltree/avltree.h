#pragma once
#include <iostream>
#include "../lib_lqueue/lqueue.h"
#include "../lib_bstree/bstree.h"

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
class AVLTree : public BSTree<TKey, TValue, AVLNode<TKey, TValue>> {
public:
    AVLTree(AVLNode<TKey, TValue>* root = nullptr);
    AVLTree(const AVLTree& other);
    ~AVLTree();

    AVLNode<TKey, TValue>* find(const TKey& key) const;
    void insert(const TKey& key, const TValue& value);
    void erase(const TKey&);
    bool is_empty() const noexcept;

    friend std::ostream& operator <<(std::ostream& os, const AVLTree& tree) {
        os << static_cast<const BSTree<TKey, TValue, AVLNode<TKey, TValue>>&>(tree);
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
};

template <class TKey, class TValue>
AVLTree<TKey, TValue>::AVLTree(AVLNode<TKey, TValue>* root) : BSTree<TKey, TValue, AVLNode<TKey, TValue>>(root) {}

template <class TKey, class TValue>
AVLTree<TKey, TValue>::AVLTree(const AVLTree& other) : BSTree<TKey, TValue, AVLNode<TKey, TValue>>(other) {}

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
void AVLTree<TKey, TValue>::RR(AVLNode<TKey, TValue>* node) {  // передается дед
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
    AVLNode<TKey, TValue>* parent = BSTree::insert_and_return_node(key, value);
    if (!parent) return;

    AVLNode<TKey, TValue>* node;
    if (parent->_right && parent->_right->_data.key == key) {
        node = parent->_right;
    }
    else if (parent->_left && parent->_left->_data.key == key) {
        node = parent->_left;
    }
    node->_parent = parent;

    AVLNode<TKey, TValue>* P = node->_parent, *G = P->_parent;
    recalc_height(P);
    if (!G)
        return;

    int balance = recalc_balance(G);
    if (abs(balance) > 1) {
        recover_balance(G);
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
    return BSTree<TKey, TValue, AVLNode<TKey, TValue>>::find(key);
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::erase(const TKey& key) {
    // начиная с фактически удалённого элемента:
    // 1) пересчитываем высоты
    // 2) пересчитываем баланс
    // 2.1) восстанавливаем баланс, если он был нарушен
    // 2.2) если что-то изменилось-> 1)

    AVLNode<TKey, TValue>* parent = BSTree::erase_and_return_node(key);

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
    return BSTree<TKey, TValue, AVLNode<TKey, TValue>>::is_empty();
}
