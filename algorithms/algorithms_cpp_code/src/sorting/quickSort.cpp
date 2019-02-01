//
// Created by kkoltun on 01.02.19.
//

#include "quickSort.h"

void quickSort(std::vector<int> &array, long p, long r) {
    if (p < r) {
        long q = partition(array, p, r);
        quickSort(array, p, q - 1);
        quickSort(array, q + 1, r);
    }
}

void exchange(std::vector<int> &array, long i, long j) {
    int iVal = array[i];
    array[i] = array[j];
    array[j] = iVal;
}

long partition(std::vector<int> &array, long p, long r) {
    int pivotVal = array[r];
    long leftBound = p - 1;

    for (long i = p; i < r; ++i) {
        if (pivotVal > array[i]) {
            ++leftBound;
            exchange(array, leftBound, i);
        }
    }
    exchange(array, r, leftBound + 1);

    return leftBound + 1;
}