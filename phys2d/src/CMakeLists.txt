set(PHYS_SOURCES
    maths/vec2.cpp
)

set(PHYS_HEADERS
    ../include/vec2.h
)

add_library(phys_2d ${PHSY_HEADERS} ${PHYS_SOURCES})

target_include_directories(phys_2d PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})