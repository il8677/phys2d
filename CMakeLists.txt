cmake_minimum_required(VERSION 3.13)

project(phys_2d)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(testworld)