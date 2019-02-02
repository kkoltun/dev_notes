//
// Created by kkoltun on 02.02.19.
//

#include <vector>

#include "gtest/gtest.h"
#include "../../src/sorting/countingSort.h"

TEST(CountingSortTest, DefaultCountingSortTest) {
    // given
    std::vector<unsigned> unsorted = {0, 5, 4, 3, 1, 1, 3, 3, 5, 0};
    unsigned maxValue = 5;

    std::vector<unsigned> expected{0, 0, 1, 1, 3, 3, 3, 4, 5, 5};

    // when
    std::vector<unsigned> actual = countingSortSimple(unsorted, maxValue);

    // then
    EXPECT_EQ(expected, actual);
}

TEST(CountingSortTest, DefaultCountingSortTest2) {
    // given
    std::vector<unsigned> unsorted = {0, 5, 4, 3, 1, 1, 3, 3, 5, 0};
    unsigned maxValue = 5;

    std::vector<unsigned> expected{0, 0, 1, 1, 3, 3, 3, 4, 5, 5};

    // when
    std::vector<unsigned> actual = countingSort(unsorted, maxValue);

    // then
    EXPECT_EQ(expected, actual);
}