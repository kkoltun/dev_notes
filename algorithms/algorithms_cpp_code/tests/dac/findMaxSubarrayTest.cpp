//
// Created by kkoltun on 01.02.19.
//

#include <vector>

#include "gtest/gtest.h"
#include "../../src/dac/findMaxSubarray.h"

TEST(FindMaxSubarrayTest, findMaxCrossingSubarrayTest) {
    // given
    std::vector<int> array{13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, 25};
    int low = 2;
    int mid = 5;
    int high = 10;

    MaxSubarrayResult expected = {3, 10, 21};

    // when
    MaxSubarrayResult actual = findMaxCrossingSubarray(array, low, high, mid);

    // then
    EXPECT_EQ(expected.i, actual.i);
    EXPECT_EQ(expected.j, actual.j);
    EXPECT_EQ(expected.sum, actual.sum);
}

TEST(FindMaxSubarrayTest, defaultFindMaxSubarrayTest) {
    // given
    std::vector<int> array{13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    int low = 0;
    int high = array.size() - 1;

    MaxSubarrayResult expected = {7, 10, 43};

    // when
    MaxSubarrayResult actual = findMaxSubarray(array, low, high);

    // then
    EXPECT_EQ(expected.i, actual.i);
    EXPECT_EQ(expected.j, actual.j);
    EXPECT_EQ(expected.sum, actual.sum);
}