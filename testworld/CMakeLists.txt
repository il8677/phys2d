cmake_minimum_required(VERSION 3.13)
project(phystest)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)

add_compile_definitions(PHYS_2D_DEBUG)
#add_compile_definitions(IMGUI_SFML_VIEWPORTS_ENABLE)

set(TEST_SOURCES
    GameObject.cpp
    Renderer.cpp
    Input.cpp
)

set(TEST_ADDITIONAL_SOURCES 
    ../vendor/imgui-docking/imgui.cpp
    ../vendor/imgui-docking/imgui_draw.cpp
    ../vendor/imgui-docking/imgui_tables.cpp
    ../vendor/imgui-docking/imgui_widgets.cpp
    ../vendor/imgui-docking/imgui_demo.cpp
    ../vendor/imgui-sfml/imgui-SFML.cpp
)

add_executable(phystest test.cpp ${TEST_SOURCES} ${TEST_ADDITIONAL_SOURCES})

target_link_libraries(phystest PRIVATE phys_2d)
target_link_libraries(phystest PUBLIC OpenGL sfml-graphics sfml-window sfml-system)

target_include_directories(phystest PRIVATE ../vendor/SFML/include)
target_include_directories(phystest PRIVATE ../vendor/imgui-sfml)
target_include_directories(phystest PRIVATE ../vendor/imgui-docking)