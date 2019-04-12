//
// Created by kkoltun on 12.04.19.
//

#ifndef ALGORITHMS_CPP_CODE_TOPOLOGICALSORT_H
#define ALGORITHMS_CPP_CODE_TOPOLOGICALSORT_H

#include <map>
#include <list>
#include <vector>
#include "DfsVertex.h"

std::list<DfsVertex *> topological_sort(const std::map<DfsVertex *, std::vector<DfsVertex *>> &graph);

void dfs_visit_with_list_add(std::map<DfsVertex *, std::vector<DfsVertex *>> graph, DfsVertex *vertex, int *timestamp,
                             std::list<DfsVertex *> &vertexList);

#endif //ALGORITHMS_CPP_CODE_TOPOLOGICALSORT_H
