#pragma once

#include "QuadTree.h"

template <typename T>
class QuadTreeIterator {
    public:
        QuadTreeIterator(QuadTree<T>* node) : current(node) {}

        std::vector<std::pair<AxisAlignedBoundingBox, T>> operator*() const { return current->getPoints(); }

        const QuadTreeIterator<T>& operator++() {
            // We set the initial value to those of the current node, this way we can reuse the while loop
            // It always checks the current node first
            // An additional if statement is needed to not overwrite the current node, otherwise we would skip the first node and cause a segfault (accessing a nullptr)
            QuadTree<T>* parent = current;
            std::vector<QuadTree<T>*> children = current->getChildren();
            int index = this->findCurrentChildIndex(current);

            // If the parent is a null pointer we are at the root node
            while (parent != nullptr) {
                // If children and index are not set, otherwise the loop breaks, can also add a check if parent is null at the end of the while
                if (children.empty() || index == -2) { // -2 because -1 is used for the index of the current node
                    children = parent->getChildren();
                    index = this->findCurrentChildIndex();
                }

                // In a for-loop grab the next child
                // We start at index + 1, if we are at north-east (index 1) we want to start at south-west (index 2)
                for (unsigned long i = index + 1; i < children.size(); i++) {
                    if (children[i] != nullptr) {
                        current = children[i];
                        return *this;
                    }
                }

                current = parent;
                parent = parent->getParent();
                // Reset the index and children so the while loop can find the next node
                children = std::vector<QuadTree<T>*>();
                index = -2;
            }

            current = nullptr;
            return *this;
        }

        /**
         * Find the current index of the child in the parent
         * Eg if we are the north west child, return 0, if we are the north east child, return 1, etc
         * @return The index of the child in the parent, -1 if not found
         */
        int findCurrentChildIndex(QuadTree<T>* parent = nullptr) {
            if (parent == nullptr) {
                parent = current->getParent();
            }
            std::vector<QuadTree< T>*> children = parent->getChildren();

            for (unsigned long i = 0; i < children.size(); i++) {
                if (children[i] == current) {
                    return (int) i;
                }
            }

            return -1; // Item not found in current's parent
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