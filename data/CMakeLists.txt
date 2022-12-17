cmake_minimum_required (VERSION 3.16)

find_package(yaml-cpp CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

add_library(data
        include/data/directory_tree.h
        include/data/config.h
        src/directory_tree.cpp
        src/config.cpp
        )
target_include_directories(data PUBLIC include/)
target_link_libraries(data PUBLIC yaml-cpp)

add_library(imgr::data ALIAS data)

# Tests
add_executable(test_data tests/test_data.cpp)
target_link_libraries(test_data PRIVATE data Catch2::Catch2WithMain fmt::fmt)
catch_discover_tests(test_data)