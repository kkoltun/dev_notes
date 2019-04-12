//
// Created by kkoltun on 12.04.19.
//

#ifndef ALGORITHMS_CPP_CODE_DFS_H
#define ALGORITHMS_CPP_CODE_DFS_H

#include <map>
#include <vector>
#include "DfsVertex.h"

void dfs(const std::map<DfsVertex*, std::vector<DfsVertex*>>&);

void dfs_visit(std::map<DfsVertex*, std::vector<DfsVertex*>>, DfsVertex*, int*);

#endif //ALGORITHMS_CPP_CODE_DFS_H
