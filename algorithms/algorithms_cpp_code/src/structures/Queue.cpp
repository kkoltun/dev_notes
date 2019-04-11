//
// Created by kkoltun on 06.02.19.
//

#include <stdexcept>

#include "Queue.h"

Queue::Queue(unsigned size) {
    this->size = size + 1;
    this->array = new int[this->size];
    this->head = 0;
    this->tail = 0;
}

bool Queue::empty() {
    return head == tail;
}

bool Queue::full() {
    return head == tail + 1;
}

void Queue::enqueue(int value) {
    if (full()) {
        throw std::overflow_error("Queue is full");
    }
    array[tail] = value;

    if (tail < size - 1) {
        ++tail;
    } else {
        tail = 0;
    }
}

int Queue::dequeue() {
    if (empty()) {
        throw std::underflow_error("Queue is empty");
    }

    int value = array[head];

    if (head < size - 1) {
        ++head;
    } else {
        head = 0;
    }

    return value;
}
