cmake_minimum_required (VERSION 3.16)

add_library(files
        include/files/tree.h
        src/tree.cpp
        )
target_include_directories(files PUBLIC include/)
#target_link_libraries(files PUBLIC wx::core wx::base wx::media)
#target_link_libraries(gui PUBLIC wx::mono)

add_library(imgr::files ALIAS files)