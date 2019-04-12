//
// Created by kkoltun on 12.04.19.
//

#include "gtest/gtest.h"
#include "../../src/graphs/topologicalSort.h"

TEST(topologicalSortTest, defaultTopologicalSortTest) {
    // given
    auto shirt = new DfsVertex();
    shirt->name = "shirt";
    auto tie = new DfsVertex();
    tie->name = "tie";
    auto jacket = new DfsVertex();
    jacket->name = "jacket";
    auto belt = new DfsVertex();
    belt->name = "belt";
    auto watch = new DfsVertex();
    watch->name = "watch";
    auto undershorts = new DfsVertex();
    undershorts->name = "undershorts";
    auto pants = new DfsVertex();
    pants->name = "pants";
    auto shoes = new DfsVertex();
    shoes->name = "shoes";
    auto socks = new DfsVertex();
    socks->name = "socks";

    std::vector<DfsVertex *> v1adjList = {tie, belt};
    std::vector<DfsVertex *> v2adjList = {jacket};
    std::vector<DfsVertex *> v3adjList = {};
    std::vector<DfsVertex *> v4adjList = {jacket};
    std::vector<DfsVertex *> v5adjList = {};
    std::vector<DfsVertex *> v6adjList = {pants, shoes};
    std::vector<DfsVertex *> v7adjList = {belt, shoes};
    std::vector<DfsVertex *> v8adjList = {};
    std::vector<DfsVertex *> v9adjList = {shoes};

    auto graph = std::map<DfsVertex *, std::vector<DfsVertex *>>();
    graph[shirt] = v1adjList;
    graph[tie] = v2adjList;
    graph[jacket] = v3adjList;
    graph[belt] = v4adjList;
    graph[watch] = v5adjList;
    graph[undershorts] = v6adjList;
    graph[pants] = v7adjList;
    graph[shoes] = v8adjList;
    graph[socks] = v9adjList;

    std::list<DfsVertex *> expected = {
            socks, undershorts, pants, watch, shoes, shirt, belt, tie, jacket
    };

    // when
    std::list<DfsVertex *> actual = topological_sort(graph);

    // then
    EXPECT_EQ(expected, actual);
}