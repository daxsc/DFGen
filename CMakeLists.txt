cmake_minimum_required (VERSION 3.8)

project(DFGen)

add_library(dfgen SHARED src/dfgen.h src/dfgen.cpp)
set_target_properties(dfgen PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")

IF(WIN32)
add_compile_definitions(_WIN32=TRUE)
add_compile_definitions(WIN_EXPORT=TRUE)
ELSE()
add_compile_definitions(__CYGWIN__=TRUE)
ENDIF()