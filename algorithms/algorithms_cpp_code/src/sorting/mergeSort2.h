//
// Created by kkoltun on 01.02.19.
//

#ifndef ALGORITHMS_CPP_CODE_MERGESORT2_H
#define ALGORITHMS_CPP_CODE_MERGESORT2_H

#include <vector>

void merge2(std::vector<int> &list, int p, int q, int r);

// sorts array from p to q not inclusively (for array 0..7 q = 8)
void mergeSort2(std::vector<int> &list, int p, int q);

#endif //ALGORITHMS_CPP_CODE_MERGESORT2_H
