#include <catch.hpp>

#include "huffman_algorithm.h"

extern void MakeNextCanonicCode(std::string& code, size_t length);
extern std::vector<std::pair<uint16_t, size_t>>& GetOrderOfSymbols(
    std::unordered_map<uint16_t, size_t>& length_of_codes);

TEST_CASE("test_huffman_algorithm") {
    std::unordered_map<uint16_t, size_t> cnt = {{0, 1}, {1, 3}, {2, 2}, {3, 4}, {4, 5}};
    auto help = HuffmanAlgorithm(cnt);
    std::unordered_map<uint16_t, std::string> codes = help.first;
    std::unordered_map<uint16_t, std::string> correct = {{0, "1100"}, {1, "100"},    {2, "101"},    {3, "00"},
                                                         {4, "01"},   {256, "1101"}, {257, "1110"}, {258, "1111"}};
    REQUIRE(codes == correct);
    std::vector<uint16_t> chars = help.second;
    std::vector<uint16_t> correct2 = {3, 4, 1, 2, 0, 256, 257, 258};
    REQUIRE(chars == correct2);
}

TEST_CASE("test_make_next_canonic_code") {
    std::string code;
    MakeNextCanonicCode(code, 3);
    REQUIRE(code == "000");
    MakeNextCanonicCode(code, 3);
    REQUIRE(code == "001");
    MakeNextCanonicCode(code, 3);
    REQUIRE(code == "010");
    MakeNextCanonicCode(code, 4);
    REQUIRE(code == "0110");
}

TEST_CASE("test_get_order_of_symbols") {
    std::unordered_map<uint16_t, size_t> length_of_codes = {{'a', 3}, {'b', 1}, {'c', 4}};
    std::vector<std::pair<uint16_t, size_t>>& order = GetOrderOfSymbols(length_of_codes);
    std::vector<std::pair<uint16_t, size_t>> correct = {{'b', 1}, {'a', 3}, {'c', 4}};
    REQUIRE(order == correct);
}
