#ifndef FORWARDLIST_H
#define FORWARDLIST_H

template <typename T>
struct Node {
    T data;
    Node* next;
};

template <typename T>
class ForwardList {
    Node<T>* head;
public:
    ForwardList():head(nullptr){};
    void push_front(T data) {
        auto* node = new Node<T>;
        node->data = data;
        node->next = head;
        this->head = node;
    }
    void push_back(T data) {
        auto* node = new Node<T>;
        node->data = data;
        auto* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = node;
        node -> next = nullptr;
    }
    void pop_front() {
        auto* temp = head;
        head = head->next;
        delete temp;
    }
    void pop_back() {
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
        }
        else {
            auto* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = nullptr;
        }
    }
};

#endif