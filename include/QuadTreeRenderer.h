#ifndef PROJECT_QUADTREE_QUADTREERENDERER_H
#define PROJECT_QUADTREE_QUADTREERENDERER_H

#include <SDL.h>
#include <cmath>
#include <vector>
#include <string>

#include "QuadTree.h"
#include "../include/QuadTreeIterator.h"

class QuadTreeRenderer {
    private:
        SDL_Renderer *renderer = nullptr;
        SDL_Window *window = nullptr;

    public:
        QuadTreeRenderer(int height, int width);
        // Destructor
        ~QuadTreeRenderer(){
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
        }

        void drawSquareContour(int x, int y, int height, int width, int r = 255, int g = 255, int b = 255, int a = 255);
        void drawSquareContour(const AxisAlignedBoundingBox& bounds, int r = 255, int g = 255, int b = 255, int a = 255);
        void drawTree(QuadTree<int> *tree);
        void updateRenderer() {
            SDL_RenderPresent(renderer);
        }
        void clearRenderer() {
            // Clear the window and make it all black
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);
        }
};


#endif
