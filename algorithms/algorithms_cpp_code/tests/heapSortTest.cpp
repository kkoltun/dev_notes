#include <iostream>
#include <vector>

#include "gtest/gtest.h"
#include "../src/sorting/heapSort.h"

TEST(HeapSortTest, MaxHeapifyTest) {
    // given
    Heap actual = Heap({16, 4, 10, 14, 7, 9, 3, 2, 8, 1});
    int misplacedElementIdx = 1;

    std::vector<int> expected{16, 14, 10, 8, 7, 9, 3, 2, 4, 1};

    // when
    maxHeapify(actual, misplacedElementIdx);

    // then
    EXPECT_EQ(expected, actual.getArray());
}

TEST(HeapSortTest, DefaultHeapSortTest) {
    // given
    std::vector<int> actual{5, 2, 4, 5, 1, 3, 6, 8};
    std::vector<int> expected{1, 2, 3, 4, 5, 5, 6, 8};

    // when
    heapSort(actual);

    // then
    EXPECT_EQ(expected, actual);
}