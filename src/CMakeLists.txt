set(CMAKE_CXX_STANDARD 20)

set(PHYS_SOURCES
    maths/vec2.cpp
    maths/mat2.cpp
    maths/Rotation.cpp
    maths/Broadphase.cpp

    Body.cpp
    World.cpp
    colliders/Shape.cpp
    common/Contact.cpp
    colliders/Collision.cpp
)

set(PHYS_HEADERS
    ../include/vec2.h
    ../maths/rotation.h

    ../body.h
    ../world.h
)

add_library(phys_2d STATIC ${PHSY_HEADERS} ${PHYS_SOURCES})

target_include_directories(phys_2d PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
