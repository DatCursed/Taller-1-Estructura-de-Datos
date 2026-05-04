#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdexcept>
using namespace std;

template <typename T>
class LinkedList {
public:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(T value) : data(value), next(nullptr), prev(nullptr) {}
    };

private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~LinkedList() {
        clear();
    }
    
    void pushBack(T value) {
        Node* node = new Node(value);
        if (tail == nullptr) {
            head = tail = node;
        } else {
            node->prev = tail;
            tail->next = node;
            tail = node;
        }
        size++;
    }

    void pushFront(T value) {
        Node* node = new Node(value);
        if (head == nullptr) {
            head = tail = node;
        } else {
            node->next = head;
            head->prev = node;
            head = node;
        }
        size++;
    }

    T popFront() {
        if (isEmpty()) throw runtime_error("List is empty");
        Node* temp = head;
        T value = temp->data;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        size--;
        return value;
    }

    T popBack() {
        if (isEmpty()) throw runtime_error("List is empty");
        Node* temp = tail;
        T value = temp->data;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        size--;
        return value;
    }

    void removeAt(int index) {
        if (index < 0 || index >= size) throw out_of_range("Index out of range");
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        if (current->prev != nullptr) {
            current->prev->next = current->next;
        } else {
            head = current->next;
        }
        if (current->next != nullptr) {
            current->next->prev = current->prev;
        } else {
            tail = current->prev;
        }
        delete current;
        size--;
    }

    T get(int index) const {
        if (index < 0 || index >= size) throw out_of_range("Index out of range");
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    T peekFront() const {
        if (isEmpty()) throw runtime_error("List is empty");
        return head->data;
    }

    T peekBack() const {
        if (isEmpty()) throw runtime_error("List is empty");
        return tail->data;
    }

    Node* getHead() const {
        return head;
    }

    bool isEmpty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }

    void clear() {
        while (!isEmpty()) {
            popFront();
        }
    }
};

#endif

