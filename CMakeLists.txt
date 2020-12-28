cmake_minimum_required(VERSION 3.6.0)
project(lm)

option(BUILD_EXAMPLES "Build example code" ON)
option(BUILD_DEBUG "Build a debug release" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(${BUILD_DEBUG})
        set(CMAKE_BUILD_TYPE Debug)

else()
        set(CMAKE_BUILD_TYPE Release)
endif()

add_compile_options(-Wall -Wextra -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual -Wno-deprecated -ansi -pedantic -fno-rtti)

#Add the include directory.
include_directories("include")

#Adding sources...
set(SOURCE "")
add_subdirectory("${PROJECT_SOURCE_DIR}/lib")

#Library building and installation.
add_library(lm_shared SHARED ${SOURCE})
set_target_properties(lm_shared PROPERTIES OUTPUT_NAME lm)

add_library(lm_static STATIC ${SOURCE})
set_target_properties(lm_static PROPERTIES OUTPUT_NAME lm)

install(TARGETS lm_shared DESTINATION lib)
install(TARGETS lm_static DESTINATION lib)
install(DIRECTORY include/ DESTINATION include/ FILES_MATCHING PATTERN "*.h")

IF(WIN32)
	target_compile_definitions(lm_shared PUBLIC -DWINBUILD)
	target_compile_definitions(lm_static PUBLIC -DWINBUILD)
ENDIF()

if(${BUILD_EXAMPLES})
	
	add_executable(multithreading examples/multithreading.cpp)
	target_link_libraries(multithreading lm_shared pthread)
	add_executable(mask examples/mask.cpp)
	target_link_libraries(mask lm_shared)
	add_executable(example examples/example.cpp)
	target_link_libraries(example lm_shared)
endif()
