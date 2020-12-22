add_executable(cpputf8_test)

target_sources(cpputf8_test PRIVATE "${PROJECT_SOURCE_DIR}/test/test.cpp")

target_link_libraries(cpputf8_test PRIVATE cpputf8)

set_property(TARGET cpputf8_test PROPERTY CXX_STANDARD 17)

set_project_warnings(cpputf8_test)

enable_testing()
add_test(NAME cpputf8_test COMMAND cpputf8_test)
