#pragma once

#include "QuadTree.h"

template <typename T>
class QuadTreeIterator {
    public:
        QuadTreeIterator(QuadTree<T>* node) : current(node) {}

        std::vector<std::pair<AxisAlignedBoundingBox, T>> operator*() const { return current->getPoints(); }

        QuadTreeIterator<T>& operator++() {
            if (current->getNorthWest() != nullptr) {
                current = current->getNorthWest();
                return *this;
            }

            // If we have a north-east child, move to it.
            if (current->getNorthEast() != nullptr) {
                current = current->getNorthEast();
                return *this;
            }

            // If we have a south-west child, move to it.
            if (current->getSouthWest() != nullptr) {
                current = current->getSouthWest();
                return *this;
            }

            // If we have a south-east child, move to it.
            if (current->getSouthEast() != nullptr) {
                current = current->getSouthEast();
                return *this;
            }

            // If we have a parent, move to the next sibling of the parent.
            while (current->getParent() != nullptr) {
                current = current->getParent();

                if (current->getNorthWest() != nullptr) {
                    current = current->getNorthWest();
                    return *this;
                }
                if (current->getNorthEast() != nullptr) {
                    current = current->getNorthEast();
                    return *this;
                }
                if (current->getSouthWest() != nullptr) {
                    current = current->getSouthWest();
                    return *this;
                }
                if (current->getSouthEast() != nullptr) {
                    current = current->getSouthEast();
                    return *this;
                }
            }

            // If we have no parent (i.e. we are at the root node), set the current node to nullptr.
            current = nullptr;
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