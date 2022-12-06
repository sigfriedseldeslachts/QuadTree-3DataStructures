#include "../include/QuadTreeRenderer.h"
#include <iostream>

QuadTreeRenderer::QuadTreeRenderer(int height, int width) : height(height), width(width) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(100);
}

void QuadTreeRenderer::drawSquareContour(int x, int y, int height, int width, int r, int g, int b, int a) {
    SDL_Rect rect = {x, y, width, height};
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderDrawRect(renderer, &rect);
}

void QuadTreeRenderer::drawSquareContour(const AxisAlignedBoundingBox &bounds, int r, int g, int b, int a) {
    drawSquareContour( (int) bounds.getX(), (int) bounds.getY(), (int) bounds.getHeight(), (int) bounds.getWidth(), r, g, b, a);
}

void QuadTreeRenderer::update() {
    SDL_RenderPresent(renderer);
}

void QuadTreeRenderer::drawTree(QuadTree<int> *tree) {
    for (QuadTreeIterator<int> it = tree->begin(); it != tree->end(); ++it)
    {
        std::vector<std::pair<AxisAlignedBoundingBox, int>> points = *it;
        for (auto point : points)
        {
            // Draws the bounding box of the points
            drawSquareContour(point.first, 255, 255, 255, 255);
        }

        // Prints the amount of points in the current node
        std::cout << "Amount of points in current node: " << points.size() << std::endl;

        // This draws the bounding box of the current tree
        drawSquareContour(it.tree().getBounds(), 0, 255, 0, 255);
    }

    SDL_RenderPresent(renderer);
}
