cmake_minimum_required(VERSION 2.8.12)

project(parser)

get_filename_component(PRJ_ROOT "${CMAKE_SOURCE_DIR}" ABSOLUTE)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)# CACHE String)
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(PRJ_DEBUG ON)
    set(PRJ_BIN_DIR "${PRJ_ROOT}/bin/Debug")
    set(PRJ_LIB_DIR "${PRJ_ROOT}/bin/Debug/libs")
    set(CMAKE_CONFIGURATION_TYPES "Debug" CACHE STRING "" FORCE)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(PRJ_RELEASE ON)
    set(PRJ_BIN_DIR "${PRJ_ROOT}/bin/Release")
    set(PRJ_LIB_DIR "${PRJ_ROOT}/bin/Release/libs")
    set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)
else()
    message(FATAL_ERROR "Invalid CMAKE_BUILD_TYPE value (Debug|Release)")
endif()

message(STATUS "binaries output: " ${PRJ_BIN_DIR})
message(STATUS "libraries output: " ${PRJ_LIB_DIR})

# ---------------------------  paths  ---------------------------
set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY_DEBUG   ${PRJ_BIN_DIR})
set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY_RELEASE ${PRJ_BIN_DIR})
set(CMAKE_EXECUTABLE_OUTPUT_PATH              ${PRJ_BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG      ${PRJ_LIB_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE    ${PRJ_LIB_DIR})
set(CMAKE_LIBRARY_OUTPUT_PATH                 ${PRJ_LIB_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG      ${PRJ_BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE    ${PRJ_BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY            ${PRJ_BIN_DIR})

#----------------------- compile options ------------------------
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#----------------------- sources --------------------------------
if (NOT TESTS)
    set(TESTS OFF)
    set(SOURCES
        src/main.cpp
        src/LexicalAnalyzer.cpp
        src/Token.cpp
        src/Calculator.cpp
    )
elseif(${TESTS} STREQUAL "ON")
    set(SOURCES
        tests/tests.cpp
        src/LexicalAnalyzer.cpp
        src/Token.cpp
        src/Calculator.cpp
    )
endif()
message(${TESTS})
#----------------------- headers --------------------------------
include_directories(src/)

add_executable(${PROJECT_NAME} ${SOURCES})
