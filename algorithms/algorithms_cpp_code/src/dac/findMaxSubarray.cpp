//
// Created by kkoltun on 01.02.19.
//

#include <limits>

#include "findMaxSubarray.h"

MaxSubarrayResult findMaxCrossingSubarray(std::vector<int>& array, int low, int high, int mid) {

    int actualSum = 0;

    int leftMaxSum = std::numeric_limits<int>::min();
    int leftMaxIdx = mid;
    for (int i = mid; i >= low; --i) {
        actualSum += array[i];

        if (actualSum > leftMaxSum) {
            leftMaxSum = actualSum;
            leftMaxIdx = i;
        }
    }

    actualSum = 0;
    int rightMaxSum = std::numeric_limits<int>::min();
    int rightMaxIdx = mid + 1;
    for (int i = mid + 1; i <= high; ++i) {
        actualSum += array[i];

        if (actualSum > rightMaxSum) {
            rightMaxSum = actualSum;
            rightMaxIdx = i;
        }
    }

    return {leftMaxIdx, rightMaxIdx, leftMaxSum + rightMaxSum};
}

MaxSubarrayResult findMaxSubarray(std::vector<int>& array, int low, int high) {
    if (low == high)
        return {low, high, array[low]};

    int mid = (high + low)/2;

    MaxSubarrayResult left = findMaxSubarray(array, low, mid);
    MaxSubarrayResult right = findMaxSubarray(array, mid + 1, high);
    MaxSubarrayResult crossing = findMaxCrossingSubarray(array, low, high, mid);

    MaxSubarrayResult maxLeftOrRight = left.sum > right.sum ? left : right;
    return crossing.sum > maxLeftOrRight.sum ? crossing : maxLeftOrRight;
}