cmake_minimum_required(VERSION 3.0)
project(chatclient)

add_library(
	chatclient
	igui.h
	isocketwrapper.h
	socketwrapper.h
	socketwrapper.cpp
)	
target_link_libraries(chatclient Ws2_32.lib Mswsock.lib AdvApi32.lib)

add_executable(
	chatclient_test
	mocks.h
	socketwrappertest.cpp
	test.cpp
)
target_link_libraries(chatclient_test chatclient gtest_main gmock_main)

add_test(
    NAME chatclient_test
    COMMAND chatclient_test
)

install(TARGETS 
	chatclient 
	chatclient_test
	DESTINATION ${CMAKE_SOURCE_DIR}/../bin
)
