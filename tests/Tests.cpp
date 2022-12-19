#define CATCH_CONFIG_MAIN
#include "../lib/catch.hpp"

#include "../include/AxisAlignedBoundingBox.h"
#include "../include/QuadTree.h"

TEST_CASE("AABBs intersect", "[collides]") {
    AxisAlignedBoundingBox a(0, 0, 10, 10);
    AxisAlignedBoundingBox b(9, 9, 10, 10);

    REQUIRE(collides(a, b));
}

TEST_CASE("AABBs don't intersect", "[collides]") {
    AxisAlignedBoundingBox a(0, 0, 10, 10);
    AxisAlignedBoundingBox b(11, 11, 10, 10);

    REQUIRE_FALSE(collides(a, b));
}

TEST_CASE("AABBs intersect on the edge", "[collides]") {
    AxisAlignedBoundingBox a(0, 0, 10, 10);
    AxisAlignedBoundingBox b(10, 10, 10, 10);

    REQUIRE(collides(a, b));
}

TEST_CASE("Children are inserted correctly") {
    QuadTree<int> root(AxisAlignedBoundingBox(0, 0, 10, 10), 1);

    root.insert(AxisAlignedBoundingBox(0, 0, 5, 5), 1);
    root.insert(AxisAlignedBoundingBox(5, 0, 5, 5), 2);
    root.insert(AxisAlignedBoundingBox(0, 5, 5, 5), 3);
    root.insert(AxisAlignedBoundingBox(5, 5, 5, 5), 4);

    // The root should have 1 point
    REQUIRE(root.getPoints().size() == 1);

    // THe last 3 children should have 1 point
    for (int i = 3; i > 1; i--) {
        REQUIRE(root.getChildren()[i]->getPoints().size() == 1);
    }

    // The first child should have 0 points (because there is nothing in its sector, the first insert went to the root)
    REQUIRE(root.getChildren()[0]->getPoints().empty());
}

TEST_CASE("Children are inserted correctly with a higher region capacity than 1") {
    QuadTree<int> root(AxisAlignedBoundingBox(0, 0, 10, 10), 2);

    root.insert(AxisAlignedBoundingBox(0, 0, 5, 5), 1);
    root.insert(AxisAlignedBoundingBox(5, 0, 5, 5), 2);
    root.insert(AxisAlignedBoundingBox(0, 5, 5, 5), 3);
    root.insert(AxisAlignedBoundingBox(5, 5, 5, 5), 4);

    // The root should have 2 points
    REQUIRE(root.getPoints().size() == 2);

    // THe last 3 children should each have 1 point
    for (int i = 3; i > 1; i--) {
        REQUIRE(root.getChildren()[i]->getPoints().size() == 1);
    }
}