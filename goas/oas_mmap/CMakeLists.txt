
cmake_minimum_required(VERSION 2.8)

find_package(BISON)
find_package(FLEX)

BISON_TARGET(MyParser src/oas_parser.y ${CMAKE_CURRENT_BINARY_DIR}/oas_parser.c)
FLEX_TARGET(MyScanner src/oas_scanner.l  ${CMAKE_CURRENT_BINARY_DIR}/oas_scanner.c)
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(bin/par
    ${BISON_MyParser_OUTPUTS}
      ${FLEX_MyScanner_OUTPUTS})

add_subdirectory (src) 
INSTALL(TARGETS bin/par  DESTINATION ${PROJECT_SOURCE_DIR}/bin)

