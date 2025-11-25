#pragma once
#include "../lib_list/list.h"

/*
template <class T>
bool is_looped_1(List<T>& list) {
    if (list.is_empty()) return false;

    List<T>::Iterator it1 = list.begin();
    List<T>::Iterator it2 = list.begin();

    while (it1 != list.end()) {
        it1++;
        it2++;
        if (it1 == list.end()) break;
        it1++;
        if (it1 == it2) {
            return true;
        }
    }

    return false;
}
*/

template <class T>
bool is_looped_1(List<T>& list) {
    if (list.is_empty()) return false;

    List<T>::Node* slow = list.head();
    List<T>::Node* fast = list.head();

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return true;
        }
    }

    return false;
}

template <class T>
bool is_looped_2(List<T>& list) {
    if (list.is_empty()) return false;

    List<T>::Node* curr = list.head();
    List<T>::Node* prev = nullptr;
    bool is_looped = false;

    while (curr != nullptr) {
        if (curr->next == list.head()) {
            is_looped = true;
        }
        List<T>::Node* tmp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = tmp;
    }

    // функция свапа
    curr = prev;
    prev = nullptr;
    while (curr != nullptr) {
        List<T>::Node* tmp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = tmp;
    }

    return is_looped;
}


template <class T>
typename List<T>::Node* find_loop(List<T>& list) {
    if (list.is_empty()) return nullptr;

    List<T>::Node* slow = list.head();
    List<T>::Node* fast = list.head();

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            break;
        }
    }

    if (fast == nullptr || fast->next == nullptr) return nullptr;

    slow = list.head();
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }

    return slow;
}

