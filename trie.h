#pragma once
#include "vertex.h"
#include "constants.h"

#include <deque>
#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>

class Trie {
public:
    struct Node {
        Vertex vertex;
        int left = -1;
        int right = -1;

        Node() : vertex(Vertex()), left(-1), right(-1){};
    };
    Trie() : tree_({}){};
    Trie(std::unordered_map<uint16_t, std::string> codes);

    void AddCode(size_t t, const std::string& code, size_t id_in_code, uint16_t symbol);
    size_t ConnectTwoVertices(size_t v, size_t u);
    size_t AddVertex(Vertex v);
    Vertex GetVert(size_t id) const;
    size_t GoTo(size_t cur_t, uint16_t bit) const;
    std::unordered_map<uint16_t, size_t> GetCodes() const;

    Node operator[](size_t id) const;

private:
    std::vector<Node> tree_;
};
