#ifndef STACK_H
#define STACK_H

#include "Linkedlist.hpp"

template <typename T>
class Stack {
private:
    LinkedList<T> list;

public:
    void push(T value) {
        list.pushFront(value);
    }

    T pop() {
        return list.popFront();
    }

    T peek() const {
        return list.peekFront();
    }

    bool isEmpty() const {
        return list.isEmpty();
    }

    int getSize() const {
        return list.getSize();
    }

    void clear() {
        list.clear();
    }
};

#endif