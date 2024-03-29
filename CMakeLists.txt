cmake_minimum_required(VERSION 3.6.0)
project(lm)

option(BUILD_EXAMPLES "Build example code" ON)
option(BUILD_DEBUG "Build a debug release" OFF)
option(BUILD_SHARED "Build a shared library" ON)
option(BUILD_STATIC "Build a static library" OFF)

#library version
set(MAJOR_VERSION 3)
set(MINOR_VERSION 1)
set(PATCH_VERSION 1)

if(${BUILD_DEBUG})

	set(RELEASE_VERSION "debug")

else()

	set(RELEASE_VERSION "prod")
endif()

if(${CMAKE_VERSION} VERSION_LESS "3.22.0")

	add_definitions(-DMAJOR_VERSION=${MAJOR_VERSION})
	add_definitions(-DMINOR_VERSION=${MINOR_VERSION})
	add_definitions(-DPATCH_VERSION=${PATCH_VERSION})
	add_definitions(-DRELEASE_VERSION=\"${RELEASE_VERSION}\")
else()

	add_compile_definitions(MAJOR_VERSION=${MAJOR_VERSION})
	add_compile_definitions(MINOR_VERSION=${MINOR_VERSION})
	add_compile_definitions(PATCH_VERSION=${PATCH_VERSION})
	add_compile_definitions(RELEASE_VERSION=\"${RELEASE_VERSION}\")
endif()


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual -Wno-deprecated -ansi -pedantic -fno-rtti)

#Add the include directory.
include_directories("include")
set(SOURCE "")
add_subdirectory("${PROJECT_SOURCE_DIR}/lib")

#library type and filenames.
if(${BUILD_DEBUG})

	set(CMAKE_BUILD_TYPE Debug)
	set(LIB_FILENAME "lm_debug")
else()

	set(CMAKE_BUILD_TYPE Release)
	set(LIB_FILENAME "lm")
endif()

if(${BUILD_SHARED})
	add_library(lm_shared SHARED ${SOURCE})
	set_target_properties(lm_shared PROPERTIES OUTPUT_NAME ${LIB_FILENAME})
	target_compile_definitions(lm_shared PUBLIC "-DLIB_VERSION=\"static\"")
	install(TARGETS lm_shared DESTINATION lib)

	message("will build ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}-${RELEASE_VERSION}-shared")
endif()

if(${BUILD_STATIC})
	add_library(lm_static STATIC ${SOURCE})
	set_target_properties(lm_static PROPERTIES OUTPUT_NAME ${LIB_FILENAME})
	target_compile_definitions(lm_static PUBLIC "-DLIB_VERSION=\"static\"")
	install(TARGETS lm_static DESTINATION lib)

	message("will build ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}-${RELEASE_VERSION}-static")
endif()

set(INSTALL_DIR "include/debug-headers/")
install(DIRECTORY include/ DESTINATION ${INSTALL_DIR} FILES_MATCHING PATTERN "*.h")

IF(WIN32)
	if(${BUILD_SHARED)
		target_compile_definitions(lm_shared PUBLIC -DWINBUILD)
	endif()
	if(${BUILD_STATIC})
		target_compile_definitions(lm_static PUBLIC -DWINBUILD)
	endif()
ENDIF()

if(${BUILD_EXAMPLES})

	if(!${BUILD_SHARED})

		message(FATAL_ERROR "The shared library must be built to build the examples!")
	endif()

	add_executable(sentry_multithreading examples/sentry_multithreading.cpp)
	target_link_libraries(sentry_multithreading lm_shared pthread)

	add_executable(mask examples/mask.cpp)
	target_link_libraries(mask lm_shared)

	add_executable(sentry_example examples/sentry_example.cpp)
	target_link_libraries(sentry_example lm_shared)

	add_executable(sentry_insertion_operator examples/sentry_insertion_operator.cpp)
	target_link_libraries(sentry_insertion_operator lm_shared)

	add_executable(insertion_operator examples/insertion_operator.cpp)
	target_link_libraries(insertion_operator lm_shared)

	add_executable(version examples/version.cpp)
	target_link_libraries(version lm_shared)

endif()
