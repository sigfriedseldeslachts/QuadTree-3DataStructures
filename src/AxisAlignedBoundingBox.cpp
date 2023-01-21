#include <utility>
#include "../include/AxisAlignedBoundingBox.h"

AxisAlignedBoundingBox::AxisAlignedBoundingBox(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

bool collides(const AxisAlignedBoundingBox &a, const AxisAlignedBoundingBox &b) {
    unsigned int axMin = a.getX();
    unsigned int axMax = a.getX() + a.getWidth();
    unsigned int ayMin = a.getY();
    unsigned int ayMax = a.getY() + a.getHeight();

    unsigned int bxMin = b.getX();
    unsigned int bxMax = b.getX() + b.getWidth();
    unsigned int byMin = b.getY();
    unsigned int byMax = b.getY() + b.getHeight();

    return (axMin < bxMax && bxMin < axMax && ayMin < byMax && byMin < ayMax);
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
