//
// Created by kkoltun on 01.02.19.
//

#ifndef ALGORITHMS_CPP_CODE_FINDMAXSUBARRAY_H
#define ALGORITHMS_CPP_CODE_FINDMAXSUBARRAY_H

#include <vector>

struct MaxSubarrayResult {
    int i;
    int j;
    int sum;
};

MaxSubarrayResult findMaxCrossingSubarray(std::vector<int>& array, int low, int high, int mid);
MaxSubarrayResult findMaxSubarray(std::vector<int>& array, int low, int high);

#endif //ALGORITHMS_CPP_CODE_FINDMAXSUBARRAY_H
