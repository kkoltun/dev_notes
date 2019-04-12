//
// Created by kkoltun on 12.04.19.
//

#include "gtest/gtest.h"
#include "../../src/graphs/dfs.h"

TEST(dfsTest, defaultDfsTest) {
    // given
    auto v1 = new DfsVertex();
    v1->name = "u";
    auto v2 = new DfsVertex();
    v2->name = "v";
    auto v3 = new DfsVertex();
    v3->name = "y";
    auto v4 = new DfsVertex();
    v4->name = "x";
    auto v5 = new DfsVertex();
    v5->name = "w";
    auto v6 = new DfsVertex();
    v6->name = "z";

    std::vector<DfsVertex *> v1adjList = {v2, v4};
    std::vector<DfsVertex *> v2adjList = {v3};
    std::vector<DfsVertex *> v3adjList = {v4};
    std::vector<DfsVertex *> v4adjList = {v2};
    std::vector<DfsVertex *> v5adjList = {v3, v6};
    std::vector<DfsVertex *> v6adjList = {v6};

    auto graph = std::map<DfsVertex *, std::vector<DfsVertex *>>();
    graph[v1] = v1adjList;
    graph[v2] = v2adjList;
    graph[v3] = v3adjList;
    graph[v4] = v4adjList;
    graph[v5] = v5adjList;
    graph[v6] = v6adjList;

    // when
    dfs(graph);

    // then
    EXPECT_EQ(Color::BLACK, v1->color);
    EXPECT_EQ(1, v1->discoveredTimestamp);
    EXPECT_EQ(8, v1->exploredTimestamp);

    EXPECT_EQ(Color::BLACK, v2->color);
    EXPECT_EQ(2, v2->discoveredTimestamp);
    EXPECT_EQ(7, v2->exploredTimestamp);

    EXPECT_EQ(Color::BLACK, v3->color);
    EXPECT_EQ(3, v3->discoveredTimestamp);
    EXPECT_EQ(6, v3->exploredTimestamp);

    EXPECT_EQ(Color::BLACK, v4->color);
    EXPECT_EQ(4, v4->discoveredTimestamp);
    EXPECT_EQ(5, v4->exploredTimestamp);

    EXPECT_EQ(Color::BLACK, v5->color);
    EXPECT_EQ(9, v5->discoveredTimestamp);
    EXPECT_EQ(12, v5->exploredTimestamp);

    EXPECT_EQ(Color::BLACK, v6->color);
    EXPECT_EQ(10, v6->discoveredTimestamp);
    EXPECT_EQ(11, v6->exploredTimestamp);
}