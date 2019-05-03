
add_custom_target(
        auto_run_pytest ALL
)

add_custom_command(
        COMMENT "Copy Data to test..."
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/../Data
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../Elastos.ELA.SPV.Cpp/Data ${CMAKE_CURRENT_BINARY_DIR}/../Data
)
add_custom_command(
        COMMENT "Copy test.py to test..."
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/../test.py
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/test.py ${CMAKE_CURRENT_BINARY_DIR}/../test.py
)

add_custom_target(copy_data_target DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/../Data ${CMAKE_CURRENT_BINARY_DIR}/../test.py)

unset(AUTO_TEST_COMMAND)

add_dependencies(auto_run_pytest copy_data_target spvsdkpy)

add_custom_command(
        TARGET auto_run_pytest
        POST_BUILD
        COMMAND python3 test.py
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../
)
