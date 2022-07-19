cmake_minimum_required(VERSION 3.13)
project(phystest)

add_executable(phystest test.cpp)

add_subdirectory(phys2d)
add_subdirectory(vendor/SFML)

target_link_libraries(phystest PRIVATE phys_2d)
target_link_libraries(phystest PRIVATE GL sfml-graphics sfml-window sfml-system)

target_include_directories(phystest PRIVATE vendor/SFML/include)