cmake_minimum_required(VERSION 3.16)

find_package(yaml-cpp CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(odb CONFIG REQUIRED libodb pgsql)
find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(OpenImageIO CONFIG REQUIRED)

add_library(data
        data/directory_tree.h
        data/directory_tree.cpp
        data/config.h
        data/config.cpp
        model/store.h
        model/store-odb.cxx
        model/store-odb.hxx
        data/photo_store.cpp
        data/photo_store.h)
target_include_directories(data PUBLIC .)
target_link_libraries(data PUBLIC yaml-cpp Boost::filesystem odb::libodb odb::libodb-pgsql OpenImageIO::OpenImageIO)

add_library(imgr::data ALIAS data)

# Tests
add_executable(test_data tests/test_data.cpp)
target_link_libraries(test_data PRIVATE data Catch2::Catch2WithMain fmt::fmt)
catch_discover_tests(test_data)