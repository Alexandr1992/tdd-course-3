cmake_minimum_required(VERSION 3.0)
project(03_bank_ocr)

add_executable(03_bank_ocr test.cpp)
target_link_libraries(03_bank_ocr gtest_main)

add_test(
    NAME 03_bank_ocr
    COMMAND 03_bank_ocr
)

install(TARGETS 03_bank_ocr 
	DESTINATION ${CMAKE_SOURCE_DIR}/../bin
)
