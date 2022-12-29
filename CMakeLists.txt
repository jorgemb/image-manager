cmake_minimum_required (VERSION 3.16)

# Add vcpkg - Allow for global VCPKG installation
if(DEFINED ENV{VCPKG_ROOT})
    message("Using global VCPKG at: " $ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "Vcpkg toolchain file")
else()
    message("Using VCPKG in manifest mode")
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/third_party/vcpkg/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "Vcpkg toolchain file")
endif()

project("image-manager" VERSION 0.1)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# Add external libraries

## WXWIDGETS
#set(wxBUILD_MONOLITHIC OFF)
#set(wxBUILD_SHARED OFF)
##set(wxBUILD_SAMPLES ALL)
#add_subdirectory(third_party/wxWidgets)

find_package(wxWidgets CONFIG REQUIRED)

# OpenImageIO
#find_package(OpenImageIO CONFIG REQUIRED)

# LibODB
find_package(odb CONFIG REQUIRED COMPONENTS libodb pgsql)

# Catch2
find_package(Catch2 3 REQUIRED)
set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)
enable_testing()
include(Catch)

# Add subprojects
add_subdirectory(gui/)
add_subdirectory(data/)
add_subdirectory(app/)

# Main file
add_executable(main WIN32 main.cpp)
target_link_libraries(main PRIVATE imgr::application)