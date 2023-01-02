cmake_minimum_required (VERSION 3.16)

find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(fmt CONFIG REQUIRED)
find_package(Catch2 3 REQUIRED)

set(APPLICATION_SRC
        app/album_manager.cpp
        app/album_manager.h)

set(APPLICATION_MAIN
        app/application.h
        app/application.cpp )

if(WIN32)
    add_executable(image_manager WIN32 ${APPLICATION_MAIN} ${APPLICATION_SRC})
else()
    add_executable(image_manager ${APPLICATION_MAIN} ${APPLICATION_SRC})
endif()
target_include_directories(image_manager PUBLIC .)
target_link_libraries(image_manager PUBLIC imgr::gui imgr::data Boost::filesystem)


# Tests
include(Catch)

add_executable(test_app ${APPLICATION_SRC})
target_include_directories(test_app PRIVATE Catch2::Catch2WithMain fmt::fmt)
catch_discover_tests(test_app)