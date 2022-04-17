#include "trie.h"

const Vertex DEFAULT_VERT = {0, END_OF_FILE};

size_t Trie::AddVertex(Vertex v) {
    Node node = Node();
    node.vertex = v;
    node.left = node.right = -1;
    tree_.push_back(node);
    size_t k = tree_.size() - 1;
    return k;
}

size_t Trie::ConnectTwoVertices(size_t v, size_t u) {
    size_t k = AddVertex(Vertex());
    tree_[k].left = v;
    tree_[k].right = u;
    tree_[k].vertex.symbol = 0;
    tree_[k].vertex.value = tree_[v].vertex.value + tree_[u].vertex.value;
    return k;
}

std::unordered_map<uint16_t, size_t> Trie::GetCodes() const {                      // for each symbol I count length of code
    if (tree_.empty()) {
        return {};
    }
    std::unordered_map<uint16_t, size_t> codes;
    std::deque<std::pair<size_t, size_t> > queue = {{tree_.size() - 1, 0}};   //.first - vertex,
                                                                                   // .second - length of path to root
    while (!queue.empty()) {
        auto [t, length] = queue.front();
        queue.pop_front();
        if (tree_[t].left == -1 && tree_[t].right == -1) {
            codes[tree_[t].vertex.symbol] =
                (length == 0 ? 1 : length);                                        // if length == 0, then only
                                                                                   // one vertex in trie
        } else {
            if (tree_[t].left != -1) {
                queue.push_back({tree_[t].left, length + 1});
            }
            if (tree_[t].right != -1) {
                queue.push_back({tree_[t].right, length + 1});
            }
        }
    }
    return codes;
}

Vertex Trie::GetVert(size_t id) const {
    return tree_[id].vertex;
}

void Trie::AddCode(size_t t, const std::string& code, size_t id_in_code, uint16_t symbol) {
    if (id_in_code == code.size()) {
        tree_[t].vertex = Vertex(0, symbol);
        return;
    }
    size_t next_t = 0;
    if (code[id_in_code] == '0') {
        if (tree_[t].left == -1) {
            AddVertex(DEFAULT_VERT);
            tree_[t].left = tree_.size() - 1;
        }
        next_t = tree_[t].left;
    } else {
        if (tree_[t].right == -1) {
            AddVertex(DEFAULT_VERT);
            tree_[t].right = tree_.size() - 1;
        }
        next_t = tree_[t].right;
    }
    AddCode(next_t, code, id_in_code + 1, symbol);
}

Trie::Trie(std::unordered_map<uint16_t, std::string> codes) : Trie() {
    AddVertex(DEFAULT_VERT);
    for (const auto& kvp : codes) {
        uint16_t symbol = kvp.first;
        const std::string& code = kvp.second;
        AddCode(0, code, 0, symbol);
    }
}

size_t Trie::GoTo(size_t cur_t, uint16_t bit) const {
    if (bit == 0) {
        if (tree_[cur_t].left == -1) {
            throw std::invalid_argument("Incorrect archive format");
        }
        return tree_[cur_t].left;
    }
    if (tree_[cur_t].right == -1) {
        throw std::invalid_argument("Incorrect archive format");
    }
    return tree_[cur_t].right;
}

Trie::Node Trie::operator[](size_t id) const {
    return tree_[id];
}