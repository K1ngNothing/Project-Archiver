#include <catch.hpp>

#include "trie.h"

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