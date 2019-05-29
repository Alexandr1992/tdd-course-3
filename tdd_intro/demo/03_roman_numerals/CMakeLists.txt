cmake_minimum_required(VERSION 3.0)
project(03_roman_numerals)

add_executable(03_roman_numerals test.cpp)
target_link_libraries(03_roman_numerals gtest_main)

add_test(
    NAME 03_roman_numerals
    COMMAND 03_roman_numerals
)

install(TARGETS 03_roman_numerals 
	DESTINATION ${CMAKE_SOURCE_DIR}/../bin
)
