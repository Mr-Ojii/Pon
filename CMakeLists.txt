cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Pon CXX)
file(GLOB_RECURSE source src/*.cpp)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_executable(${PROJECT_NAME} ${source})

set(ADD_INCLUDE_DIR CACHE PATH "Additional include directory")

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(tomlplusplus REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE ${ADD_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2_mixer::SDL2_mixer)

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
  set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()
