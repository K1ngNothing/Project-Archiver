#include <catch.hpp>

#include "heap.h"

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
    test.Pop();
    test.Add({100, 0});
    correct = {100, 0};
    REQUIRE(test.GetMin() == correct);
}
