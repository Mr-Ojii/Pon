cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Pon CXX)
file(GLOB_RECURSE source src/*.cpp)
add_executable(${PROJECT_NAME} ${source})

set(ADD_INCLUDE_DIR CACHE PATH "Additional include directory")

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(tomlplusplus REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE ${ADD_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2_mixer::SDL2_mixer)
