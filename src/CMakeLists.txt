
cmake_minimum_required(VERSION 2.8)

SET(OAS_DIR_LIB "${PROJECT_SOURCE_DIR}/lib" CACHE STRING "Options: [$ENV{HOME}/oas]")

SET(LIBNAME oas)

SET(SOURCES
    Relation.cpp
    scan.cpp
    sort.cpp
    MMapLinux.cpp
    Meta.cpp
    StringUtilities.cpp
    IntegerField.cpp
    RawStringField.cpp
)

ADD_LIBRARY(${LIBNAME} STATIC ${SOURCES})

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include/)

INSTALL(TARGETS ${LIBNAME} ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib)     





