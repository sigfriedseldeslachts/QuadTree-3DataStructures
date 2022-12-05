cmake_minimum_required(VERSION 3.23)
project(Project_QuadTree)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project_QuadTree src/main.cpp src/AxisAlignedBoundingBox.cpp include/AxisAlignedBoundingBox.h src/QuadTree.cpp include/QuadTree.h src/Window.cpp include/Window.h)

# Include SDL2
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})

#[[
# Add Catch2
Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.2.0
)
FetchContent_MakeAvailable(Catch2)
target_link_libraries(Project_QuadTree Catch2::Catch2)]]

target_link_libraries(Project_QuadTree ${SDL2_LIBRARIES})
