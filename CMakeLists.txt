cmake_minimum_required(VERSION 3.6.0)
project(log)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual -Wno-deprecated -ansi -pedantic -fno-rtti)

option(BUILD_STATIC "By default, a shared library is built. Set to on to switch to a static library" OFF)
option(BUILD_EXAMPLES "Build example code" ON)

#Adding sources...
set(SOURCE "")
add_subdirectory("${PROJECT_SOURCE_DIR}/src")

#Library building and installation.
if(${BUILD_STATIC})
	add_library(log STATIC ${SOURCE})
else()
	add_library(log SHARED ${SOURCE})
endif()

install(TARGETS log DESTINATION install/lib)
install(DIRECTORY src/ DESTINATION install/include/log FILES_MATCHING PATTERN "*.h")

if(${BUILD_EXAMPLES})
	add_executable(multithreading examples/multithreading.cpp)
	target_link_libraries(multithreading log pthread)
	add_executable(mask examples/mask.cpp)
	target_link_libraries(mask log)
	add_executable(example examples/example.cpp)
	target_link_libraries(example log)
endif()
