cmake_minimum_required (VERSION 3.8)

project(DFGen)

add_library(dfgen SHARED src/dfgen.h src/dfgen.cpp)

IF(WIN32)
add_compile_definitions(_WIN32=TRUE)
add_compile_definitions(WIN_EXPORT=TRUE)
ELSE()
add_compile_definitions(__CYGWIN__=TRUE)
add_compile_definitions(__GNUC__=TRUE)
ENDIF()