#ifndef PROJECT_QUADTREE_AXISALIGNEDBOUNDINGBOX_H
#define PROJECT_QUADTREE_AXISALIGNEDBOUNDINGBOX_H

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

        unsigned int getX() const;
        unsigned int getY() const;
        unsigned int getWidth() const;
        unsigned int getHeight() const;
};


#endif //PROJECT_QUADTREE_AXISALIGNEDBOUNDINGBOX_H
