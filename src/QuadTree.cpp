#include <iostream>
#include "../include/QuadTree.h"
#include "../include/QuadTreeIterator.h"

template<typename T>
void QuadTree<T>::insert(const AxisAlignedBoundingBox &bounds, const T &metadata, QuadTree<T> *parent_node) {
    // We should check if the given bounds collides with the bounds of this node
    // If it does, continue on otherwise we stop here because subregions will also not collide
    if (!collides(this->bounds, bounds)) {
        return;
    }

    // Set parent node
    this->parent = parent_node;

    // If there is space in the current tree, we can just insert the AABB
    if (this->points.size() < this->region_capacity && this->north_west == nullptr) {
        // Print the metadata
        std::cout << "Inserting " << (int) metadata << std::endl;
        this->points.push_back(std::make_pair(bounds, metadata));
        return;
    }

    // Check if we have not yet subdivided the current tree
    if (this->north_west == nullptr) {
        this->subdivide();
    }

    // Insert the AABB into the correct subtree
    this->north_west->insert(bounds, metadata, this);
    this->north_east->insert(bounds, metadata, this);
    this->south_west->insert(bounds, metadata, this);
    this->south_east->insert(bounds, metadata, this);
}

template<typename T>
void QuadTree<T>::subdivide() {
    // First check if we have already subdivided
    if (this->north_west != nullptr) {
        return;
    }

    unsigned int x = this->bounds.getX(), y = this->bounds.getY(),
                 width = this->bounds.getWidth(), height = this->bounds.getHeight();

    this->north_west = new QuadTree<T>(AxisAlignedBoundingBox(x, y, width / 2, height / 2), this->region_capacity);
    this->north_east = new QuadTree<T>(AxisAlignedBoundingBox(x + (width / 2), y, width / 2, height / 2), this->region_capacity);
    this->south_west = new QuadTree<T>(AxisAlignedBoundingBox(x, y + (height / 2), width / 2, height / 2), this->region_capacity);
    this->south_east = new QuadTree<T>(AxisAlignedBoundingBox(x + (width / 2), y + (height / 2), width / 2, height / 2), this->region_capacity);
}

template<typename T>
std::unordered_set<T> QuadTree<T>::query(const AxisAlignedBoundingBox &bounds) {
    // Createa a vector to store the results
    std::unordered_set<T> results;

    // Check if the AABB is actually inside the bounds of the current tree
    if (!collides(this->bounds, bounds)) {
        return results;
    }

    // From the current points vector get all the metadata that is inside the given AABB
    for (std::pair point : this->points) {
        if (collides(point.first, bounds)) {
            results.insert(point.second);
        }
    }

    // Check if we have subtrees, if not, return the results
    if (this->north_west == nullptr) {
        return results;
    }

    // Get the results from the subtrees
    std::unordered_set<T> north_west_results = this->north_west->query(bounds);
    std::unordered_set<T> north_east_results = this->north_east->query(bounds);
    std::unordered_set<T> south_west_results = this->south_west->query(bounds);
    std::unordered_set<T> south_east_results = this->south_east->query(bounds);

    // Insert the results from the subtrees into the results vector
    results.insert(north_west_results.begin(), north_west_results.end());
    results.insert(north_east_results.begin(), north_east_results.end());
    results.insert(south_west_results.begin(), south_west_results.end());
    results.insert(south_east_results.begin(), south_east_results.end());

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
    if (this->north_west == nullptr) {
        return results;
    }

    // Get the results from the subtrees
    std::vector<std::pair<AxisAlignedBoundingBox, T>> north_west_results = this->north_west->get_as_vector();
    std::vector<std::pair<AxisAlignedBoundingBox, T>> north_east_results = this->north_east->get_as_vector();
    std::vector<std::pair<AxisAlignedBoundingBox, T>> south_west_results = this->south_west->get_as_vector();
    std::vector<std::pair<AxisAlignedBoundingBox, T>> south_east_results = this->south_east->get_as_vector();

    // Insert the results from the subtrees into the results vector
    results.insert(results.end(), north_west_results.begin(), north_west_results.end());
    results.insert(results.end(), north_east_results.begin(), north_east_results.end());
    results.insert(results.end(), south_west_results.begin(), south_west_results.end());
    results.insert(results.end(), south_east_results.begin(), south_east_results.end());

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
