cmake_minimum_required (VERSION 3.16)

find_package(wxWidgets CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem)

add_library(gui STATIC
        view/view.h
        view/view.cpp
        gui/image_panel.cpp
        gui/image_panel.h gui/image_gallery.cpp gui/image_gallery.h gui/exceptions.h)
target_include_directories(gui PUBLIC .)
target_link_libraries(gui PUBLIC wx::core wx::base Boost::filesystem)

add_library(imgr::gui ALIAS gui)