#include <vector>

#include "gtest/gtest.h"
#include "../../src/sorting/heapSort.h"

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

TEST(HeapSortTest, BuildMaxHeapTest) {
    // given
    std::vector<int> actual{5, 2, 4, 5, 1, 3, 6, 8};
    std::vector<int> expected{8, 5, 6, 5, 1, 3, 4, 2};

    // when
    buildMaxHeap(actual);

    // then
    EXPECT_EQ(expected, actual);
}

TEST(HeapSortTest, DefaultHeapSortTest) {
    // given
    std::vector<int> actual{2, 6, 1, 2, 3, 13, 46, 1, 35, 7};
    std::vector<int> expected{1, 1, 2, 2, 3, 6, 7, 13, 35, 46};

    // when
    heapSort(actual);

    // then
    EXPECT_EQ(expected, actual);
}

TEST(HeapSortTest, HeapExtactMaxTest) {
    // given
    Heap actual({8, 5, 6, 5, 1, 3});
    int expectedMax = 8;
    std::vector<int> expectedAfterExtract{6, 5, 3, 5, 1};

    // when
    int actualMax = heapExtractMax(actual);

    EXPECT_EQ(expectedMax, actualMax);
    EXPECT_EQ(expectedAfterExtract, actual.getArray());
}