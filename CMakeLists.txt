cmake_minimum_required(VERSION 3.23)
project(Project_QuadTree)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project_QuadTree src/main.cpp src/AxisAlignedBoundingBox.cpp include/AxisAlignedBoundingBox.h src/QuadTree.cpp include/QuadTree.h src/QuadTreeRenderer.cpp include/QuadTreeRenderer.h include/QuadTreeIterator.h include/PairHash.h)

# Create separate target for tests
add_executable(Project_QuadTree_tests lib/catch.hpp src/AxisAlignedBoundingBox.cpp include/AxisAlignedBoundingBox.h src/QuadTree.cpp include/QuadTree.h include/QuadTreeIterator.h tests/Tests.cpp include/PairHash.h)

# Include SDL2
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})

target_link_libraries(Project_QuadTree ${SDL2_LIBRARIES})

target_compile_options(
        Project_QuadTree
        PUBLIC
        -Wall -Wextra -Wpedantic -Werror
)
