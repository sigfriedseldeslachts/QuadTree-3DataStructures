#include <iostream>
#include "../include/QuadTree.h"
#include "../include/QuadTreeIterator.h"

template<typename T>
void QuadTree<T>::insert(const AxisAlignedBoundingBox &boundingBox, const T &metadata) {
    // We should check if the given boundingBox collides with the boundingBox of this node
    // If it does, continue on otherwise we stop here because subregions will also not collide
    if (!collides(this->bounds, boundingBox)) {
        return;
    }

    // If there is space in the current tree, we can just insert the AABB
    // When this is true, we insert and stop here. We don't need to insert it in other children since this will get queried anyway
    if (this->points.size() < this->region_capacity && this->children[0] == nullptr) {
        this->points.push_back(std::make_pair(boundingBox, metadata));
        return;
    }

    // Check if we have not yet subdivided the current tree
    if (this->children[0] == nullptr) {
        this->subdivide();
    }

    // For all the children, we should insert the AABB
    // It needs to be inserted in ALL the children because if it is inserted in only one then it might not be shown when querying it
    for (QuadTree<T>* child : this->children) {
        child->insert(boundingBox, metadata);
    }
}

template<typename T>
void QuadTree<T>::subdivide() {
    // First check if we have already subdivided
    if (this->children[0] != nullptr) {
        return;
    }

    unsigned int x = this->bounds.getX(), y = this->bounds.getY(),
                 width = this->bounds.getWidth(), height = this->bounds.getHeight();

    this->children[0] = new QuadTree<T>(AxisAlignedBoundingBox(x, y, width / 2, height / 2), this->region_capacity, this);
    this->children[1] = new QuadTree<T>(AxisAlignedBoundingBox(x + (width / 2), y, width / 2, height / 2), this->region_capacity, this);
    this->children[2] = new QuadTree<T>(AxisAlignedBoundingBox(x, y + (height / 2), width / 2, height / 2), this->region_capacity, this);
    this->children[3] = new QuadTree<T>(AxisAlignedBoundingBox(x + (width / 2), y + (height / 2), width / 2, height / 2), this->region_capacity, this);
}

template<typename T>
std::unordered_set<std::pair<AxisAlignedBoundingBox, T>> QuadTree<T>::query(const AxisAlignedBoundingBox &requested_bounds) {
    // Create a vector to store the results
    std::unordered_set<std::pair<AxisAlignedBoundingBox, T>> results = {};

    // Check if the AABB is actually inside the requested_bounds of the current tree
    if (!collides(this->bounds, requested_bounds)) {
        return results;
    }

    // From the current points vector get all the metadata that is inside the given AABB
    for (std::pair point : this->points) {
        if (collides(point.first, requested_bounds)) {
            results.insert(point);
        }
    }

    // Check if we have subtrees, if not, return the results
    if (this->children[0] == nullptr) {
        return results;
    }

    // For all children, get the results
    for (QuadTree<T>* child : this->children) {
        auto child_results = child->query(requested_bounds);
        results.insert(child_results.begin(), child_results.end());
    }

    return results;
}

template<typename T>
std::vector<std::pair<AxisAlignedBoundingBox, T>> QuadTree<T>::get_as_vector() {
    // Go through the whole tree and get each AABB and metadata
    std::vector<std::pair<AxisAlignedBoundingBox, T>> results;

    // Get the points from the current tree
    for (std::pair point : this->points) {
        results.push_back(point);
    }

    // Check if we have subtrees, if not, return the results
    if (this->children[0] == nullptr) {
        return results;
    }

    // For all children, get the results
    for (QuadTree<T>* child : this->children) {
        std::vector<std::pair<AxisAlignedBoundingBox, T>> child_results = child->get_as_vector();
        results.insert(results.end(), child_results.begin(), child_results.end());
    }

    return results;
}

template<typename T>
QuadTreeIterator<T> QuadTree<T>::begin() {
    return QuadTreeIterator<T>(this);
}

template<typename T>
QuadTreeIterator<T> QuadTree<T>::end() {
    return QuadTreeIterator<T>(nullptr);
}
