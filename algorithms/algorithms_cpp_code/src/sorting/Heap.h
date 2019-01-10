//
// Created by karolkoltun on 04.01.19.
//

#ifndef ALGORITHMS_CPP_CODE_HEAP_H
#define ALGORITHMS_CPP_CODE_HEAP_H

#include <vector>

class Heap {
private:
    std::vector<int> array;

public:

    explicit Heap(std::vector<int> array);

    int parent(int i) const;
    int left(int i) const;
    int right(int i) const;

    bool hasLeft(int i) const;
    bool hasRight(int i) const;

    int parentIdx(int i) const;
    int leftIdx(int i) const;
    int rightIdx(int i) const;

    int operator[](int i) const;

    void set(int idx, int value);

    std::vector<int>& getArray();
};


#endif //ALGORITHMS_CPP_CODE_HEAP_H
