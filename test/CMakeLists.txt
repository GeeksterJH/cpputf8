macro(add_test_case test_name)
	add_executable(${test_name})

	target_sources(${test_name}
				   PRIVATE "${PROJECT_SOURCE_DIR}/test/${test_name}.cpp")

	target_link_libraries(${test_name} PRIVATE cpputf8)

	set_property(TARGET ${test_name} PROPERTY CXX_STANDARD 17)
	set_property(TARGET ${test_name} PROPERTY FOLDER "cpputf8_tests")

	set_project_warnings(${test_name})

	add_test(NAME ${test_name} COMMAND ${test_name})
endmacro()

add_test_case(is_valid)
add_test_case(decode_first)
add_test_case(get_encode_width)
add_test_case(get_info)
add_test_case(length)
