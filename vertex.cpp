#include "vertex.h"

bool Vertex::operator<(const Vertex& a) const {
    if (value == a.value) {
        return symbol < a.symbol;
    }
    return value < a.value;
}
bool Vertex::operator>(const Vertex& a) const {
    if (value == a.value) {
        return symbol > a.symbol;
    }
    return value > a.value;
}
bool Vertex::operator==(const Vertex& a) const {
    return value == a.value && symbol == a.symbol;
}