//
// Created by kkoltun on 12.04.19.
//

#include "topologicalSort.h"

std::list<DfsVertex*> topological_sort(const std::map<DfsVertex *, std::vector<DfsVertex *>> &graph) {
    int timestamp = 0;
    std::list<DfsVertex*> vertexList = std::list<DfsVertex*>();

    for (auto &vertexWithAdjacentVortices : graph) {
        if (vertexWithAdjacentVortices.first->color == WHITE) {
            dfs_visit_with_list_add(graph, vertexWithAdjacentVortices.first, &timestamp, vertexList);
        }
    }

    return vertexList;
}

void dfs_visit_with_list_add(std::map<DfsVertex *, std::vector<DfsVertex *>> graph, DfsVertex *vertex, int *timestamp, std::list<DfsVertex*>& vertexList) {
    ++(*timestamp);

    vertex->color = GRAY;
    vertex->discoveredTimestamp = *timestamp;

    for (DfsVertex *adjVertex : graph[vertex]) {
        if (adjVertex->color == WHITE) {
            adjVertex->predescessor = vertex;

            dfs_visit_with_list_add(graph, adjVertex, timestamp, vertexList);
        }
    }

    vertexList.push_front(vertex);

    vertex->color = BLACK;

    ++(*timestamp);
    vertex->exploredTimestamp = *timestamp;
}