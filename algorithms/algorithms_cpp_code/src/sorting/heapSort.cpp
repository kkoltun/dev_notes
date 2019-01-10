//
// Created by karolkoltun on 04.01.19.
//

#include <iostream>

#include "heapSort.h"
#include "Heap.h"

void heapSort(std::vector<int> &list) {
    Heap heap = Heap(list);

    std::cout << "Element 0: " << heap[0] << std::endl;
    std::cout << "Element 1: " << heap[1] << std::endl;
    std::cout << "Element 1 parent: array[" << heap.parentIdx(1) << "]=" << heap.parent(1) << std::endl;
    std::cout << "Element 1 left: array[" << heap.leftIdx(1) << "]=" << heap.left(1) << std::endl;
    std::cout << "Element 1 right: array[" << heap.rightIdx(1) << "]=" << heap.right(1) << std::endl;
}

// assumes binary trees rooted at left(i) and right(i) are max-heaps but heap[i] might be smaller than its children
void maxHeapify(Heap &heap, int i) {
    auto isMaxHeap = [](Heap& heap, int i) -> bool { return heap[i] >= heap.left(i) && heap[i] >= heap.right(i); };

    while (heap.hasLeft(i) && heap.hasRight(i)) {
        if (isMaxHeap(heap, i)) {
            return;
        }
        int largestIdx = i;

        if (heap.left(i) > heap[largestIdx]) {
            largestIdx = heap.leftIdx(i);
        }

        if (heap.right(i) > heap[largestIdx]) {
            largestIdx = heap.rightIdx(i);
        }

        int currentLargest = heap[largestIdx];
        heap.set(largestIdx, heap[i]);
        heap.set(i, currentLargest);

        i = largestIdx;
    }
}

