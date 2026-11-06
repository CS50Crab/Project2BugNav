cmake_minimum_required(VERSION 3.28)
project(BugNavGraphics LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# download the graphics library once
include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON)
FetchContent_MakeAvailable(SFML)

add_executable(bug_nav_graphics
    src/main.cpp
    src/Map.cpp
    src/Tile.cpp
    src/Bug.cpp
    src/BugNav1.cpp
    src/BugNav2.cpp)
target_link_libraries(bug_nav_graphics PRIVATE SFML::Graphics)
if(MINGW)
    target_link_options(bug_nav_graphics PRIVATE -static-libgcc -static-libstdc++)
endif()
