//
// Created by kkoltun on 01.02.19.
//

#include "gtest/gtest.h"
#include "../../src/sorting/quickSort.h"

TEST(QuickSortTest, PartitionFullArrayTest) {
    // given
    std::vector<int> actual = {4, 1, 2, 5, 7, 1, 5};
    std::vector<int> expected = {4, 1, 2, 1, 5, 5, 7};

    long p = 0;
    long r = actual.size() - 1;


    // when
    partition(actual, p, r);

    // then
    EXPECT_EQ(expected, actual);
}

TEST(QuickSortTest, DefaultQuicksortTest) {
    // given
    std::vector<int> actual = {2, 1, 3, 8, 7, 5, 6, 4};
    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8};

    long p = 0;
    long r = actual.size() - 1;


    // when
    quickSort(actual, p, r);

    // then
    EXPECT_EQ(expected, actual);
}