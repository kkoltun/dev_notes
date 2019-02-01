#include <utility>

//
// Created by karolkoltun on 04.01.19.
//

#include "Heap.h"

Heap::Heap(std::vector<int> array) {
    this->size = array.size();
    this->array = std::move(array);
}

int Heap::parent(int i) const {
    return array[this->parentIdx(i)];
}

int Heap::left(int i) const {
    return array[this->leftIdx(i)];
}

int Heap::right(int i) const {
    return array[this->rightIdx(i)];
}

bool Heap::hasLeft(int i) const {
    return this->size > leftIdx(i);
}

bool Heap::hasRight(int i) const {
    return this->size > rightIdx(i);
}

int Heap::parentIdx(int i) const {
    return (i - 1) / 2;
}

int Heap::leftIdx(int i) const {
    return 2 * i + 1;
}

int Heap::rightIdx(int i) const {
    return 2 * i + 2;
}

int Heap::getSize() const {
    return this->size;
}

void Heap::shrinkBy(int size) {
    this->size -= size;
}

int Heap::operator[](int i) const {
    return array[i];
}

void Heap::set(int idx, int value) {
    array[idx] = value;
}

std::vector<int>& Heap::getArray() {
    return this->array;
}