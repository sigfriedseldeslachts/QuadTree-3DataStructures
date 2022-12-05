#include <iostream>
#include <chrono>

#include "../include/AxisAlignedBoundingBox.h"
#include "../include/QuadTree.h"

int main() {
    // Create a new AABB tree with a capacity of 4
    QuadTree<int> root_tree(AxisAlignedBoundingBox(0, 0, 100, 100), 4);

    // Insert some AABBs
    root_tree.insert(AxisAlignedBoundingBox(0, 0, 10, 10), 1);
    root_tree.insert(AxisAlignedBoundingBox(10, 10, 10, 10), 2);
    root_tree.insert(AxisAlignedBoundingBox(20, 20, 10, 10), 3);
    root_tree.insert(AxisAlignedBoundingBox(30, 30, 10, 10), 4);
    root_tree.insert(AxisAlignedBoundingBox(40, 40, 10, 10), 5);
    root_tree.insert(AxisAlignedBoundingBox(50, 50, 10, 10), 6);

    // Start a chrono timer
    auto start = std::chrono::high_resolution_clock::now();

    // Query the tree for AABBs that intersect with a given AABB
    std::unordered_set<int> results = root_tree.query(AxisAlignedBoundingBox(0, 0, 100, 100));

    // Stop the chrono timer
    auto stop = std::chrono::high_resolution_clock::now();

    // Print the results
    for (int result : results) {
        std::cout << result << std::endl;
    }

    // Print the time it took to query the tree
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << " microseconds" << std::endl;

    return 0;
}
