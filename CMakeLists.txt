cmake_minimum_required(VERSION 3.21)

set(VCPKG_MANIFEST_MODE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("ModelViewer")

file(GLOB_RECURSE SOURCE_FOLDER "src/*.h" "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_FOLDER})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

find_package(SDL3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

find_package(bgfx CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE bgfx::bx bgfx::bgfx bgfx::bimg bgfx::bimg_decode)