
add_custom_target(
	auto_run_pytest ALL
)

file(GLOB_RECURSE PYSOURCE_FILES "*.py")
set(SPVSDKPY_TARGET_NAME $<TARGET_FILE:spvsdkpy>)

add_custom_target(
	copy_data_for_pytest
	COMMENT "Copy Data to test..."
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../Elastos.ELA.SPV.Cpp/Data ${CMAKE_CURRENT_BINARY_DIR}/Data
)

add_custom_target(
	copy_dependence_for_pytest
	COMMENT "Preparing py test..."
	COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PYSOURCE_FILES} ${SPVSDKPY_TARGET_NAME} ${CMAKE_CURRENT_BINARY_DIR}
	DEPENDS spvsdkpy
)

unset(AUTO_TEST_COMMAND)

add_dependencies(auto_run_pytest copy_dependence_for_pytest copy_data_for_pytest spvsdkpy)

add_custom_command(
	TARGET auto_run_pytest
	POST_BUILD
	COMMAND python3 test.py
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

