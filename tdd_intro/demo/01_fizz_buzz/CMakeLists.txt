cmake_minimum_required(VERSION 3.0)
project(01_fizz_buzz)

add_executable(01_fizz_buzz test.cpp)
target_link_libraries(01_fizz_buzz gtest_main)

add_test(
    NAME 01_fizz_buzz
    COMMAND 01_fizz_buzz
)

install(TARGETS 01_fizz_buzz 
	DESTINATION ${CMAKE_SOURCE_DIR}/../bin
)
