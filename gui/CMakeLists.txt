cmake_minimum_required (VERSION 3.16)

find_package(wxWidgets CONFIG REQUIRED)

add_library(gui STATIC
        view/view.h
        view/view.cpp
        gui/image_panel.cpp
        gui/image_panel.h gui/image_gallery.cpp gui/image_gallery.h gui/exceptions.h)
target_include_directories(gui PUBLIC .)
target_link_libraries(gui PUBLIC wx::core wx::base)
#target_link_libraries(gui PUBLIC wx::mono)

add_library(imgr::gui ALIAS gui)