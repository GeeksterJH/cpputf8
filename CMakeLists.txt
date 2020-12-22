cmake_minimum_required(VERSION 3.18)

project(cpputf8 CXX)

include(cmake/CompilerWarnings.cmake)
include(cmake/UnicodeData.cmake)

option(CPPUTF8_ENABLE_TESTS "Enable the testing targets" OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

download_unicode_data()

# Main library
add_subdirectory(include)

# Tests
if(CPPUTF8_ENABLE_TESTS)
	enable_testing()
	add_subdirectory(test)
endif()
