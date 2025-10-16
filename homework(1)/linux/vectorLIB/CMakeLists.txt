add_library(vectorLIB SHARED
    vector.cpp
    vector.h
)

target_include_directories(vectorLIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(vectorLIB PUBLIC numberLIB)
