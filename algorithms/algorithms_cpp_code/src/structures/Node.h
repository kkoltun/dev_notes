//
// Created by kkoltun on 06.02.19.
//

#ifndef ALGORITHMS_CPP_CODE_NODE_H
#define ALGORITHMS_CPP_CODE_NODE_H

template <typename T>
struct Node {
    Node *prev;
    Node *next;
    T *element;

    explicit Node(T *element) : element(element) {}
};


#endif //ALGORITHMS_CPP_CODE_NODE_H
