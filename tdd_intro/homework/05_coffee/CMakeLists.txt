cmake_minimum_required(VERSION 3.0)
project(05_coffee)

add_executable(05_coffee test.cpp)
target_link_libraries(05_coffee gtest_main gmock_main)

add_test(
    NAME 05_coffee
    COMMAND 05_coffee
)

install(TARGETS 05_coffee 
	DESTINATION ${CMAKE_SOURCE_DIR}/../bin
)
