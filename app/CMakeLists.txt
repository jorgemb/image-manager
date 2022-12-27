cmake_minimum_required (VERSION 3.16)

add_library(application STATIC
        app/Application.h
        app/Application.cpp
        )
target_include_directories(application PUBLIC .)
target_link_libraries(application PUBLIC imgr::gui imgr::data)
#target_link_libraries(gui PUBLIC wx::mono)

add_library(imgr::application ALIAS application)