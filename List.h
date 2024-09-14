#ifndef LIST_H
#define LIST_H
#include <stdexcept>
#include <iostream>

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

    ~List() {
        clear();
    }

    T front() const {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        return head->data;
    }

    T back() const {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }
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

    T pop_front() {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }

        Node<T> *next = head->next;
        T data = head->data;
        delete head;
        head = next;

        if (head == nullptr) {
            tail = nullptr;
        } else {
            head->prev = nullptr;
        }
        return data;
    }

    T pop_back() {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }

        T data = tail->data;
        if (tail->prev == nullptr) {
            delete tail;
            tail = nullptr;
            head = nullptr;
        } else {
            Node<T> *prev = tail->prev;
            delete tail;
            tail = prev;
            tail->next = nullptr;
        }
        return data;
    }

    void insert(const T &data, const size_t position) {
        if (position == 0) {
            push_front(data);
            return;
        }

        Node<T> *temp = head;
        for (size_t i = 0; temp != nullptr && i < position - 1; ++i) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            throw std::out_of_range("Index out of range");
        }

        auto node = new Node<T>(data);
        Node<T> *next = temp->next;

        node->next = next;
        node->prev = temp;
        temp->next = node;

        if (next == nullptr) {
            next->prev = node;
        } else {
            tail = node;
        }
    }

    void remove(const size_t position) {
        if (position == 0) {
            pop_front();
            return;
        }

        Node<T> *temp = head;
        for (size_t i = 0; temp != nullptr && i < position; ++i) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            throw std::out_of_range("Index out of range");
        }

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
    }

    T &operator[](const size_t index) const {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        Node<T> *temp = head;
        for (size_t i = 0; i < index; ++i) {
            if (temp == nullptr) {
                throw std::out_of_range("Index out of range");
            }
            temp = temp->next;
        }
        return temp->data;
    }

    [[nodiscard]] bool empty() const {
        return head == nullptr;
    }

    [[nodiscard]] size_t size() const {
        size_t size = 0;
        Node<T> *temp = head;
        while (temp != nullptr) {
            ++size;
            temp = temp->next;
        }
        return size;
    }

    void clear() {
        while (head != nullptr) {
            const Node<T> *temp = head;
            head = head->next;
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
    }

    void reverse() {
        if (head == nullptr) {
            return;
        }

        Node<T> *prev = nullptr;
        Node<T> *current = head;
        tail = head;

        while (current != nullptr) {
            Node<T> *next = current->next;
            current->next = prev;
            current->prev = next;
            prev = current;
            current = next;
        }
        head = prev;
    }

    static void printList(const List &list) {
        for (Node<T> *temp = head; temp != nullptr; temp = temp->next) {
            std::cout << temp->data << ' ';
        }
        std::cout << '\n';
    }
};

#endif
