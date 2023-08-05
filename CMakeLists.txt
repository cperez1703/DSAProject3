cmake_minimum_required(VERSION 3.24)
project(dsaproject3)

set(CMAKE_CXX_STANDARD 14)

add_executable(dsaproject3 main.cpp Window.h Database.h RedBlackTree.h Artist.h HashMap.h Artist.cpp)

# Set the SFML_DIR variable to the location of SFML CMake files
set(SFML_DIR "/usr/local/Cellar/sfml/2.5.1/lib/cmake/SFML")

# Find the dynamic version of SFML libraries
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

target_link_libraries(dsaproject3 sfml-system sfml-window sfml-graphics sfml-audio)