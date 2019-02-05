//
// Created by kkoltun on 05.02.19.
//

#include "gtest/gtest.h"
#include "../../src/sorting/bucketSort.h"

TEST(BucketSortTest, defaultBucketSortTest) {
    // given
    std::vector<float> actual{0.19, 0.3, 0.1, 0.25, 0.9, 0.85};
    std::vector<float> expected{0.1, 0.19, 0.25, 0.3, 0.85, 0.9};

    // when
    bucketSort(actual);

    // then
    EXPECT_EQ(expected, actual);
}