#ifndef FORWARDLIST_H
#define FORWARDLIST_H

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
    ForwardList():head(nullptr){}

    void push_front(T data) {
        auto* node = new Node(data);
        node->next = head;
        this->head = node;
    }

    void push_back(T data) {
        auto* node = new Node(data);
        auto* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = node;
    }

    void pop_front() {
        auto* temp = head;
        this->head = head->next;
        delete temp;
    }

    void pop_back() {
        if (head->next == nullptr) {
            delete head;
            this->head = nullptr;
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

    void insert_in_position(T data, const size_t position) {
        auto* node = new Node<T>;
        auto* temp = head;
        node->data = data;
        for (size_t i = 0; i < position - 1; i++) {
            temp = temp->next;
        }
        node->next = temp->next;
        temp->next = node;
    }
};

#endif