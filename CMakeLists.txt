# @file CMakeLists.txt
# 
# CMake files for read experiments

cmake_minimum_required(VERSION 3.10)

# project info
project(session)

# force debug build since used for testing
set(CMAKE_BUILD_TYPE Debug)

# C++11 standard
set(CMAKE_CXX_STANDARD 17)

# Assume each .cpp file is a separate application
file(GLOB APPLICATIONS "*.cpp")

# Generate executable for each application
foreach(APP ${APPLICATIONS})

    # Use basename (no path, no extension) of .cpp file for application name
    get_filename_component(APPBASENAME "${APP}" NAME_WLE)

    # Application is based on .cpp file only
    add_executable(${APPBASENAME} ${APPBASENAME}.cpp)

endforeach()
