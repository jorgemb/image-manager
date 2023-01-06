cmake_minimum_required (VERSION 3.16)

find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(fmt CONFIG REQUIRED)
find_package(OpenEXR CONFIG REQUIRED) # Required for OpenImageIO as stated in: https://github.com/OpenImageIO/oiio/issues/2014
find_package(OpenImageIO CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)

add_library(test_helper STATIC
        test_helper/helper.h
        test_helper/helper.cpp
        )
target_include_directories(test_helper PUBLIC .)
target_link_libraries(test_helper PUBLIC yaml-cpp Boost::filesystem OpenImageIO::OpenImageIO)

add_library(imgr::test_helper ALIAS test_helper)