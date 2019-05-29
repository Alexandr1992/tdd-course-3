cmake_minimum_required(VERSION 3.0)
project(03_allergies)

add_executable(03_allergies test.cpp)
target_link_libraries(03_allergies gtest_main)

add_test(
    NAME 03_allergies
    COMMAND 03_allergies
)

install(TARGETS 03_allergies 
	DESTINATION ${CMAKE_SOURCE_DIR}/../bin
)
