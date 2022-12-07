#include <iostream>
#include <chrono>

#include "../include/AxisAlignedBoundingBox.h"
#include "../include/QuadTree.h"
#include "../include/QuadTreeRenderer.h"

#define HEIGHT 800
#define WIDTH 800
#define GENERATE_POINTS 20

int main() {
    // Create a new render window
    QuadTreeRenderer window(HEIGHT, WIDTH);

    // Create a new AABB tree with a capacity of 4
    QuadTree<int> root_tree(AxisAlignedBoundingBox(2, 2, HEIGHT - 4, WIDTH - 4), 1);

    root_tree.insert(AxisAlignedBoundingBox(100, 100, 100, 100), 1);
    root_tree.insert(AxisAlignedBoundingBox(200, 200, 100, 100), 2);
    root_tree.insert(AxisAlignedBoundingBox(700, 700, 100, 100), 3);

    // Insert in the south-west region
    root_tree.insert(AxisAlignedBoundingBox(600, 600, 20, 20), 5);

    // Print amount of AABBs
    std::cout << "Amount of AABBs: " << root_tree.get_as_vector().size() << std::endl;

    // Draw the root tree
    window.drawTree(&root_tree);

    std::cout << "Amount in area is: " << root_tree.query(AxisAlignedBoundingBox(550, 550, 100, 100)).size() << std::endl;

    SDL_Event event;
    while (event.type != SDL_QUIT){
        SDL_Delay(10);  // setting some Delay
        SDL_PollEvent(&event);  // Catching the poll event.
    }
}
