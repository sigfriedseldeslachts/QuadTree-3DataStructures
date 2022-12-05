#include "../include/AxisAlignedBoundingBox.h"

AxisAlignedBoundingBox::AxisAlignedBoundingBox(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

bool collides(const AxisAlignedBoundingBox &a, const AxisAlignedBoundingBox &b) {
    return a.x < b.x + b.width &&
           a.x + a.width > b.x &&
           a.y < b.y + b.height &&
           a.y + a.height > b.y;
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
