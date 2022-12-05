#include <iostream>
#include <chrono>

#include "../include/AxisAlignedBoundingBox.h"
#include "../include/QuadTree.h"
#include "../include/QuadTreeRenderer.h"

#define HEIGHT 500
#define WIDTH 500
#define GENERATE_POINTS 1000

int main() {
    // Create a new render window
    QuadTreeRenderer window(HEIGHT, WIDTH);

    // Create a new AABB tree with a capacity of 4
    QuadTree<int> root_tree(AxisAlignedBoundingBox(2, 2, HEIGHT - 4, WIDTH - 4), 1);

    // Insert some AABBs
    root_tree.insert(AxisAlignedBoundingBox(10, 10, 10, 10), 1);
    root_tree.insert(AxisAlignedBoundingBox(20, 20, 10, 10), 2);
    root_tree.insert(AxisAlignedBoundingBox(30, 30, 10, 10), 3);
    root_tree.insert(AxisAlignedBoundingBox(40, 40, 10, 10), 4);

    // Print amount of AABBs
    std::cout << "Amount of AABBs: " << root_tree.get_as_vector().size() << std::endl;

    // Draw the root tree
    window.drawTree(&root_tree);

    SDL_Event event;
    while (event.type != SDL_QUIT){
        SDL_Delay(10);  // setting some Delay
        SDL_PollEvent(&event);  // Catching the poll event.
    }
}
