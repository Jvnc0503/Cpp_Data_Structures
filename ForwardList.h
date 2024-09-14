#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include <stdexcept>
#include <iostream>

template<typename T>
struct Node {
    T data;
    Node *next;

    Node() : next(nullptr) {
    }

    explicit Node(T data) : data(data), next(nullptr) {
    }

    Node(T data, Node *next) : data(data), next(next) {
    }
};

template<typename T>
class ForwardList {
    Node<T> *head;

public:
    ForwardList() : head(nullptr) {
    }

    T front() const {
        return head->data;
    }

    T back() const {
        Node<T> *temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        return temp->data;
    }

    void push_front(T data) {
        auto node = new Node<T>(data);
        node->next = head;
        head = node;
    }

    void push_back(T data) {
        auto node = new Node<T>(data);

        if (head == nullptr) {
            head = node;
            return;
        }

        Node<T> *temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = node;
    }

    void pop_front() {
        const Node<T> *temp = head;
        head = head->next;
        delete temp;
    }

    void pop_back() {
        if (head == nullptr) {
            return;
        }
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            return;
        }
        Node<T> *temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
    }

    void insert(const T &data, const size_t position) {
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

        node->next = temp->next;
        temp->next = node;
    }

    void clear() {
        while (head != nullptr) {
            const Node<T> *temp = head;
            head = head->next;
            delete temp;
        }
    }

    T &operator[](const size_t index) const {
        Node<T> *temp = head;
        for (size_t i = 0; i < index; i++) {
            if (temp == nullptr) {
                throw std::out_of_range("Index out of range");
            }
            temp = temp->next;
        }
        if (temp == nullptr) {
            throw std::out_of_range("Index out of range");
        }
        return temp->data;
    }

    void reverse() {
        Node<T> *prev = nullptr;

        while (head != nullptr) {
            Node<T> *current = head;
            head = head->next;
            current->next = prev;
            prev = current;
        }
        head = prev;
    }

    void sort() {
        Node<T> *sorted = nullptr;
        Node<T> *current = head;

        while (current != nullptr) {
            Node<T> *next = current->next;

            if (sorted == nullptr || sorted->data >= current->data) {
                current->next = sorted;
                sorted = current;
            } else {
                Node<T> *temp = sorted;
                while (temp->next != nullptr && temp->next->data < current->data) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }

            current = next;
        }

        head = sorted;
    }

    static void printList(const ForwardList<T> list) {
        Node<T> *temp = list.head;
        while (temp != nullptr) {
            std::cout << temp->data << ' ';
            temp = temp->next;
        }
    }

    bool empty() {
        if (head == nullptr) {
            return true;
        }
        return false;
    }

    int size() {
        size_t i = 0;
        Node<T> *temp = head;
        while (temp != nullptr) {
            temp = temp->next;
            ++i;
        }
        return i;
    }
};

#endif
