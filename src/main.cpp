#include <iostream>
#include <chrono>
#include <fstream>

#include "../include/AxisAlignedBoundingBox.h"
#include "../include/QuadTree.h"
#include "../include/QuadTreeRenderer.h"

#define HEIGHT 800
#define WIDTH 800
#define GENERATE_POINTS 10000
#define TIME_ITERATIONS 100

void measureTime();

int main() {
    // Create a new render window
    QuadTreeRenderer window(HEIGHT, WIDTH);

    // Create a new AABB tree with a capacity of 4
    QuadTree<int> root_tree(AxisAlignedBoundingBox(2, 2, HEIGHT - 4, WIDTH - 4), 1);

    root_tree.insert(AxisAlignedBoundingBox(100, 100, 100, 100), 1); // Insert to the left
    root_tree.insert(AxisAlignedBoundingBox(350, 350, 100, 100), 2); // Insert in middle
    root_tree.insert(AxisAlignedBoundingBox(200, 200, 100, 100), 3);
    root_tree.insert(AxisAlignedBoundingBox(700, 700, 100, 100), 4);
    root_tree.insert(AxisAlignedBoundingBox(300, 300, 100, 100), 5);
    root_tree.insert(AxisAlignedBoundingBox(600, 600, 20, 20), 6);

    // Print amount of AABBs
    std::cout << "Amount of AABBs: " << root_tree.get_as_vector().size() << std::endl;

    // Draw the root tree
    window.drawTree(&root_tree);

    // Test if we can query
    AxisAlignedBoundingBox aabb(550, 550, 200, 200);
    std::cout << "Amount in area is: " << root_tree.query(aabb).size() << std::endl;
    //window.drawSquareContour(aabb, 0, 0, 255, 255);

    // Update the renderer
    window.updateRenderer();

    // Measure the time it takes to iterate over the tree
    measureTime();
    std::cout << "Calculated the graph timings" << std::endl;

    SDL_Event event;
    while (event.type != SDL_QUIT){
        SDL_Delay(10);  // setting some Delay
        SDL_PollEvent(&event);  // Catching the poll event.
    }

    return 0;
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
}