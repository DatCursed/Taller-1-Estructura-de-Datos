#ifndef QUEUE_H
#define QUEUE_H

#include "Linkedlist.hpp"

template <typename T>
class Queue {
private:
    LinkedList<T> list;

public:
    void enqueue(T value) {
        list.pushBack(value);
    }

    T dequeue() {
        return list.popFront();
    }

    T peek() const {
        return list.peekFront();
    }

    T peekAt(int index) const {
        return list.get(index);
    }

    void removeAt(int index) {
        list.removeAt(index);
    }

    bool isEmpty() const {
        return list.isEmpty();
    }

    int getSize() const {
        return list.getSize();
    }

    typename LinkedList<T>::Node* getHead() const {
        return list.getHead();
    }

    void clear() {
        list.clear();
    }
};

#endif