add_executable(tests mathtests.cpp catch_amalgamated.cpp)

target_link_libraries(tests PRIVATE phys_2d)