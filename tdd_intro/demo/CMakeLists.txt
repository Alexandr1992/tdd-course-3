cmake_minimum_required(VERSION 3.0)

# add subprojects
add_subdirectory(01_bob)
add_subdirectory(01_fizz_buzz)
add_subdirectory(02_anagram)
add_subdirectory(02_word_count)
add_subdirectory(03_allergies)
add_subdirectory(03_roman_numerals)
add_subdirectory(04_timer)

set_target_properties(01_bob 01_fizz_buzz 
	02_anagram 02_word_count 
	03_allergies 03_roman_numerals 04_timer
	PROPERTIES FOLDER demo
)
