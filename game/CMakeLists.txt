cmake_minimum_required(VERSION 3.13)
project(physgame)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)

#add_compile_definitions(IMGUI_SFML_VIEWPORTS_ENABLE)

set(GAME_SOURCES
    Engine/GameObject.cpp
    Engine/Renderer.cpp
    Engine/Component.cpp
    Engine/BodyComponent.cpp
    
    GameObjects/Player/Player.cpp
    GameObjects/Player/Gun.cpp
    
    GameObjects/Bullets/PistolBullet.cpp
    GameObjects/Bullets/SMGBullet.cpp
    GameObjects/Bullets/RocketBullet.cpp
    GameObjects/Bullets/Bullet.cpp
    
    GameObjects/Helper/Spawner.cpp
    GameObjects/Helper/Health.cpp
    GameObjects/Helper/Loot.cpp
    GameObjects/Helper/LootDropper.cpp

    GameObjects/Enemies/EnemyController.cpp
    GameObjects/Enemies/Suicider.cpp
    GameObjects/Enemies/Shooter.cpp
    GameObjects/Enemies/Elite.cpp
    
    util/Random.cpp

    Input.cpp
    Game.cpp
)

set(GAME_ADDITIONAL_SOURCES 
    ../vendor/imgui-docking/imgui.cpp
    ../vendor/imgui-docking/imgui_draw.cpp
    ../vendor/imgui-docking/imgui_tables.cpp
    ../vendor/imgui-docking/imgui_widgets.cpp
    ../vendor/imgui-docking/imgui_demo.cpp
    ../vendor/imgui-sfml/imgui-SFML.cpp
)

add_executable(physgame main.cpp ${GAME_SOURCES} ${GAME_ADDITIONAL_SOURCES})

target_link_libraries(physgame PRIVATE phys_2d)
target_link_libraries(physgame PUBLIC OpenGL sfml-graphics sfml-window sfml-system)

target_include_directories(physgame PRIVATE ../vendor/SFML/include)
target_include_directories(physgame PRIVATE ../vendor/imgui-sfml)
target_include_directories(physgame PRIVATE ../vendor/imgui-docking)
target_include_directories(physgame PRIVATE include)

message(${CMAKE_CXX_FLAGS_DEBUG})