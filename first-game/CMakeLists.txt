cmake_minimum_required(VERSION 3.0.0)
project(first_game VERSION 0.1.0)

# finding and including SDL
#find_package(SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIRS})

set(ENV{LIBGL_ALWAYS_SOFTWARE} "1")


include(CTest)
enable_testing()

# copy asssets folder into build
#file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

file(GLOB_RECURSE SOURCES "src/**/*.c")
file(GLOB_RECURSE HEADERS "src/**/*.h")
# file(GLOB_RECURSE SOURCES "src/**/*.cpp")
# file(GLOB_RECURSE HEADERS "src/**/*.hpp")


add_executable(first_game src/main.c ${SOURCES} ${HEADERS})



add_subdirectory(raylib)
target_link_libraries(${PROJECT_NAME} raylib)


# Link SDL
#target_link_libraries(procedural_animations ${SDL2_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)