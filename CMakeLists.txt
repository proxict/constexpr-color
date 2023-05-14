cmake_minimum_required(VERSION 3.0)
project(constexpr-color VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(constexpr-color INTERFACE)

# 'SYSTEM' to prevent compilers from generating warnings in projects using this library
target_include_directories(constexpr-color SYSTEM INTERFACE include)

if (BUILD_TESTS)
    add_subdirectory(test)
endif()

