cmake_minimum_required(VERSION 3.10)

project(LibrariesExample CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(numberLIB)
add_subdirectory(vectorLIB)
add_subdirectory(main)
