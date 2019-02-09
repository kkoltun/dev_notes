//
// Created by kkoltun on 06.02.19.
//

#ifndef ALGORITHMS_CPP_CODE_LINKEDLIST_H
#define ALGORITHMS_CPP_CODE_LINKEDLIST_H


#include "Node.h"

// strict implementation for CLRS book
template<typename T>
class DoublyLinkedList {
public:
    Node<T> *head = nullptr;

    void insert(Node<T> *node) {
        node->next = head;
        node->prev = nullptr;

        if (head != nullptr) {
            head->prev = node;
        }

        head = node;
    }

    Node<T> *search(T value) {
        Node<T> *node = head;

        while (node != nullptr && *(node->element) != value) {
            node = node->next;
        }

        return node;
    }

    void remove(Node<T> *node) {
        Node<T> *nodePrev = node->prev;
        Node<T> *nodeNext = node->next;

        if (nodePrev != nullptr) {
            nodePrev->next = nodeNext;
        } else {
            head = nodeNext;
        }

        if (nodeNext != nullptr) {
            nodeNext->prev = nodePrev;
        } else {
            if (nodePrev != nullptr) {
                nodePrev->next = nullptr;
            }
        }
    }
};


#endif //ALGORITHMS_CPP_CODE_LINKEDLIST_H
