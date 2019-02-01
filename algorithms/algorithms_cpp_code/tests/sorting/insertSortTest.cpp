#include <iostream>
#include <vector>

#include "gtest/gtest.h"
#include "../../src/sorting/insertSort.h"

TEST(InsertSortTest, NoElementsTest) {
    // given
    std::vector<int> unsorted{1};
    std::vector<int> expected{1};

    // when
    std::vector<int> actual = insertSort(unsorted);

    // then
    EXPECT_EQ(expected, actual);
}

TEST(InsertSortTest, OneElementTest) {
    // given
    std::vector<int> unsorted{1};
    std::vector<int> expected{1};

    // when
    std::vector<int> actual = insertSort(unsorted);

    // then
    EXPECT_EQ(expected, actual);
}

TEST(InsertSortTest, DefaultTest) {
// given
std::vector<int> unsorted{1, 4, 3, 2};
std::vector<int> expected{1, 2, 3, 4};

// when
std::vector<int> actual = insertSort(unsorted);

// then
EXPECT_EQ(expected, actual);
}