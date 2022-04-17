#include <catch.hpp>
#include <sstream>

#include "dearchive.h"
#include "istream_wrapper.h"
#include "heap.h"
#include "huffman_algorithm.h"
#include "ostream_wrapper.h"
#include "trie.h"

TEST_CASE("test_heap") {
    Heap test;
    test.Add({2, 1});
    test.Add({1, 2});
    test.Add({1, 1});
    Vertex correct = {1, 1};
    REQUIRE(test.GetMin() == correct);
    test.Pop();
    test.Add({0, 100});
    correct = {0, 100};
    REQUIRE(test.GetMin() == correct);
    test.Pop();
    test.Pop();
    test.Pop();
    test.Pop();
    test.Pop();
    test.Pop();  /// test for no crush in this situation
    test.Add({100, 0});
    correct = {100, 0};
    REQUIRE(test.GetMin() == correct);
}

TEST_CASE("test_trie") {
    Trie test;
    test.AddVertex({0, 0});
    test.AddVertex({1, 1});
    test.AddVertex({2, 2});
    test.ConnectTwoVertices(0, 1);
    test.ConnectTwoVertices(3, 2);
    std::unordered_map<uint16_t, size_t> correct_codes = {{0, 2}, {1, 2}, {2, 1}};
    REQUIRE(correct_codes == test.GetCodes());

    test.AddCode(4, "0100", 0, 6);
    size_t t = 4;  /// root of trie
    t = test.GoTo(t, 0);
    t = test.GoTo(t, 1);
    t = test.GoTo(t, 0);
    t = test.GoTo(t, 0);
    REQUIRE(t == 6);
}
TEST_CASE("test_istream_wrapper") {
    std::stringstream s;
    s << "123456789";
    IStreamWrapper input_stream(s);
    REQUIRE(input_stream.GetBits(8) == '1');
    uint16_t c = input_stream.GetBits(9);
    c = input_stream.GetBits(9);
    c = input_stream.GetBits(9);
    REQUIRE(c == 333);
    REQUIRE(input_stream.GetBits(1) == 0);
    REQUIRE(input_stream.GetBits(1) == 1);
}

TEST_CASE("test_ostream_wrapper") {
    std::stringstream s;
    OStreamWrapper output_stream(s);
    output_stream.Put1b(1);
    output_stream.Put1b(0);
    output_stream.Put1b(1);
    output_stream.Put1b(0);
    output_stream.Put1b(0);
    output_stream.Put1b(1);
    output_stream.Put1b(1);
    output_stream.Put1b(1);

    output_stream.Put9b(1);

    output_stream.Put1b(0);
    output_stream.Put1b(1);
    output_stream.Put1b(0);
    output_stream.Put1b(0);
    output_stream.Put1b(1);
    output_stream.Put1b(1);
    output_stream.Put1b(1);

    output_stream.Flush();
    uint8_t a, b, c;
    s >> a;
    s >> b;
    s >> c;
    REQUIRE(a == 229);
    REQUIRE(b == 1);
    REQUIRE(c == 228);
}

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

TEST_CASE("test_reading_through_trie") {
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