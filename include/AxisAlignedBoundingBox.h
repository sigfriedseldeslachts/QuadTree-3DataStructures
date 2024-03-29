#pragma once

#include <cmath>
#include <unordered_set>

// This class represents an axis-aligned bounding box
// In a 2D problem, this is simply a rectangle whose sides are
// parallel to the X- and Y-axis
class AxisAlignedBoundingBox {

    private:
        unsigned int x, y, width, height;

    public:
        // Constructor
        AxisAlignedBoundingBox(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

        /**
         * Gives two bounding boxes and checks if they collide
         * @param a Bounding box a
         * @param b Bounding box b
         * @return True if they collide, false otherwise
         */
        friend bool collides(const AxisAlignedBoundingBox &a, const AxisAlignedBoundingBox &b);

        // Create an operator==
        bool operator==(const AxisAlignedBoundingBox& other) const;

        [[nodiscard]] unsigned int getX() const;
        [[nodiscard]] unsigned int getY() const;
        [[nodiscard]] unsigned int getWidth() const;
        [[nodiscard]] unsigned int getHeight() const;
};