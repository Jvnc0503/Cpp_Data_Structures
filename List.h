#ifndef LIST_H
#define LIST_H

template <typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;
    Node() : next(nullptr), prev(nullptr) {}
};

template <typename T>
class List {
    Node<T>* head;
    Node<T>* tail;
public:
    List() : head(nullptr), tail(nullptr) {}

    T front() const {
        return head->data;
    }

    T back() const {
        return tail->data;
    }
};

#endif