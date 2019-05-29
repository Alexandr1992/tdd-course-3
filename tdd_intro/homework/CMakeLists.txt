cmake_minimum_required(VERSION 3.0)

# add subprojects
add_subdirectory(01_leap_year)
add_subdirectory(02_ternary_numbers)
add_subdirectory(03_bank_ocr)
add_subdirectory(04_weather_client)
add_subdirectory(05_coffee)

set_target_properties(01_leap_year 02_ternary_numbers 
	03_bank_ocr 04_weather_client 05_coffee
	PROPERTIES FOLDER homework
)
