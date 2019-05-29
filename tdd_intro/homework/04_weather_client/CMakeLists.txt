cmake_minimum_required(VERSION 3.0)
project(04_weather_client)

add_executable(04_weather_client test.cpp)
target_link_libraries(04_weather_client gtest_main gmock_main)

add_test(
    NAME 04_weather_client
    COMMAND 04_weather_client
)

install(TARGETS 04_weather_client 
	DESTINATION ${CMAKE_SOURCE_DIR}/../bin
)
