cmake_minimum_required(VERSION 3.0)
project(02_word_count)

add_executable(02_word_count test.cpp)
target_link_libraries(02_word_count gtest_main)

add_test(
    NAME 02_word_count
    COMMAND 02_word_count
)

install(TARGETS 02_word_count 
	DESTINATION ${CMAKE_SOURCE_DIR}/../bin
)
