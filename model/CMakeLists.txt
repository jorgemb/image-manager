cmake_minimum_required(VERSION 3.16)

find_package(odb CONFIG REQUIRED libodb sqlite)

# Model library
add_library(model
        model/store.h
        model/store-odb.cxx
        model/store-odb.hxx)
target_include_directories(model PUBLIC .)
target_link_libraries(model PUBLIC odb::libodb odb::libodb-sqlite)

add_library(imgr::model ALIAS model)
