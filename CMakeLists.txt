cmake_minimum_required(VERSION 3.13)

set(CMAKE_OSX_ARCHITECTURES arm64;x86_64)

project(phys_2d)

set(CMAKE_CXX_STANDARD 17)

if(UNIX)
	set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wextra")
	set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -fsanitize=address")
	set(CMAKE_XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT "dwarf-with-dsym")
endif(UNIX)

add_subdirectory(src)
add_subdirectory(vendor/SFML)
add_subdirectory(tests)
add_subdirectory(testworld)
