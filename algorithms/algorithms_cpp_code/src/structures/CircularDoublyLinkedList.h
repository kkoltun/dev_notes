//
// Created by kkoltun on 06.02.19.
//

#ifndef ALGORITHMS_CPP_CODE_CIRCULARLINKEDLIST_H
#define ALGORITHMS_CPP_CODE_CIRCULARLINKEDLIST_H

#include "Node.h"

template<typename T>
struct CircularDoublyLinkedList {
    Node<T> *head = nullptr;

    void insert(Node<T> *node) {
        if (head != nullptr) {
            auto lastElement = head->prev;

            // correct new head links
            node->next = head;
            node->prev = lastElement;

            // correct old head link
            head->prev = node;

            // correct last element link
            lastElement->next = node;
        } else {
            // one element list - head links with itself
            node->next = node;
            node->prev = node;
        }

        // set new head
        head = node;
    }

    Node<T> *search(T value) {
        if (head == nullptr) {
            return nullptr;
        }

        if (*(head->element) == value) {
            return head;
        } else {
            auto currentNode = head->next;

            while (currentNode != head) {
                if (*(currentNode->element) == value) {
                    return currentNode;
                }
                currentNode = currentNode->next;
            }
        }

        return nullptr;
    }

    void remove(Node<T> *node) {
        if (node->prev == node) {
            head = nullptr;
        } else {
            Node<T> *nodePrev = node->prev;
            Node<T> *nodeNext = node->next;

            nodePrev->next = nodeNext;
            nodeNext->prev = nodePrev;

            if (node == head) {
                head = nodeNext;
            }
        }
    }
};


#endif //ALGORITHMS_CPP_CODE_CIRCULARLINKEDLIST_H
