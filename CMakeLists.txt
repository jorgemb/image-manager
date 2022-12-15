cmake_minimum_required (VERSION 3.16)

# Add vcpkg - Allow for global VCPKG installation
if(DEFINED ENV{VCPKG_ROOT})
    message("Using global VCPKG at: " $ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "Vcpkg toolchain file")
else()
    message("Using VCPKG in manifest mode")
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "Vcpkg toolchain file")
endif()

project ("image-manager" VERSION 0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# Add external libraries
#set(wxBUILD_MONOLITHIC ON)
set(wxBUILD_SHARED OFF)
add_subdirectory(third_party/wxWidgets)

# Add subprojects
add_subdirectory(gui/)
add_subdirectory(files/)

# Main file
add_executable(main WIN32 main.cpp)
target_link_libraries(main PRIVATE imgr::gui)