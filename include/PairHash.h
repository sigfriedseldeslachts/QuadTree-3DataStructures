#pragma once

#include <unordered_set>
#include "AxisAlignedBoundingBox.h"

namespace std {
    template<typename T1, typename T2>
    struct hash<std::pair<T1, T2>> {
        std::size_t operator()(std::pair<T1, T2> const &p) const {
            auto h1 = std::hash<T1>()(p.first);
            auto h2 = std::hash<T2>()(p.second);

            return h1 ^ h2;
        }
    };

    template<>
    struct hash<AxisAlignedBoundingBox> {
        std::size_t operator()(AxisAlignedBoundingBox const &box) const {
            // Get a hash of all the variables and XOR them together
            auto x = std::hash<unsigned int>()(box.getX());
            auto y = std::hash<unsigned int>()(box.getY());
            auto width = std::hash<unsigned int>()(box.getWidth());
            auto height = std::hash<unsigned int>()(box.getHeight());

            return x ^ y ^ width ^ height;
        }
    };
}
