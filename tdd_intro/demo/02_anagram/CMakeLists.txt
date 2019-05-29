cmake_minimum_required(VERSION 3.0)
project(02_anagram)

add_executable(02_anagram test.cpp)
target_link_libraries(02_anagram gtest_main)

add_test(
    NAME 02_anagram
    COMMAND 02_anagram
)

install(TARGETS 02_anagram 
	DESTINATION ${CMAKE_SOURCE_DIR}/../bin
)
