cmake_minimum_required(VERSION 3.0)

GETSUBDIRLIST(PROJECTS ${CMAKE_CURRENT_SOURCE_DIR})

foreach(PROJ ${PROJECTS})
    project(${PROJ})

    if(${PROJ} STREQUAL "01_bob")
        # Steps.cpp contains compile errors
        FILE(GLOB SOURCES_FILES ${PROJ}/test.cpp)
    else()
        FILE(GLOB SOURCES_FILES ${PROJ}/*.h ${PROJ}/*.cpp)
    endif()
	
    add_executable(${PROJ} ${SOURCES_FILES})
    target_link_libraries(${PROJ} gtest_main gmock_main)

    add_test(NAME ${PROJ} COMMAND ${PROJ})
endforeach()

set_target_properties(${PROJECTS} PROPERTIES FOLDER demo)

install(TARGETS ${PROJECTS} DESTINATION ${CMAKE_SOURCE_DIR}/../bin)
