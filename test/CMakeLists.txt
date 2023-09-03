set( TEST_DIRECTORY ${PROJECT_SOURCE_DIR}/test )
include( ${TEST_DIRECTORY}/AddTestHelpers.cmake )

set( SUB_DIR_UTIL util )
set( SUB_DIR_PATH path )
set( SUB_DIR_ITERATOR iterator )

## テストケースの追加
create_test_case( ${SUB_DIR_UTIL}/throw_if.cpp )
create_test_case( ${SUB_DIR_PATH}/branch.cpp )
create_test_case( ${SUB_DIR_PATH}/parse.cpp )
create_test_case( ${SUB_DIR_PATH}/character.cpp )
create_test_case( ${SUB_DIR_ITERATOR}/index_t.cpp )
