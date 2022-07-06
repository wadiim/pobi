cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(CarRental)
enable_language(CXX)

add_subdirectory(library)
add_subdirectory(program)

enable_testing()
