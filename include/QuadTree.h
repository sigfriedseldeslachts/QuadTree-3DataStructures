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

        std::vector<QuadTree<T> *> children = {nullptr, nullptr, nullptr, nullptr};
        QuadTree* parent = nullptr;

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
        [[nodiscard]] const std::vector<QuadTree<T> *> &getChildren() const {
            return children;
        }
        [[nodiscard]] QuadTree *getParent() const {
            return parent;
        }
        [[nodiscard]] QuadTree *getNorthWest() const {
            return children[0];
        }
        [[nodiscard]] QuadTree *getNorthEast() const {
            return children[1];
        }
        [[nodiscard]] QuadTree *getSouthWest() const {
            return children[2];
        }
        [[nodiscard]] QuadTree *getSouthEast() const {
            return children[3];
        }
};

template class QuadTree<int>;
