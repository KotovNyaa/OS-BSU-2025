cmake_minimum_required(VERSION 3.10)

project(MatrixMultLab)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/O2)
else()
    add_compile_options(-O3 -pthread)
endif()

find_package(Threads REQUIRED)

add_executable(matrix_lab 
    main.cpp 
    matrix.cpp  
)

target_link_libraries(matrix_lab PRIVATE Threads::Threads)
