cmake_minimum_required (VERSION 3.16)

add_library(gui STATIC
        gui/gui.h
        gui/gui.cpp
        gui/image_panel.cpp gui/image_panel.h)
target_include_directories(gui PUBLIC .)
target_link_libraries(gui PUBLIC wx::core wx::base wx::media)
#target_link_libraries(gui PUBLIC wx::mono)

add_library(imgr::gui ALIAS gui)