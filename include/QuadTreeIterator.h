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
                    int index = this->findCurrentChildIndex(); // Index of the current node in the parent's children vector
                    std::vector<QuadTree< T>*> children = parent->getChildren();

                    // In a for-loop grab the next child
                    // We start at index + 1, if we are at north-east (index 1) we want to start at south-west (index 2)
                    for (int i = index + 1; i < children.size(); i++) {
                        if (children[i] != nullptr) {
                            current = children[i];
                            return *this;
                        }
                    }

                    current = parent;
                    parent = parent->getParent();
                }

                current = nullptr;
            }

            return *this;
        }

        /**
         * Find the current index of the child in the parent
         * Eg if we are the north west child, return 0, if we are the north east child, return 1, etc
         * @return The index of the child in the parent
         */
        int findCurrentChildIndex() {
            QuadTree<T>* parent = current->getParent();
            std::vector<QuadTree< T>*> children = parent->getChildren();

            for (int i = 0; i < children.size(); i++) {
                if (children[i] == current) {
                    return i;
                }
            }

            return -1;
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