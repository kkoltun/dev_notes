//
// Created by kkoltun on 11.04.19.
//

#include "bfs.h"

void bfs(std::map<Vertex *, std::vector<Vertex *>> graph, Vertex *source) {
    for (auto &itr : graph) {
        if (itr.first == source) {
            continue;
        }
        itr.first->color = Color::WHITE;
        itr.first->degree = 0;
        itr.first->predecessor = nullptr;
    }

    source->color = Color::GRAY;
    source->degree = 0;
    source->predecessor = nullptr;

    std::queue<Vertex *> queue = std::queue<Vertex *>();
    queue.push(source);

    while (!queue.empty()) {
        Vertex *u = queue.front();
        queue.pop();

        for (Vertex *v : graph[u]) {
            if (v->color == Color::WHITE) {
                v->color = Color::GRAY;
                v->degree = u->degree + 1;
                v->predecessor = u;

                queue.push(v);
            }
        }
        u->color = Color::BLACK;
    }
}