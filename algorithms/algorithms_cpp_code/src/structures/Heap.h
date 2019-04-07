//
// Created by karolkoltun on 04.01.19.
//

#ifndef ALGORITHMS_CPP_CODE_HEAP_H
#define ALGORITHMS_CPP_CODE_HEAP_H

#include <vector>

class Heap {
private:
    std::vector<int> array;
    int size;

public:

    explicit Heap(std::vector<int> array);

    int parent(int) const;
    int left(int) const;
    int right(int) const;

    bool hasLeft(int) const;
    bool hasRight(int) const;

    int parentIdx(int) const;
    int leftIdx(int) const;
    int rightIdx(int) const;

    int getSize() const;
    void shrinkBy(int);

    int operator[](int) const;

    void set(int, int);

    std::vector<int>& getArray();
};


#endif //ALGORITHMS_CPP_CODE_HEAP_H
