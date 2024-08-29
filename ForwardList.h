#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include <stdexcept>

template <typename T>
struct Node {
    T data;
    Node* next;
    Node () : next (nullptr) {}
    explicit Node (T data) : data (data), next (nullptr) {}
    Node (T data, Node* next) : data (data), next (next) {}
};

template <typename T>
class ForwardList {
    Node<T>* head;
public:
    ForwardList () : head (nullptr) {}

    T front() const {
        return head->data;
    }

    T back() const {
        Node<T>* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        return temp->data;
    }

    void push_front(T data) {
        auto node = new Node<T>(data);
        node->next = head;
        this->head = node;
    }

    void push_back(T data) {
        auto node = new Node<T>(data);
        Node<T>* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = node;
    }

    void pop_front() {
        const Node<T>* temp = head;
        this->head = head->next;
        delete temp;
    }

    void pop_back() {
        if (head->next == nullptr) {
            delete head;
            this->head = nullptr;
        }
        else {
            const Node<T>* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = nullptr;
        }
    }

    void insert_in_position(T data, const size_t position) {
        auto node = new Node<T>;
        Node<T>* temp = head;
        node->data = data;
        for (size_t i = 0; i < position - 1; i++) {
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

    T& operator[](const size_t index) const {
        Node<T>* temp = head;
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
        Node<T>* prev = nullptr;

        while (head != nullptr) {
            Node<T> *current = head;
            head = head->next;
            current->next = prev;
            prev = current;
        }
        head = prev;
    }
};

#endif