//
// Created by kkoltun on 11.04.19.
//

#ifndef ALGORITHMS_CPP_CODE_VERTEX_H
#define ALGORITHMS_CPP_CODE_VERTEX_H

enum Color {
    WHITE, // undiscovered
    GRAY,  // discovered
    BLACK  // explored
};

struct Vertex {
    Color color;
    unsigned degree;
    Vertex* predecessor;
};

#endif //ALGORITHMS_CPP_CODE_VERTEX_H
