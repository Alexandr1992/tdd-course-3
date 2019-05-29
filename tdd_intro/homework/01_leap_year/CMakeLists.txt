cmake_minimum_required(VERSION 3.0)
project(01_leap_year)

add_executable(01_leap_year test.cpp)
target_link_libraries(01_leap_year gtest_main)

add_test(
    NAME 01_leap_year
    COMMAND 01_leap_year
)

install(TARGETS 01_leap_year 
	DESTINATION ${CMAKE_SOURCE_DIR}/../bin
)
