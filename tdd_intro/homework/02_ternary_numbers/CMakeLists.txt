cmake_minimum_required(VERSION 3.0)
project(02_ternary_numbers)

add_executable(02_ternary_numbers test.cpp)
target_link_libraries(02_ternary_numbers gtest_main)

add_test(
    NAME 02_ternary_numbers
    COMMAND 02_ternary_numbers
)

install(TARGETS 02_ternary_numbers 
	DESTINATION ${CMAKE_SOURCE_DIR}/../bin
)
