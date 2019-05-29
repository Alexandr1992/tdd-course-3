cmake_minimum_required(VERSION 3.0)

# add subproject
add_subdirectory(chatclient)
set_target_properties(chatclient chatclient_test PROPERTIES FOLDER cleanroom)
