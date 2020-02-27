#########################################################################
#                                                                       #
#     BUILD SRC AS A NATIVE LIBRARY THAT CAN BE LINKED TO THE TESTS     #
#                                                                       #
#########################################################################
cmake_minimum_required(VERSION 3.5)


project(hello-world-tests LANGUAGES C CXX)
set(LIB_NAME ourSampleApp)

include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# we use this to get code coverage
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

# go get gtest and pull it in
include(cmake/googletest.cmake)
fetch_googletest(
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_BINARY_DIR}/googletest
    )

# these are for use in file discovery done below
set(COMPONENTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../components")
set(SRC_MAIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../main")


#########################################
#   THIS BLOCK FINDS ALL SOURCE FILES   #
#########################################
set(SEARCH_DIR "")
MACRO(DISCOVER_ALL_SRC_FILES return_list)
    FILE(GLOB_RECURSE new_list ${SEARCH_DIR}/*.c)
    SET(${return_list} ${new_list})
ENDMACRO()
set(SEARCH_DIR ${COMPONENTS_DIR})
DISCOVER_ALL_SRC_FILES(APP_COMP_SRCS)
set(SEARCH_DIR ${SRC_MAIN_DIR})
DISCOVER_ALL_SRC_FILES(APP_MAIN_SRCS)
set(APP_SOURCES ${APP_COMP_SRCS} ${APP_MAIN_SRCS})
message(STATUS "ALL DISCOVERED SRC FILES: ${APP_SOURCES}")


#########################################
#   THIS BLOCK FINDS ALL HEADER FILES   #
#########################################
MACRO(DISCOVER_ALL_HEADER_FILES return_list)
    FILE(GLOB_RECURSE new_list ${SEARCH_DIR}/*.h)
    SET(${return_list} ${new_list})
ENDMACRO()
set(SEARCH_DIR ${COMPONENTS_DIR})
DISCOVER_ALL_HEADER_FILES(APP_COMP_HEADERS)
set(SEARCH_DIR ${SRC_MAIN_DIR})
DISCOVER_ALL_HEADER_FILES(APP_MAIN_HEADERS)
set(APP_HEADERS_QUALIFIED_PATHS ${APP_COMP_HEADERS} ${APP_MAIN_HEADERS})
message(STATUS "ALL DISCOVERED HEADER FILES: ${APP_HEADERS_QUALIFIED_PATHS}")


#################################################################
#   THIS BLOCK DISCOVERS ALL DIRECTORIES WITH HEADERS IN THEM   #
#################################################################
MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list ${SEARCH_DIR}/*.h)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()
set(SEARCH_DIR ${COMPONENTS_DIR})
HEADER_DIRECTORIES(HEADER_COMP_DIR_LIST)
set(SEARCH_DIR ${SRC_MAIN_DIR})
HEADER_DIRECTORIES(HEADER_MAIN_DIR_LIST)
set(HEADER_DIR_LIST ${HEADER_COMP_DIR_LIST} ${HEADER_MAIN_DIR_LIST})
message(STATUS "HEADER DIRS: ${HEADER_DIR_LIST}")

#############################################################################
#   THIS BLOCK CONFIGURES THE LIBRARY TO BE BUILT WITH THE ABOVE SETTINGS   #
#############################################################################
add_library(${LIB_NAME} "")
target_sources(
    ${LIB_NAME} # same as library name
    PRIVATE
        ${APP_SOURCES}
    PUBLIC
        ${APP_HEADERS_QUALIFIED_PATHS}
    )
target_include_directories(
    ${LIB_NAME} # same as library name
    PUBLIC
        ${HEADER_DIR_LIST}
    )


###################################################################
#                                                                 #
#     DISCOVER AND BUILD TEST EXECUTABLES (ONE PER TEST FILE)     #
#                                                                 #
###################################################################
set(CMAKE_CXX_STANDARD 14)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/mocks)

#######################################
#   THIS BLOCK FINDS ALL TEST FILES   #
#######################################
MACRO(DISCOVER_ALL_TEST_FILES return_list)
    FILE(GLOB_RECURSE new_list ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
    SET(file_list "")
    FOREACH(file_path ${new_list})
        string( REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" relative_path ${file_path} )
        SET(file_list ${file_list} ${relative_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES file_list)
    SET(${return_list} ${file_list})
ENDMACRO()
DISCOVER_ALL_TEST_FILES(APP_SOURCES)
message(STATUS "ALL DISCOVERED TEST FILES: ${APP_SOURCES}")


#################################################
#   QUEUE UP AN EXECUTABLE FOR EACH TEST FILE   #
#################################################
foreach( testsourcefile ${APP_SOURCES} )
    string( REPLACE ".cpp" "" testname ${testsourcefile} )
    GET_FILENAME_COMPONENT(exename ${testname} NAME)
    add_executable( ${exename} ${testsourcefile} )
    target_include_directories(${exename} PUBLIC "${PROJECT_BINARY_DIR}" )
    target_link_libraries( ${exename} gtest_main ${LIB_NAME} )
endforeach( testsourcefile ${APP_SOURCES} )
