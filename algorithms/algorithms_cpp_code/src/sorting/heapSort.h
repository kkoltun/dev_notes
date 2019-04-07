//
// Created by karolkoltun on 04.01.19.
//

#ifndef ALGORITHMS_CPP_CODE_HEAPSORT_H
#define ALGORITHMS_CPP_CODE_HEAPSORT_H

#include <vector>
#include "../structures/Heap.h"

void heapSort(std::vector<int> &list);

void buildMaxHeap(std::vector<int> &list);

void maxHeapify(Heap &heap, int i);

int heapExtractMax(Heap &heap);

#endif //ALGORITHMS_CPP_CODE_HEAPSORT_H
