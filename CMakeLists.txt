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
set(Boost_NO_WARN_NEW_VERSIONS 1)

# Parameters
set(IMGR_ENABLE_TESTING on CACHE BOOL "Enable building of tests")
message("IMGR_ENABLE_TESTING: " ${IMGR_ENABLE_TESTING})

# Add external libraries

# Catch2
if(IMGR_ENABLE_TESTING)
    find_package(Catch2 3 REQUIRED)
    set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)
    enable_testing()
    include(Catch)

    # Subdirectory with tests library
    add_subdirectory(test_helper/)
endif()

# Add subprojects
add_subdirectory(model/)
add_subdirectory(gui/)
add_subdirectory(data/)
add_subdirectory(app/)
