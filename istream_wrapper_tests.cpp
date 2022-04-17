#include <catch.hpp>
#include <sstream>

#include "istream_wrapper.h"

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
