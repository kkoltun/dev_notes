//
// Created by kkoltun on 06.02.19.
//

#include"gtest/gtest.h"
#include "../../src/structures/DoublyLinkedList.h"

TEST(DoublyLinkedListTest, headAndInsertTest) {
    // given
    auto node = Node<int>(nullptr);

    auto list = DoublyLinkedList<int>();

    // when
    list.insert(&node);

    // then
    EXPECT_EQ(&node, list.head);
}

TEST(DoublyLinkedListTest, searchTestElementFound) {
    // given
    int value1 = 1;
    auto node1 = Node<int>(&value1);
    int value2 = 2;
    auto node2 = Node<int>(&value2);
    int value3 = 3;
    auto node3 = Node<int>(&value3);

    auto expectedFoundNode = &node2;

    auto list = DoublyLinkedList<int>();

    // when
    list.insert(&node1);
    list.insert(&node2);
    list.insert(&node3);

    auto actualFoundNode = list.search(value2);

    // then
    EXPECT_EQ(expectedFoundNode, actualFoundNode);
}

TEST(DoublyLinkedListTest, searchTestElementNotFound) {
    // given
    int absentValue = 4;

    int value1 = 1;
    auto node1 = Node<int>(&value1);
    int value2 = 2;
    auto node2 = Node<int>(&value2);
    int value3 = 3;
    auto node3 = Node<int>(&value3);

    auto list = DoublyLinkedList<int>();

    // when
    list.insert(&node1);
    list.insert(&node2);
    list.insert(&node3);

    auto actualFoundNode = list.search(absentValue);

    // then
    EXPECT_EQ(nullptr, actualFoundNode);
}

TEST(DoublyLinkedListTest, removeTestHeadElement) {
    // given
    auto n1 = Node<int>(nullptr);
    auto n2 = Node<int>(nullptr);
    auto n3 = Node<int>(nullptr);

    auto list = DoublyLinkedList<int>();

    // when
    list.insert(&n1);
    list.insert(&n2);
    list.insert(&n3);

    list.remove(&n3);

    // then
    EXPECT_EQ(&n2, list.head);
    EXPECT_EQ(nullptr, n2.prev);
}

TEST(DoublyLinkedListTest, removeTestMiddleElement) {
    // given
    auto n1 = Node<int>(nullptr);
    auto n2 = Node<int>(nullptr);
    auto n3 = Node<int>(nullptr);

    auto list = DoublyLinkedList<int>();

    // when
    list.insert(&n1);
    list.insert(&n2);
    list.insert(&n3);

    list.remove(&n2);

    // then
    EXPECT_EQ(&n1, n3.next);
    EXPECT_EQ(&n3, n1.prev);
}

TEST(DoublyLinkedListTest, removeTestTailElement) {
    // given
    auto n1 = Node<int>(nullptr);
    auto n2 = Node<int>(nullptr);
    auto n3 = Node<int>(nullptr);

    auto list = DoublyLinkedList<int>();

    // when
    list.insert(&n1);
    list.insert(&n2);
    list.insert(&n3);

    list.remove(&n1);

    // then
    EXPECT_EQ(nullptr, n2.next);
}

TEST(DoublyLinkedListTest, defaultDoublyLinkedListTest) {
    // given
    auto n1 = Node<int>(nullptr);
    auto n2 = Node<int>(nullptr);
    auto n3 = Node<int>(nullptr);

    auto list = DoublyLinkedList<int>();

    // when
    list.insert(&n1);
    list.insert(&n2);
    list.insert(&n3);

    // then
    auto currentNode = list.head;
    EXPECT_EQ(nullptr, currentNode->prev);
    EXPECT_EQ(&n3, currentNode);
    EXPECT_EQ(&n2, currentNode->next);

    currentNode = currentNode->next;
    EXPECT_EQ(&n3, currentNode->prev);
    EXPECT_EQ(&n2, currentNode);
    EXPECT_EQ(&n1, currentNode->next);

    currentNode = currentNode->next;
    EXPECT_EQ(&n2, currentNode->prev);
    EXPECT_EQ(&n1, currentNode);
    EXPECT_EQ(nullptr, currentNode->next);
}
