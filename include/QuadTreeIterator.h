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
        } else if (current->getNorthEast() != nullptr) {
            current = current->getNorthEast();
        } else if (current->getSouthWest() != nullptr) {
            current = current->getSouthWest();
        } else if (current->getSouthEast() != nullptr) {
            current = current->getSouthEast();
        } else {
            // If we currently have no children, we should move up the tree until we find a node with children
            while (current->getParent() != nullptr) {
                if (current->getParent()->getNorthEast() != nullptr && current->getParent()->getNorthEast() != current) {
                    current = current->getParent()->getNorthEast();
                    break;
                } else if (current->getParent()->getSouthWest() != nullptr && current->getParent()->getSouthWest() != current) {
                    current = current->getParent()->getSouthWest();
                    break;
                } else if (current->getParent()->getSouthEast() != nullptr && current->getParent()->getSouthEast() != current) {
                    current = current->getParent()->getSouthEast();
                    break;
                }

                current = current->getParent();
            }

            // If we have no parent (i.e. we are at the root node), we should set the current node to nullptr
            if (current->getParent() == nullptr) {
                current = nullptr;
            }
        }

        return *this;
    }
    QuadTreeIterator<T>& operator--() {
        if (current == nullptr) {
            current = current->getParent();

            while (current != nullptr) {
                current = current->getSouthEast();
            }
        } else if (current->getParent()->getNorthWest() == current) {
            // If we are the north-west child, we should move to the parent
            current = current->getParent();
        } else if (current->getParent()->getNorthEast() == current) {
            // If we are the north-east child, we should move to the north-west child
            current = current->getParent()->getSouthWest();
        } else if (current->getParent()->getSouthWest() == current) {
            // If we are the south-west child, we should move to the north-east child
            current = current->getParent()->getNorthEast();
        } else if (current->getParent()->getSouthEast() == current) {
            // If we are the south-east child, we should move to the south-west child
            current = current->getParent()->getNorthWest();
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