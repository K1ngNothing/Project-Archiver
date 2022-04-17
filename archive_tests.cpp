#include <catch.hpp>
#include <sstream>
#include <iostream>

#include "archive.h"
#include "ostream_wrapper.h"

extern void PrintCode(const std::string& code, OStreamWrapper& output_stream);
extern std::pair<std::unordered_map<size_t, size_t>, size_t> GetHelpingInfo(
    std::unordered_map<uint16_t, std::string>& codes);

TEST_CASE("test_print_code") {
    std::stringstream s;
    OStreamWrapper output_stream(s);
    PrintCode("11011", output_stream);
    output_stream.Flush();

    uint8_t a;
    s >> a;
    REQUIRE(a == 27);
}

TEST_CASE("test_get_helping_info") {
    std::unordered_map<uint16_t, std::string> codes = {{1, "100"}, {2, "000"}, {3, "1"}};
    auto [cnt_of_length, max_code_size] = GetHelpingInfo(codes);

    std::unordered_map<size_t, size_t> correct = {{1, 1}, {3, 2}};
    REQUIRE(cnt_of_length == correct);
    REQUIRE(max_code_size == 3);
}
