#pragma once

#include <unordered_set>
#include <vector>
#include <map>
#include "AxisAlignedBoundingBox.h"

template <typename T>
class QuadTreeIterator;

template <typename T>
class QuadTree {
    private:
        AxisAlignedBoundingBox bounds;
        unsigned int region_capacity = 0;
        std::vector<std::pair<AxisAlignedBoundingBox, T>> points;

        //QuadTree<T>* children[4];

        QuadTree* parent = nullptr;
        QuadTree* north_west = nullptr; // AKA: Top-Left
        QuadTree* north_east = nullptr; // AKA: Top-Right
        QuadTree* south_west = nullptr; // AKA: Bottom-Left
        QuadTree* south_east = nullptr; // AKA: Bottom-Right

    public:
        QuadTree(const AxisAlignedBoundingBox& bounds, unsigned int region_capacity, QuadTree* parent = nullptr) : bounds(bounds), region_capacity(region_capacity), parent(parent) {}

        void insert(const AxisAlignedBoundingBox& bounds, const T& metadata);
        void subdivide();
        std::unordered_set<T> query(const AxisAlignedBoundingBox& bounds);

        // Get all points as a vector
        std::vector<std::pair<AxisAlignedBoundingBox, T>> get_as_vector();

        QuadTreeIterator<T> begin();
        QuadTreeIterator<T> end();

        [[nodiscard]] AxisAlignedBoundingBox &getBounds() {
            return bounds;
        }
        [[nodiscard]] const std::vector<std::pair<AxisAlignedBoundingBox, T>> &getPoints() const {
            return points;
        }
        [[nodiscard]] QuadTree *getParent() const {
            return parent;
        }
        [[nodiscard]] QuadTree *getNorthWest() const {
            return north_west;
        }
        [[nodiscard]] QuadTree *getNorthEast() const {
            return north_east;
        }
        [[nodiscard]] QuadTree *getSouthWest() const {
            return south_west;
        }
        [[nodiscard]] QuadTree *getSouthEast() const {
            return south_east;
        }
};

template class QuadTree<int>;
