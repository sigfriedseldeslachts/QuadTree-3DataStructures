#ifndef PROJECT_QUADTREE_QUADTREE_H
#define PROJECT_QUADTREE_QUADTREE_H

#include <unordered_set>
#include <vector>
#include "AxisAlignedBoundingBox.h"

// This class is our actual quadtree
// It stores AABB’s together with some metadata
// Space Complexity: O(N)
template <typename MetadataType>
class QuadTree {
    private:
        AxisAlignedBoundingBox bounds;
        unsigned int region_capacity = 0;

        // Create a point map
        std::vector<std::pair<AxisAlignedBoundingBox, MetadataType>> points;

        // Subtrees
        QuadTree* north_west = nullptr; // AKA: Top-Left
        QuadTree* north_east = nullptr; // AKA: Top-Right
        QuadTree* south_west = nullptr; // AKA: Bottom-Left
        QuadTree* south_east = nullptr; // AKA: Bottom-Right

    public:
        // Constructor
        // `bounds` specifies the edges of the region that
        // the quadtree covers.
        // `region_capacity` specifies the maximum number of objects
        // in a single region
        QuadTree(const AxisAlignedBoundingBox& bounds, unsigned int region_capacity) : bounds(bounds), region_capacity(region_capacity) {}

        void insert(const AxisAlignedBoundingBox& bounds, const MetadataType& metadata);

        /**
         * Subdivides the current region into four sub-regions
         */
        void subdivide();

        // This method should return a std::unordered_set of
        // all items inside the given AABB.
        // The given AABB may span multiple square regions of
        // the quadtree.
        // The worst-case time-complexity of this method should be
        // O(log(N)) for a Quadtree with N leaf nodes
        // TODO: You should decide the element type of the
        // std::unordered_set
        // Your set should contain the AABB and the Metadata of
        // all objects in the given region.
        std::unordered_set<MetadataType> query(const AxisAlignedBoundingBox& bounds);

        // TODO: You should decide the return type for this method
        // This method should return an iterator that runs over
        // every element in the quadtree.
        auto begin();

        // TODO: You should decide the return type for this method
        // This method should return an iterator pointing
        // one past the last element in the quadtree.
        // When iterating from begin() to end(),
        // we should visit all elements in the quadtree.
        // There is no requirement with regards to
        // the order that you visit these elements in.
        auto end();
};

template class QuadTree<int>;

#endif //PROJECT_QUADTREE_QUADTREE_H
