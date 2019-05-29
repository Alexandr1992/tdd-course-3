cmake_minimum_required(VERSION 3.0)
project(01_bob)

# Steps.cpp is not added because it does not include gtest header
# and contains compile errors
add_executable(01_bob test.cpp)
target_link_libraries(01_bob gtest_main)

add_test(
    NAME 01_bob
    COMMAND 01_bob
)

install(TARGETS 01_bob 
	DESTINATION ${CMAKE_SOURCE_DIR}/../bin
)
