
cmake_minimum_required(VERSION 2.8)

SET(OAS_DIR_LIB "${PROJECT_SOURCE_DIR}/lib" CACHE STRING "Options: [$ENV{HOME}/oas]")

SET(LIBNAME oas)

SET(SOURCES
    Relation.cpp
    Record.cpp
    Record1.cpp
    scan.cpp
    MMapLinux.cpp
    Meta.cpp
    StringUtilities.cpp
)

ADD_LIBRARY(${LIBNAME} STATIC ${SOURCES})

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include/)

INSTALL(TARGETS ${LIBNAME} ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib)     





