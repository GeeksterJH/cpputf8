cmake_minimum_required(VERSION 3.18)

project(cpputf8 CXX)

include(cmake/CompilerWarnings.cmake)
include(cmake/UnicodeData.cmake)

option(CPPUTF8_ENABLE_TESTS "Enable the testing targets" OFF)

download_unicode_data()

# Main library
add_subdirectory(include)

# Tests
if(CPPUTF8_ENABLE_TESTS)
	add_subdirectory(test)
endif()
