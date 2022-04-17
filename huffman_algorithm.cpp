#include "huffman_algorithm.h"

size_t GetId(std::map<Vertex, std::vector<size_t>>& get_id_in_trie, Vertex vert) {
    size_t id = get_id_in_trie[vert].back();
    get_id_in_trie[vert].pop_back();
    return id;
}

void AddOne(std::string& num) {
    if (num.empty()) {
        num = "1";
        return;
    }
    bool is_adding = true;

    for (size_t j = 0; j < num.size(); j++) {
        size_t i = num.size() - j - 1;
        if (num[i] == '1' && is_adding) {
            num[i] = '0';
        } else {
            num[i] += is_adding;
            is_adding = 0;
        }
    }
    if (is_adding) {
        num = "1" + num;
    }
}

// Huffman's algorithm : for each symbol finding a length of the code
std::unordered_map<uint16_t, size_t> GetBasicCodes(std::unordered_map<uint16_t, size_t> count_of_symbols) {
    count_of_symbols[FILENAME_END] = 1;
    count_of_symbols[ONE_MORE_FILE] = 1;
    count_of_symbols[ARCHIVE_END] = 1;

    Trie trie = Trie();
    Heap heap = Heap();
    std::map<Vertex, std::vector<size_t>> get_id_in_trie;
    for (const std::pair<uint16_t, size_t> kvp : count_of_symbols) { // setup of algorithm
        Vertex elem = Vertex(kvp.second, kvp.first);
        heap.Add(elem);
        size_t id = trie.AddVertex(elem);
        get_id_in_trie[elem].push_back(id);                          // vertexes can duplicate each other due to nature
                                                                     // of algorithm
    }
    while (heap.Size() > 1) {                                        // algorithm itself
        Vertex v1 = heap.GetMin();
        heap.Pop();
        Vertex v2 = heap.GetMin();
        heap.Pop();

        size_t v = GetId(get_id_in_trie, v1);
        size_t u = GetId(get_id_in_trie, v2);
        size_t k = trie.ConnectTwoVertices(v, u);
        Vertex v3 = trie.GetVert(k);
        get_id_in_trie[v3].push_back(k);
        heap.Add(v3);
    }
    return trie.GetCodes();
}

void MakeNextCanonicCode(std::string& code, size_t length) {
    if (!code.empty()) {                                             // if not the first code
        AddOne(code);
    }
    while (code.size() < length) {
        code += "0";
    }
}

std::vector<std::pair<uint16_t, size_t>>& GetOrderOfSymbols(std::unordered_map<uint16_t, size_t>& length_of_codes) {
    static std::vector<std::pair<uint16_t, size_t>> order;
    for (std::pair<uint16_t, size_t> p : length_of_codes) {
        auto [symbol, length] = p;
        order.push_back({symbol, length});
    }

    std::sort(order.begin(), order.end(), [](const std::pair<uint16_t, size_t>& a, const std::pair<uint16_t, size_t>& b) {
        if (a.second == b.second) {
            return a.first < b.first;
        }
        return a.second < b.second;
    });
    return order;
}

std::pair<std::unordered_map<uint16_t, std::string>, std::vector<uint16_t>> GetCanonicCodes(
    std::unordered_map<uint16_t, size_t>& length_of_codes) {

    std::vector<std::pair<uint16_t, size_t>> order = GetOrderOfSymbols(length_of_codes);

    std::vector<uint16_t> help;                                      // order of symbols without lengths
    for (auto [symbol, length] : order) {
        help.push_back(symbol);
    }

    std::string cur_code;
    std::unordered_map<uint16_t, std::string> res;
    for (size_t i = 0; i < order.size(); i++) {
        auto [symbol, length] = order[i];
        MakeNextCanonicCode(cur_code, length);
        res[symbol] = cur_code;
    }
    return {res, help};
}

std::pair<std::unordered_map<uint16_t, std::string>, std::vector<uint16_t>> HuffmanAlgorithm(
    std::unordered_map<uint16_t, size_t> count_of_symbols) {

    std::unordered_map<uint16_t, size_t> length_of_basic_codes = GetBasicCodes(count_of_symbols);
    return GetCanonicCodes(length_of_basic_codes);
}