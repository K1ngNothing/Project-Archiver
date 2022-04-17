#include <catch.hpp>
#include <sstream>

#include "dearchive.h"

extern void ReconstructCanonicHuffmanCodes(uint16_t symbol_count, const std::vector<uint16_t>& symbols,
                                           std::unordered_map<uint16_t, std::string>& codes,
                                           IStreamWrapper& input_stream);

TEST_CASE("reconstruct_canonic_huffman_codes") {
    uint16_t symbol_count = 5;
    std::vector<uint16_t> symbols = {'a', 'c', 'b', 'd', 'e'};
    std::unordered_map<uint16_t, std::string> codes;

    std::stringstream s;
    s << static_cast<char>(0);
    s << static_cast<char>(4);
    s << static_cast<char>(0);
    s << static_cast<char>(24);
    s << static_cast<char>(0);

    IStreamWrapper input_stream(s);
    ReconstructCanonicHuffmanCodes(symbol_count, symbols, codes, input_stream);
    std::unordered_map<uint16_t, std::string> correct = {
        {'a', "00"}, {'c', "01"}, {'b', "1000"}, {'d', "1001"}, {'e', "1010"}};
    REQUIRE(correct == codes);
}

TEST_CASE("test_read_one_symbol") {
    std::unordered_map<uint16_t, std::string> codes = {{0, "000"}, {1, "001"}, {2, "10"}, {3, "01"}, {4, "11"}};
    std::stringstream s;
    s << 'a';
    s << 'b';
    IStreamWrapper input_stream(s);
    Trie trie(codes);
    std::vector<uint16_t> res;
    for (size_t i = 0; i < 4; i++) {
        uint16_t c = ReadOneSymbol(input_stream, trie);
        res.push_back(c);
    }
    std::vector<uint16_t> correct = {2, 0, 4, 1};
    REQUIRE(correct == res);
}
