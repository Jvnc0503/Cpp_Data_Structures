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

    ~ForwardList() {
        clear();
    }

    T front() const {
        if (head == nullptr) {
            throw std::runtime_error("List is empty");
        }
        return head->data;
    }

    T back() const {
        if (head == nullptr) {
            throw std::runtime_error("List is empty");
        }
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

    T pop_front() {
        if (head == nullptr) {
            throw std::runtime_error("List is empty");
        }
        T data = head->data;
        const Node<T> *temp = head;
        head = head->next;
        delete temp;
        return data;
    }

    T pop_back() {
        if (head == nullptr) {
            throw std::runtime_error("List is empty");
        }
        if (head->next == nullptr) {
            T data = head->data;
            delete head;
            head = nullptr;
            return data;
        }
        Node<T> *temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        T data = temp->next->data;
        delete temp->next;
        temp->next = nullptr;
        return data;
    }

    void insert(const T &data, const size_t position) {
        if (position == 0) {
            push_front(data);
            return;
        }

        Node<T> *temp = head;
        for (size_t i = 0; i < position - 1; ++i) {
            if (temp == nullptr) {
                throw std::out_of_range("Index out of range");
            }
            temp = temp->next;
        }

        auto node = new Node<T>(data);
        node->next = temp->next;
        temp->next = node;
    }

    void clear() {
        while (head != nullptr) {
            const Node<T> *temp = head;
            head = head->next;
            delete temp;
        }
        head = nullptr;
    }

    T &operator[](const size_t index) const {
        if (head == nullptr) {
            throw std::out_of_range("Index out of range");
        }
        Node<T> *temp = head;
        for (size_t i = 0; i < index; i++) {
            if (temp == nullptr) {
                throw std::out_of_range("Index out of range");
            }
            temp = temp->next;
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

    static void printList(const ForwardList &list) {
        Node<T> *temp = list.head;
        while (temp != nullptr) {
            std::cout << temp->data << ' ';
            temp = temp->next;
        }
        std::cout << '\n';
    }

    bool empty() const {
        return head == nullptr;
    }

    size_t size() const {
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
