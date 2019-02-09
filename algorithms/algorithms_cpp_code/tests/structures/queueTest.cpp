//
// Created by kkoltun on 06.02.19.
//

#include"gtest/gtest.h"
#include "../../src/structures/Queue.h"

TEST(QueueTest, defaultQueueTest) {
    // given
    unsigned size = 5;
    std::vector<int> toEnqueueFirst{4, 3, 2, 5, 6};
    std::vector<int> toEnqueueSecond{1, 3, 3, 2, 1};
    std::vector<int> expectedDequeued{4, 3, 2, 5, 6, 1, 3, 3, 2, 1};
    std::vector<int> actualDequeued{};

    Queue queue = Queue(size);

    // when
    // perform more operations than queue size to force circularity
    for (int &i : toEnqueueFirst) {
        queue.enqueue(i);
    }

    for (int i = 0; i < size; ++i) {
        actualDequeued.push_back(queue.dequeue());
    }

    for (int &i : toEnqueueSecond) {
        queue.enqueue(i);
    }

    for (int i = 0; i < size; ++i) {
        actualDequeued.push_back(queue.dequeue());
    }

    // then
    EXPECT_EQ(expectedDequeued, actualDequeued);
}