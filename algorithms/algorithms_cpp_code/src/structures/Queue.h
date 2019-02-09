//
// Created by kkoltun on 06.02.19.
//

#ifndef ALGORITHMS_CPP_CODE_QUEUE_H
#define ALGORITHMS_CPP_CODE_QUEUE_H


class Queue {
private:
    unsigned head = 0;
    unsigned tail = 0;
    unsigned size;

    int* array;

public:
    Queue(unsigned);

    bool empty();

    bool full();

    void enqueue(int);

    int dequeue();
};


#endif //ALGORITHMS_CPP_CODE_QUEUE_H
