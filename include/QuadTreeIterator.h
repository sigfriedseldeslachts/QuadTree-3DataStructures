#pragma once

#include "QuadTree.h"

template <typename T>
class QuadTreeIterator {
    public:
        QuadTreeIterator(QuadTree<T>* node) : current(node) {}

        std::vector<std::pair<AxisAlignedBoundingBox, T>> operator*() const { return current->getPoints(); }

        const QuadTreeIterator<T>& operator++() {
            if (current->getNorthWest() != nullptr) {
                current = current->getNorthWest();
            } else if (current->getNorthEast() != nullptr) {
                current = current->getNorthEast();
            } else if (current->getSouthWest() != nullptr) {
                current = current->getSouthWest();
            } else if (current->getSouthEast() != nullptr) {
                current = current->getSouthEast();
            } else {
                QuadTree<T>* parent = current->getParent();

                while (parent != nullptr) {
                    // Check if we are north west child
                    bool is_north_west = parent->getNorthWest() == current;
                    bool is_north_east = parent->getNorthEast() == current;
                    bool is_south_west = parent->getSouthWest() == current;
                    bool is_south_east = parent->getSouthEast() == current;

                    if (parent->getNorthWest() != nullptr && !is_north_west && !is_north_east && !is_south_west && !is_south_east) {
                        current = parent->getNorthWest();
                        return *this;
                    } else if (parent->getNorthEast() != nullptr && !is_north_east && !is_south_west && !is_south_east) {
                        current = parent->getNorthEast();
                        return *this;
                    } else if (parent->getSouthWest() != nullptr && !is_south_west && !is_south_east) {
                        current = parent->getSouthWest();
                        return *this;
                    } else if (parent->getSouthEast() != nullptr && !is_south_east) {
                        current = parent->getSouthEast();
                        return *this;
                    }

                    current = parent;
                    parent = parent->getParent();
                }

                current = nullptr;
            }

            return *this;
        }

        bool operator==(const QuadTreeIterator<T>& rhs) {
            return current == rhs.current;
        }
        bool operator!=(const QuadTreeIterator<T>& rhs) {
            return current != rhs.current;
        }
        QuadTree<T>* operator->() const { return current; }
        [[nodiscard]] QuadTree<T>& tree() const { return *current; }
    private:
        QuadTree<T>* current;
};

template class QuadTreeIterator<int>;