#include <catch.hpp>

#include "vertex.h"

TEST_CASE("test_vertex") {
    Vertex a(1, 'a');
    Vertex b(1, 'b');
    REQUIRE(!(a == b));
    REQUIRE(a < b);

    a = Vertex(2, 0);
    REQUIRE(a > b);
}
