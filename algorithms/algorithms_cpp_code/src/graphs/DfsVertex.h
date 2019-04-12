//
// Created by kkoltun on 12.04.19.
//

#ifndef ALGORITHMS_CPP_CODE_DFSVERTEX_H
#define ALGORITHMS_CPP_CODE_DFSVERTEX_H

#include <string>

#include "Vertex.h"

struct DfsVertex {
    std::string name;
    DfsVertex* predescessor;
    Color  color;
    int discoveredTimestamp;
    int exploredTimestamp;
};


#endif //ALGORITHMS_CPP_CODE_DFSVERTEX_H
