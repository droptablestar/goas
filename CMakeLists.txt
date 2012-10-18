
cmake_minimum_required(VERSION 2.8)

project(OAS)

find_package(BISON)
find_package(FLEX)

BISON_TARGET(MyParser src/oas_parser.y src/oas_parser.c)
FLEX_TARGET(MyScanner src/oas_scanner.l  src/oas_scanner.c)
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../lib)

add_executable(bin/par
    ${BISON_MyParser_OUTPUTS}
      ${FLEX_MyScanner_OUTPUTS})

add_subdirectory(src) 
INSTALL(TARGETS bin/par  DESTINATION ${OAS_SRC_DIR}/bin)

