//
// Created by karolkoltun on 04.01.19.
//

#include <iostream>

#include "heapSort.h"
#include "../structures/Heap.h"

void heapSort(std::vector<int> &list) {
    buildMaxHeap(list);

    Heap heap = Heap(list);

    for (int i = heap.getSize() - 1; i >= 1; --i) {
        int currentElementValue = heap[i];
        heap.getArray()[i] = heap[0];
        heap.getArray()[0] = currentElementValue;

        heap.shrinkBy(1);
        maxHeapify(heap, 0);
    }

    list = heap.getArray();
}

void buildMaxHeap(std::vector<int> &list) {
    Heap heap = Heap(list);
    for (int i = heap.getSize() - 1; i >= 0; --i) {
        maxHeapify(heap, i);
    }
    list = heap.getArray();
}

bool isMaxHeap(Heap &heap, int i) {
    bool maxHeap = true;
    if (heap.hasLeft(i)) {
        maxHeap = heap[i] >= heap.left(i);
    }
    if (maxHeap &&
    heap.hasRight(i)) {
        maxHeap = heap[i] >= heap.right(i);
    }
    return maxHeap;
}

// assumes binary trees rooted at left(i) and right(i) are max-heaps but heap[i] might be smaller than its children
void maxHeapify(Heap &heap, int i) {
    if (isMaxHeap(heap, i) || i >= heap.getSize() || !heap.hasLeft(i)) {
        return;
    }
    int largestIdx = i;

    if (heap.left(i) > heap[largestIdx]) {
        largestIdx = heap.leftIdx(i);
    }

    if (heap.hasRight(i) && (heap.right(i) > heap[largestIdx])) {
        largestIdx = heap.rightIdx(i);
    }

    int largestVal = heap[largestIdx];
    heap.set(largestIdx, heap[i]);
    heap.set(i, largestVal);

    maxHeapify(heap, largestIdx);
}

int heapExtractMax(Heap &heap) {
    int max = heap[0];

    heap.set(0, heap[heap.getSize() - 1]);
    heap.getArray().pop_back();
    heap.shrinkBy(1);
    maxHeapify(heap, 0);

    return max;
}
