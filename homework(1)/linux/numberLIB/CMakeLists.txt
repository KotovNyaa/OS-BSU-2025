add_library(numberLIB STATIC
    number.cpp
    number.h
)

set_property(TARGET numberLIB PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(numberLIB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
