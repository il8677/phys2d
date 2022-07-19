cmake_minimum_required(VERSION 3.13)
project(phystest)

set(TEST_ADDITIONAL_SOURCES 
    vendor/imgui-docking/imgui.cpp
    vendor/imgui-docking/imgui_draw.cpp
    vendor/imgui-docking/imgui_tables.cpp
    vendor/imgui-docking/imgui_widgets.cpp
    vendor/imgui-docking/imgui_demo.cpp
    vendor/imgui-sfml/imgui-SFML.cpp
)

add_subdirectory(vendor/SFML)

set(CMAKE_CXX_STANDARD 17)
add_executable(phystest test.cpp ${TEST_ADDITIONAL_SOURCES})

add_subdirectory(phys2d)

target_link_libraries(phystest PRIVATE phys_2d)
target_link_libraries(phystest PUBLIC OpenGL sfml-graphics sfml-window sfml-system)

target_include_directories(phystest PRIVATE vendor/SFML/include)
target_include_directories(phystest PRIVATE vendor/imgui-sfml)
target_include_directories(phystest PRIVATE vendor/imgui-docking)