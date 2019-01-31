//
// Created by karolkoltun on 04.01.19.
//

#include <iostream>

#include "heapSort.h"
#include "Heap.h"

void heapSort(std::vector<int> &list) {
    buildMaxHeap(list);

    Heap heap = Heap(list);

    for (int i = heap.getSize() - 1; i >= 1; --i) {
        int currentElementValue = heap[i];
        heap.getArray()[i] = heap[0];
        heap.getArray()[0] = currentElementValue;

        heap.shrinkBy(1);
        maxHeapify(heap, i);
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

// assumes binary trees rooted at left(i) and right(i) are max-heaps but heap[i] might be smaller than its children
void maxHeapify(Heap &heap, int i) {
    auto isMaxHeap = [](Heap& heap, int i) -> bool { return heap[i] >= heap.left(i) && heap[i] >= heap.right(i); };

    // przerobić na skrypt rekursywny bazujący na size
    while (heap.hasLeft(i)) {
        if (isMaxHeap(heap, i)) {
            return;
        }
        int largestIdx = i;

        if (heap.left(i) > heap[largestIdx]) {
            largestIdx = heap.leftIdx(i);
        }

        if (heap.hasRight(i) && (heap.right(i) > heap[largestIdx])) {
            largestIdx = heap.rightIdx(i);
        }

        int currentLargest = heap[largestIdx];
        heap.set(largestIdx, heap[i]);
        heap.set(i, currentLargest);

        i = largestIdx;
    }
}

