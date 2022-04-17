#pragma once

#include <cstdint>
#include <cstddef>

struct Vertex {
    size_t value;
    uint16_t symbol;

    Vertex(size_t value, uint16_t symbol) : value(value), symbol(symbol){}

    Vertex() : value(0), symbol(0){};

    bool operator<(const Vertex& a) const;
    bool operator>(const Vertex& a) const;
    bool operator==(const Vertex& a) const;
};
