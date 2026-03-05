#pragma once
#include <iostream>

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
        os << << node._data.key << " : " << node._data.value;
        return os;
    }
};

template <class TKey, class TValue>
class Tree {
    TreeNode<TKey, TValue>* _root;
public:
    Tree(TreeNode<TKey, TValue>* root = nullptr);
    // конструктор инициализации (с default nullptr)
    ~Tree();  // реализуется через проход

    void insert(const TKey&, const TValue&);
    TValue* find(const TKey&) const noexcept;  // возвращает первое попадание
    void erase(const TKey&);
    bool is_empty() const noexcept;
    void clear() noexcept;

    void print_w() const noexcept; // вывод в ширину
    void print_lcr() const noexcept;
    void print_lrc() const noexcept;
    void print_clr() const noexcept;

private:
    // O(N), память на стек вызовов
    void print_lcr_rec(TreeNode<TKey, TValue>*) const noexcept; 
    void print_clr_rec(TreeNode<TKey, TValue>*) const noexcept;
    void print_lrc_rec(TreeNode<TKey, TValue>*) const noexcept;
    void clear_rec(TreeNode<TKey, TValue>* node);  // обход в ширину нельзя, используем lrc
    TValue* find_rec(TreeNode<TKey, TValue>*, const TKey&) const noexcept;
};

template <class TKey, class TValue>
Tree<TKey, TValue>::Tree(TreeNode<TKey, TValue>* root) : _root(root) {}

template <class TKey, class TValue>
Tree<TKey, TValue>::~Tree() {
    if (_root) delete _root;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    TreeNode<TKey, TValue>* node = new TreeNode<TKey, TValue>(key, value);

    if (is_empty()) {
        _root = node;
        return;
    }

    // обход в ширину
    // проверять на дублёры не надо, они могут быть
    TreeNode<TKey, TValue>* cur = nullptr;
    Queue<TreeNode<TKey, TValue>*> q;
    q.push(_root);
    while (true) {
        cur = q.top();
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
TValue* Tree<TKey, TValue>::find(const TKey& key) const noexcept {
    return find_rec(_root, key);
}

template <class TKey, class TValue>
TValue* Tree<TKey, TValue>::find_rec(TreeNode<TKey, TValue>* node, const TKey& key) const noexcept {
    if (node != nullptr && node->_data.key == key) return node;
    if (node->_left == nullptr && node->_right == nullptr) return nullptr;

    return find_rec(node->_left);
    return find_rec(node->_right);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::erase(const TKey& key) {
    TreeNode<TKey, TValue>* node = find(key);
    if (node == nullptr) {
        throw std::logic_error("The node not found");
    }
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
void Tree<TKey, TValue>::print_w() const noexcept {  // O(N), память - количество элементов
    if (is_empty()) return;
    Queue<TreeNode<TKey, TValue*>> q;
    q.push(_root);
    TreeNode<TKey, TValue>* curr = q.top();

    while (!q.is_empty()) {
        std::cout << curr << " ";
        q.pop();
        if (curr->_left)
            q.push(curr->_left);
        if (curr->_right)
            q.push(cur->_right);
    }
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_lcr() const noexcept {
    print_lcr_rec(_root);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_lrc() const noexcept {
    print_lrc_rec(_root);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_clr() const noexcept {
    print_clr_rec(_root);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_clr_rec(TreeNode<TKey, TValue>* node) const noexcept {
    if (node == nullptr) return;

    std::cout << node->_data.second << " ";
    print_clr_rec(node->_left);  // можно добавить условие проверки на nullptr и убрать проверку из начала
    print_clr_rec(node->_right);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_lcr_rec(TreeNode<TKey, TValue>* node) const noexcept {
    if (node == nullptr) return;

    print_clr_rec(node->_left);
    std::cout << node->_data.second << " ";
    print_clr_rec(node->_right);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_lrc_rec(TreeNode<TKey, TValue>* node) const noexcept {
    if (node == nullptr) return;

    print_clr_rec(node->_left);
    print_clr_rec(node->_right);
    std::cout << node->_data.second << " ";
}