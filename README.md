# Quad Tree

This is an implementation for a Quad Tree in C++ for 2D points.

## Extra requirements

- [SDL](https://www.libsdl.org) (for graphics)

## Usage

The main program (`main.cpp`) is a simple example of how to use the Quad Tree. It creates a Quad Tree with a given size and inserts random points in it. Then, it draws the Quad Tree and the points in a window. The space bar can be used to regenerate points and show a new Quad Tree. The blue square represents the query region.

### Time complexity
A `measureTime()` function is also present, it runs the algorithm a few thousand times and puts the results in a csv file, this can then be used to plot the time complexity of the algorithm. 

## Notes
There are two random point generators in the main function. One is to make sure that there are always points inside the query region. The other is to populate the other area. Sometimes the last one puts points inside the query region, therefore the program can state it has inserted 3 points but there are actually 4 points in the query region.