cmake_minimum_required(VERSION 3.16)

find_package(odb CONFIG REQUIRED libodb sqlite)

# Core library
add_library(model_core model/store.h)
target_include_directories(model_core PUBLIC . odb::libodb)

# Model library
add_library(model_full
        model/store-odb.cxx
        model/store-odb.hxx)
target_link_libraries(model_full PUBLIC odb::libodb odb::libodb-sqlite model_core)

add_library(imgr::model_core ALIAS model_core)
add_library(imgr::model ALIAS model_full)

# Tests
if(IMGR_ENABLE_TESTING)
    find_package(Catch2 3 REQUIRED)
    include(Catch)

#    add_executable(test_data tests/test_data.cpp)
#    target_link_libraries(test_data PRIVATE data Catch2::Catch2WithMain fmt::fmt imgr::test_helper)
#    catch_discover_tests(test_data)
endif()