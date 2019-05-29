cmake_minimum_required(VERSION 3.0)
project(04_timer)

add_executable(04_timer test.cpp)
target_link_libraries(04_timer gtest_main)

add_test(
    NAME 04_timer
    COMMAND 04_timer
)

install(TARGETS 04_timer 
	DESTINATION ${CMAKE_SOURCE_DIR}/../bin
)
