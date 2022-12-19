#include <utility>
#include "../include/AxisAlignedBoundingBox.h"

AxisAlignedBoundingBox::AxisAlignedBoundingBox(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

bool collides(const AxisAlignedBoundingBox &a, const AxisAlignedBoundingBox &b) {
    // Check if B collides with A, the top left corner is 0,0
    // A is the bounding box of the object
    // B is the bounding box of the node
    return a.x < b.x + b.width &&
           a.x + a.width > b.x &&
           a.y < b.y + b.height &&
           a.y + a.height > b.y;
}

bool AxisAlignedBoundingBox::operator==(const AxisAlignedBoundingBox &other) const {
    return x == other.x &&
           y == other.y &&
           width == other.width &&
           height == other.height;
}

unsigned int AxisAlignedBoundingBox::getX() const {
    return x;
}

unsigned int AxisAlignedBoundingBox::getY() const {
    return y;
}

unsigned int AxisAlignedBoundingBox::getWidth() const {
    return width;
}

unsigned int AxisAlignedBoundingBox::getHeight() const {
    return height;
}
