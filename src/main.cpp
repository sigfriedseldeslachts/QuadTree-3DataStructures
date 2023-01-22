#include <iostream>
#include <chrono>
#include <fstream>
#include <experimental/random>

#include "../include/AxisAlignedBoundingBox.h"
#include "../include/QuadTree.h"
#include "../include/QuadTreeRenderer.h"

#define HEIGHT 800
#define WIDTH 800
#define GENERATE_POINTS 10000
#define TIME_ITERATIONS 100

// Create a new render window
QuadTreeRenderer window(HEIGHT, WIDTH);

using std::experimental::randint;

void measureTime();
void drawNewTree();

int main() {
    drawNewTree();

    // Measure the time it takes to iterate over the tree
    //measureTime();

    SDL_Event event;
    while (event.type != SDL_QUIT){
        SDL_Delay(10);  // setting some Delay
        SDL_PollEvent(&event);  // Catching the poll event.

        // On space press, draw a new tree
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
            drawNewTree();
        }
    }

    return 0;
}

void drawNewTree() {
    // Clear the window
    window.clearRenderer();

    // Create a new AABB tree with a capacity of 4
    QuadTree<int> root_tree(AxisAlignedBoundingBox(2, 2, HEIGHT - 4, WIDTH - 4), 1); // -4 to avoid drawing on the edge of the window

    // Get a random bounding box in the root with a max size of 100
    AxisAlignedBoundingBox bounds(randint(4, WIDTH - 304), randint(4, HEIGHT - 304), 300, 300);

    // Inside the requested bounds, generate a random number of points
    int number_of_items_in_box = randint(1, 3);
    for (int i = 0; i < number_of_items_in_box; i++) {
        // Get a random bounding box in the requested bounds with a max size of 10
        AxisAlignedBoundingBox bounding_box(randint(bounds.getX(), bounds.getX() + bounds.getWidth()), randint(bounds.getY(), bounds.getY() + bounds.getHeight()), randint(30, 70), randint(30, 70));

        // Insert the bounding box into the root
        root_tree.insert(bounding_box, i);
    }

    // Outside the requested bounds, make a random number of max 10 items
    int number_of_items_outside_box = randint(1, 10);
    for (int i = 0; i < number_of_items_outside_box; i++) {
        // Get a random bounding box outside of the requested bounds with a max size of 100
        AxisAlignedBoundingBox bounding_box(randint(0, WIDTH - 100), randint(0, WIDTH - 100), randint(20, 100), randint(20, 100));

        // Insert the bounding box into the root
        root_tree.insert(bounding_box, i);
    }

    std::cout << "Amount of items created inside the bounds: " << number_of_items_in_box << std::endl;

    // Draw the root tree
    window.drawTree(&root_tree);

    // Test if we can query
    std::cout << "Items counted via query inside the bounds: " << root_tree.query(bounds).size() << std::endl;
    window.drawSquareContour(bounds, 0, 0, 255, 255);

    // Update the renderer
    window.updateRenderer();
}

void measureTime() {
    long times[TIME_ITERATIONS]; // Array of floats to store the times

    for (int i = 0; i < TIME_ITERATIONS; i++) {
        int points_to_create = GENERATE_POINTS * (i + 1);

        // Create a QuadTree with a capacity of 1
        QuadTree<int> root(AxisAlignedBoundingBox(0, 0, 1000, 1000), 1);

        // Insert a lot of random points
        for (int j = 0; j < points_to_create; j++) {
            root.insert(AxisAlignedBoundingBox(rand() % 1000, rand() % 1000, 1, 1), j);
        }

        // Measure the time it takes to query the tree
        auto start = std::chrono::high_resolution_clock::now();

        // Query the whole tree
        root.query(AxisAlignedBoundingBox(0, 0, 100, 100));

        auto end = std::chrono::high_resolution_clock::now();

        // Store the time in the array
        times[i] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }

    // Create a csv file with the times
    std::ofstream file;
    file.open("times.csv");
    for (int i = 0; i < TIME_ITERATIONS; i++) {
        file << GENERATE_POINTS * (i + 1) << "," << times[i] << std::endl;
    }
    file.close();

    std::cout << "Calculated the graph timings" << std::endl;
}