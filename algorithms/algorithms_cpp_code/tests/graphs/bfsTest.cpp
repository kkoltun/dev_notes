//
// Created by kkoltun on 11.04.19.
//

#include "gtest/gtest.h"
#include "../../src/graphs/bfs.h"

TEST(bfsTest, defaultBfsTest) {
// given
    auto v1 = new Vertex();
    auto v2 = new Vertex();
    auto v3 = new Vertex();
    auto v4 = new Vertex();
    auto v5 = new Vertex();
    auto v6 = new Vertex();
    auto v7 = new Vertex();

    std::vector<Vertex *> v1adjList = {v2, v3};
    std::vector<Vertex *> v2adjList = {v1, v3};
    std::vector<Vertex *> v3adjList = {v1, v2, v4, v5};
    std::vector<Vertex *> v4adjList = {v3, v6};
    std::vector<Vertex *> v5adjList = {v3, v6, v7};
    std::vector<Vertex *> v6adjList = {v4, v5};
    std::vector<Vertex *> v7adjList = {v5};

    auto graph = std::map<Vertex *, std::vector<Vertex *>>();
    graph[v1] = v1adjList;
    graph[v2] = v2adjList;
    graph[v3] = v3adjList;
    graph[v4] = v4adjList;
    graph[v5] = v5adjList;
    graph[v6] = v6adjList;
    graph[v7] = v7adjList;

    // when
    bfs(graph, v2);

    // then
    EXPECT_EQ(Color::BLACK, v1->color);
    EXPECT_EQ(v2, v1->predecessor);
    EXPECT_EQ(1, v1->degree);

    EXPECT_EQ(Color::BLACK, v2->color);
    EXPECT_EQ(nullptr, v2->predecessor);
    EXPECT_EQ(0, v2->degree);

    EXPECT_EQ(Color::BLACK, v3->color);
    EXPECT_EQ(v2, v3->predecessor);
    EXPECT_EQ(1, v3->degree);

    EXPECT_EQ(Color::BLACK, v4->color);
    EXPECT_EQ(v3, v4->predecessor);
    EXPECT_EQ(2, v4->degree);

    EXPECT_EQ(Color::BLACK, v5->color);
    EXPECT_EQ(v3, v5->predecessor);
    EXPECT_EQ(2, v5->degree);

    EXPECT_EQ(Color::BLACK, v6->color);
    EXPECT_EQ(v4, v6->predecessor);
    EXPECT_EQ(3, v6->degree);

    EXPECT_EQ(Color::BLACK, v7->color);
    EXPECT_EQ(v5, v7->predecessor);
    EXPECT_EQ(3, v7->degree);
}