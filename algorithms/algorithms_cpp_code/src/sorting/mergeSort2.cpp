//
// Created by kkoltun on 01.02.19.
//

#include <algorithm>
#include <limits>

#include "mergeSort2.h"

void merge2(std::vector<int> &list, int p, int q, int r) {
    std::vector<int> left = std::vector<int>();
    std::copy(list.begin() + p, list.begin() + r, std::back_inserter(left));

    std::vector<int> right = std::vector<int>();
    std::copy(list.begin() + r, list.begin() + q, std::back_inserter(right));

    left.push_back(std::numeric_limits<int>::max());
    right.push_back(std::numeric_limits<int>::max());

    int leftIdx = 0;
    int rightIdx = 0;
    int i = p;

    while (i < q) {
        if (left[leftIdx] < right[rightIdx]) {
            list[i] = left[leftIdx];
            ++leftIdx;
        } else {
            list[i] = right[rightIdx];
            ++rightIdx;
        }
        ++i;
    }
}


// sorts array from p to q not inclusively (for array 0..7 q = 8)
void mergeSort2(std::vector<int> &list, int p, int q) {
    if (p < q) {
        int r = (p + q)/2;
        mergeSort2(list, p, r);
        mergeSort2(list, p, r);
        merge2(list, p, q, r);
    }
}
