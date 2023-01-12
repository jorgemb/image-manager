cmake_minimum_required(VERSION 3.16)

find_package(yaml-cpp CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(OpenEXR CONFIG REQUIRED) # Required for OpenImageIO as stated in: https://github.com/OpenImageIO/oiio/issues/2014
find_package(OpenImageIO CONFIG REQUIRED)

add_library(data
        data/directory_tree.h
        data/directory_tree.cpp
        data/config.h
        data/config.cpp
        data/photo_store.cpp
        data/photo_store.h
        )
target_include_directories(data PUBLIC .)
target_link_libraries(data PUBLIC imgr::model yaml-cpp Boost::filesystem OpenImageIO::OpenImageIO)

add_library(imgr::data ALIAS data)

# Tests
if(IMGR_ENABLE_TESTING)
    find_package(Catch2 3 REQUIRED)
    include(Catch)

    add_executable(test_data tests/test_data.cpp)
    target_link_libraries(test_data PRIVATE data Catch2::Catch2WithMain fmt::fmt imgr::test_helper)
    catch_discover_tests(test_data)
endif()