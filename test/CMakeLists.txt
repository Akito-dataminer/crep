set( TEST_DIRECTORY ${PROJECT_SOURCE_DIR}/test )
include( ${TEST_DIRECTORY}/AddTestHelpers.cmake )

set( SUB_DIR util )

## テストケースの追加
create_test_case( ${SUB_DIR}/path.cpp )
create_test_case( ${SUB_DIR}/throw_if.cpp )
