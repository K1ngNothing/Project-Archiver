#include <catch.hpp>
#include <sstream>

#include "ostream_wrapper.h"

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
