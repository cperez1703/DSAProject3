cmake_minimum_required(VERSION 3.24)
project(dsaproject3)

set(CMAKE_CXX_STANDARD 14)

add_executable(dsaproject3 main.cpp Window.h Database.h RedBlackTree.h main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(c:/SFML/include/SFML)
target_link_libraries(dsaproject3 sfml-system sfml-window sfml-graphics sfml-audio)