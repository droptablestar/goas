
cmake_minimum_required(VERSION 2.8)

SET(OAS_DIR_LIB "../lib" CACHE STRING "Options: [$ENV{HOME}/oas]")

SET(LIBNAME oas)

SET(SOURCES
    project.c
    record.c
    scan.c
    select.c
    sort.c
)

ADD_LIBRARY(${LIBNAME} STATIC ${SOURCES})

INCLUDE_DIRECTORIES(../include/)

INSTALL(TARGETS ${LIBNAME}  DESTINATION ${PROJECT_SOURCE_DIR}/${OAS_DIR_LIB})     





