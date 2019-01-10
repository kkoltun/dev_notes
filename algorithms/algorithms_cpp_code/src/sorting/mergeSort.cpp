#include <climits>
#include <iostream>
#include <vector>

#include "mergeSort.h"

void mergeSort(std::vector<int>& list, int p, int r) {
    if (p < r) {
        int q = (p + r)/2;

        mergeSort(list, p, q);
        mergeSort(list, q + 1, r);
        merge(list, p, q, r);
    }
}

void mergeSort(std::vector<int>& list) {
    mergeSort(list, 0, list.size() - 1);
}

// p <= q < r
// list[p, q] and list[q+1, r] are sorted
void merge(std::vector<int>& list, int p, int q, int r) {
    if (p > q || q >= r) {
        std::cout << "Given values: p=" << p << "; q=" << q << "; r=" << r << " are not correct.";
        return;
    }

    std::vector<int> left = std::vector<int>();
    std::vector<int> right = std::vector<int>();

    for (int i = p; i < q + 1; ++i) {
        left.push_back(list[i]);
    }

    for (int i = q + 1; i < r + 1; ++i) {
        right.push_back(list[i]);
    }

    left.push_back(INT_MAX);
    right.push_back(INT_MAX);

    int left_idx = 0;
    int right_idx = 0;
    int i = p;

    while (i < r + 1) {
        int left_val = left[left_idx];
        int right_val = right[right_idx];

        if (left_val < right_val) {
            list[i] = left_val;
            ++left_idx;
        } else {
            list[i] = right_val;
            ++right_idx;
        }

        ++i;
    }
}