//
// Created by kkoltun on 06.02.19.
//

#include <stdexcept>

#include "Queue.h"

Queue::Queue(unsigned size) {
    // allocate one element more, tail must point to empty space
    this->size = size + 1;
    this->array = new int[size + 1];
}

bool Queue::empty() {
    return head == tail;
}

bool Queue::full() {
    return tail == size - 1
           ? head == 0
           : head == tail + 1;
}

void Queue::enqueue(int element) {
    if (this->full()) {
        throw std::runtime_error("Queue overflow");
    }

    array[tail] = element;

    if (tail == size - 1) {
        tail = 0;
    } else {
        ++tail;
    }
}

int Queue::dequeue() {
    if (this->empty()) {
        throw std::runtime_error("Queue underflow");
    }

    int element = array[head];

    if (head == size - 1) {
        head = 0;
    } else {
        ++head;
    }

    return element;
}
