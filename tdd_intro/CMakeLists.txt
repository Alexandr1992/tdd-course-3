cmake_minimum_required(VERSION 3.0)
project(tdd-course-3)

# to run tests after build
enable_testing()

# turn on using solution folders for IDE
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Compiler flags
# /MT, /MTd - for static linkage
# /W4 - warning level 4
# /MP - to compile by several threads
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /MP")

# add gtest and gmock as subprojects
add_subdirectory(3rd_party/googletest EXCLUDE_FROM_ALL)

# organize targets in an IDE
set_target_properties(gtest gtest_main gmock_main PROPERTIES FOLDER 3rd-party/GTest)

include_directories(3rd_party/googletest/googletest/include)
include_directories(3rd_party/googletest/googlemock/include)

add_subdirectory(homework)
add_subdirectory(demo)
add_subdirectory(cleanroom)
