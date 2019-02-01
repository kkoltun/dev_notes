#include <iostream>
#include <vector>

#include "gtest/gtest.h"
#include "../../src/sorting/mergeSort.h"
#include "../../src/sorting/mergeSort2.h"

TEST(MergeTest, DefaultMergeTest) {
    // given
    std::vector<int> actual{5, 2, 4, 5, 1, 3, 6, 8};
    int left_unsorted_start_idx = 1;
    int left_unsorted_end_idx = 3;
    int right_unsorted_end_idx = 7;

    std::vector<int> expected{5, 1, 2, 3, 4, 5, 6, 8};

    // when
    merge(actual, left_unsorted_start_idx, left_unsorted_end_idx, right_unsorted_end_idx);

    // then
    EXPECT_EQ(expected, actual);
}

TEST(MergeSortTest, DefaultMergeSortTest) {
    // given
    std::vector<int> actual{5, 2, 4, 5, 1, 3, 6, 8};

    std::vector<int> expected{1, 2, 3, 4, 5, 5, 6, 8};

    // when
    mergeSort(actual);

    // then
    EXPECT_EQ(expected, actual);
}

TEST(MergeTest2, DefaultMergeTest) {
    // given
    std::vector<int> actual{5, 2, 4, 5, 1, 3, 6, 8};
    int left_unsorted_start_idx = 1;
    int right_unsorted_start_idx = 4;
    int right_unsorted_end_idx = 7;

    std::vector<int> expected{5, 1, 2, 3, 4, 5, 6, 8};

    // when
    merge2(actual, left_unsorted_start_idx, right_unsorted_end_idx, right_unsorted_start_idx);

    // then
    EXPECT_EQ(expected, actual);
}

TEST(MergeSortTest2, DefaultMergeSortTest) {
    // given
    std::vector<int> actual{5, 2, 4, 5, 1, 3, 6, 8};

    std::vector<int> expected{1, 2, 3, 4, 5, 5, 6, 8};

    // when
    mergeSort2(actual, 0, actual.size());

    // then
    EXPECT_EQ(expected, actual);
}