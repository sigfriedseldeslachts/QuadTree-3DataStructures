#include <catch2/catch_test_macros.hpp>

#include "../include/AxisAlignedBoundingBox.h"

TEST_CASE("AABBs intersect", "[collides]") {
    AxisAlignedBoundingBox a(0, 0, 10, 10);
    AxisAlignedBoundingBox b(10, 10, 10, 10);

    REQUIRE(collides(a, b));
}

TEST_CASE("AABBs don't intersect", "[collides]") {
    AxisAlignedBoundingBox a(0, 0, 10, 10);
    AxisAlignedBoundingBox b(20, 20, 10, 10);

    REQUIRE_FALSE(collides(a, b));
}