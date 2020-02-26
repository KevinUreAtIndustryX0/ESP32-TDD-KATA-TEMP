cmake_minimum_required(VERSION 3.5)

# (Not part of the boilerplate)
# This example uses an extra component for common functions such as Wi-Fi and Ethernet connection.
set(EXTRA_COMPONENT_DIRS $ENV{IDF_PATH}/examples/common_components/protocol_examples_common)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

# If we call cmake from CI with -DGitTag=v1.2.3 we use it for semantic versioning,
# otherwise we should report the build timestamp for local builds.
SET(GitTag "v0.0.0" CACHE STRING "optional github release tag")

project(hello-world LANGUAGES C CXX)
message(STATUS "building " ${CMAKE_PROJECT_NAME} " from GitTag " ${GitTag})

string(REPLACE "-" "_" TEMP_PROJECT_NAME ${CMAKE_PROJECT_NAME})
SET(CPROJECT_NAME "${TEMP_PROJECT_NAME}" CACHE STRING "C-Identifier-Friendly project name")

configure_file(CmakeConfig.h.in CmakeConfig.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_BINARY_DIR})

