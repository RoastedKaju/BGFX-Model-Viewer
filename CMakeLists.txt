cmake_minimum_required(VERSION 3.21)

set(VCPKG_MANIFEST_MODE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("ModelViewer")

file(GLOB_RECURSE SOURCE_FOLDER "src/*.h" "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_FOLDER})

find_package(SDL3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)