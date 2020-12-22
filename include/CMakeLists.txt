add_library(cpputf8 INTERFACE)

target_include_directories(cpputf8 INTERFACE "${PROJECT_SOURCE_DIR}/include"
											 "${CMAKE_BINARY_DIR}/include")

set_project_warnings(cpputf8)

target_precompile_headers(
	cpputf8 INTERFACE "${CMAKE_BINARY_DIR}/include/cpputf8/unicode_data.hpp")

add_custom_command(
	COMMAND python3 ${PROJECT_SOURCE_DIR}/scripts/generate_unicode_data.py
			${CMAKE_BINARY_DIR}
	OUTPUT "${CMAKE_BINARY_DIR}/include/cpputf8/unicode_data.hpp"
	DEPENDS "${PROJECT_SOURCE_DIR}/scripts/generate_unicode_data.py"
	COMMENT "Generating unicode_data.hpp...")

# This target runs the `generate_unicode_data` script
add_custom_target(
	cpputf8_generate_unicode_data ALL
	DEPENDS "${CMAKE_BINARY_DIR}/include/cpputf8/unicode_data.hpp")

add_dependencies(cpputf8 cpputf8_generate_unicode_data)
