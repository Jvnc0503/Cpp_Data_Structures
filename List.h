#ifndef LIST_H
#define LIST_H
#include <stdexcept>

template<typename T>
struct Node {
    T data;
    Node *next;
    Node *prev;

    Node() : next(nullptr), prev(nullptr) {
    }

    explicit Node(const T &data) : data(data), next(nullptr), prev(nullptr) {
    }
};

template<typename T>
class List {
    Node<T> *head;
    Node<T> *tail;

public:
    List() : head(nullptr), tail(nullptr) {
    }

    T front() const {
        return head->data;
    }

    T back() const {
        return tail->data;
    }

    void push_front(const T &data) {
        auto node = new Node<T>(data);
        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            head->prev = node;
            node->next = head;
            head = node;
        }
    }

    void push_back(const T &data) {
        auto node = new Node<T>(data);
        if (tail == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }

    void insert(T data, const size_t position) {
        if (position == 0) {
            push_front(data);
            return;
        }

        auto node = new Node<T>(data);
        Node<T> *temp = head;

        for (size_t i = 0; i < position; ++i) {
            if (temp == nullptr) {
                throw std::out_of_range("Index out of range");
            }
            temp = temp->next;
        }

        if (temp->next == nullptr) {
            temp->next = node;
            node->prev = temp;
            tail = node;
        } else {
            node->next = temp->next;
            node->prev = temp;
            temp->next->prev = node;
            temp->next = node;
        }
    }
};

#endif
