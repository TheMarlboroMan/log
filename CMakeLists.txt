cmake_minimum_required(VERSION 3.5.1)
project(log)
set(CMAKE_BUILD_TYPE Release)

add_compile_options(-Wall -Wextra -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual -Wno-deprecated -ansi -pedantic -fno-rtti)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_STATIC "By default, a shared library is built. Set to on to switch to a static library" OFF)
option(BUILD_EXAMPLES "Build example code" ON)

#option(CREATE_DOCS "Build library documentation (requires Doxygen and Graphviz/Dot to be installed)" OFF)

#Adding sources...
set(SOURCE "")
add_subdirectory("${PROJECT_SOURCE_DIR}/src")

#Library building and installation.
if(${BUILD_STATIC})
	add_library(log STATIC ${SOURCE})
else()
	add_library(log SHARED ${SOURCE})
endif()
install(TARGETS log DESTINATION /usr/lib)
install(DIRECTORY src/ DESTINATION include/log FILES_MATCHING PATTERN "*.h")

if(${BUILD_EXAMPLES})
	add_executable(main examples/main.cpp)
	target_link_libraries(main log pthread)
endif()