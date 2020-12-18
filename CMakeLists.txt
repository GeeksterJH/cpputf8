cmake_minimum_required(VERSION 3.18)

project(cpputf8 CXX)

include(cmake/CompilerWarnings.cmake)

option(CPPUTF8_ENABLE_TESTS "Enable the testing targets" OFF)

# Main library
add_library(cpputf8 INTERFACE)

target_include_directories(cpputf8 INTERFACE "${PROJECT_SOURCE_DIR}/include"
											 "${CMAKE_BINARY_DIR}/include")

set_project_warnings(cpputf8)

# Unicode Data
if(NOT EXISTS "${CMAKE_BINARY_DIR}/assets/UnicodeData.txt")
	message("Downloading UnicodeData.txt...")

	file(DOWNLOAD
		 "https://www.unicode.org/Public/14.0.0/ucd/UnicodeData-14.0.0d3.txt"
		 "${CMAKE_BINARY_DIR}/assets/UnicodeData.txt")
endif()

add_custom_command(
	COMMAND python3 ${PROJECT_SOURCE_DIR}/scripts/generate_unicode_data.py
			${CMAKE_BINARY_DIR}
	OUTPUT "${CMAKE_BINARY_DIR}/include/cpputf8/unicode_data.hpp"
	DEPENDS "${PROJECT_SOURCE_DIR}/scripts/generate_unicode_data.py")

add_custom_target(
	cpputf8_generate_unicode_data ALL
	DEPENDS "${CMAKE_BINARY_DIR}/include/cpputf8/unicode_data.hpp")

add_dependencies(cpputf8 cpputf8_generate_unicode_data)

target_precompile_headers(
	cpputf8 INTERFACE "${CMAKE_BINARY_DIR}/include/cpputf8/unicode_data.hpp")

# Tests
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	set(CPPUTF8_ENABLE_TESTS ON)
endif()

if(CPPUTF8_ENABLE_TESTS)
	add_executable(cpputf8_test)

	target_sources(cpputf8_test PRIVATE "${PROJECT_SOURCE_DIR}/test/test.cpp")

	target_link_libraries(cpputf8_test PRIVATE cpputf8)

	set_property(TARGET cpputf8_test PROPERTY CXX_STANDARD 17)

	set_project_warnings(cpputf8_test)

	enable_testing()
	add_test(NAME cpputf8_test COMMAND cpputf8_test)
endif()
