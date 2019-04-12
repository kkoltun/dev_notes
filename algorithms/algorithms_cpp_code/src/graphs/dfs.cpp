//
// Created by kkoltun on 12.04.19.
//

#include "dfs.h"


void dfs(const std::map<DfsVertex *, std::vector<DfsVertex *>> &graph) {
    int timestamp = 0;

    for (auto &vertexWithAdjacentVortices : graph) {
        if (vertexWithAdjacentVortices.first->color == WHITE) {
            dfs_visit(graph, vertexWithAdjacentVortices.first, &timestamp);
        }
    }
}

void dfs_visit(std::map<DfsVertex *, std::vector<DfsVertex *>> graph, DfsVertex *vertex, int *timestamp) {
    ++(*timestamp);

    vertex->color = GRAY;
    vertex->discoveredTimestamp = *timestamp;

    for (DfsVertex *adjVertex : graph[vertex]) {
        if (adjVertex->color == WHITE) {
            adjVertex->predescessor = vertex;

            dfs_visit(graph, adjVertex, timestamp);
        }
    }

    vertex->color = BLACK;

    ++(*timestamp);
    vertex->exploredTimestamp = *timestamp;
}