set( TEST_DIRECTORY ${PROJECT_SOURCE_DIR}/test )
include( ${TEST_DIRECTORY}/AddTestHelpers.cmake )

set( SUB_DIR_UTIL util )
set( SUB_DIR_PATH path )

## テストケースの追加
create_test_case( ${SUB_DIR_UTIL}/throw_if.cpp )
create_test_case( ${SUB_DIR_PATH}/branch.cpp )
