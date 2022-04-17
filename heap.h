#pragma once

#include <vector>

#include "vertex.h"

class Heap {
public:
    Heap();
    Vertex GetMin() const;
    void Pop();
    void Add(Vertex x);
    size_t Size() const;

private:
    std::vector<Vertex> heap_;

    void ShiftDown(size_t i);
    void ShiftUp(size_t i);
};
