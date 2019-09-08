cmake_minimum_required(VERSION 3.5.1)

project(log)

set(CMAKE_BUILD_TYPE Release)

add_compile_options(-Wall -Wextra -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual -Wno-deprecated -ansi -pedantic -fno-rtti)

#TODO: Should also allow for c++14
add_compile_options(-std=c++11)

#TODO: Add the rest of flags...
#optimizations_y="OPTIMIZATION=-O2"
#optimizations_n="#OPTIMIZATION=-O2"
#debug_y="DEBUG=-g"
#debug_n="#DEBUG=-g"
#cpp14_y="CPPREV=-std=c++14" 
#	cpp14_n="CPPREV=-std=c++11"


set(SOURCE "")

add_subdirectory("${PROJECT_SOURCE_DIR}/src")

add_library(log STATIC ${SOURCE})
