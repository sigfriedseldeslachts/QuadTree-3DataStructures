#include "../include/QuadTree.h"

template<typename MetadataType>
void QuadTree<MetadataType>::insert(const AxisAlignedBoundingBox &bounds, const MetadataType &metadata) {
    // First we should check if the AABB is actually inside the bounds of the current tree
    if (!collides(this->bounds, bounds)) {
        return;
    }

    // If there is space in the current tree, we can just insert the AABB
    if (this->points.size() < this->region_capacity) {
        this->points.push_back(std::make_pair(bounds, metadata));
        return;
    }

    // Check if we have not yet subdivided the current tree
    if (this->north_west == nullptr) {
        this->subdivide();
    }

    // Insert the AABB into the correct subtree
    this->north_west->insert(bounds, metadata);
    this->north_east->insert(bounds, metadata);
    this->south_west->insert(bounds, metadata);
    this->south_east->insert(bounds, metadata);
}

template<typename MetadataType>
void QuadTree<MetadataType>::subdivide() {
    // First check if we have already subdivided
    if (this->north_west != nullptr) {
        return;
    }

    unsigned int x = this->bounds.getX(), y = this->bounds.getY(),
                 width = this->bounds.getWidth(), height = this->bounds.getHeight();

    this->north_west = new QuadTree<MetadataType>(AxisAlignedBoundingBox(x, y, width / 2, height / 2), this->region_capacity);
    this->north_east = new QuadTree<MetadataType>(AxisAlignedBoundingBox(x + width / 2, y, width / 2, height / 2), this->region_capacity);
    this->south_west = new QuadTree<MetadataType>(AxisAlignedBoundingBox(x, y + height / 2, width / 2, height / 2), this->region_capacity);
    this->south_east = new QuadTree<MetadataType>(AxisAlignedBoundingBox(x + width / 2, y + height / 2, width / 2, height / 2), this->region_capacity);
}

template<typename MetadataType>
std::unordered_set<MetadataType> QuadTree<MetadataType>::query(const AxisAlignedBoundingBox &bounds) {
    // Createa a vector to store the results
    std::unordered_set<MetadataType> results;

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
    std::unordered_set<MetadataType> north_west_results = this->north_west->query(bounds);
    std::unordered_set<MetadataType> north_east_results = this->north_east->query(bounds);
    std::unordered_set<MetadataType> south_west_results = this->south_west->query(bounds);
    std::unordered_set<MetadataType> south_east_results = this->south_east->query(bounds);

    // Insert the results from the subtrees into the results vector
    results.insert(north_west_results.begin(), north_west_results.end());
    results.insert(north_east_results.begin(), north_east_results.end());
    results.insert(south_west_results.begin(), south_west_results.end());
    results.insert(south_east_results.begin(), south_east_results.end());

    return results;
}

template<typename MetadataType>
auto QuadTree<MetadataType>::begin() {
    return nullptr;
}

template<typename MetadataType>
auto QuadTree<MetadataType>::end() {
    return nullptr;
}
