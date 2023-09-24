##################################################
# Copyright(c) 2023 Akito Dataminer
#
# This software is released under the MIT License.
# Refer the accompanying LICENSE.txt or the description
# at the provided URL for details.
# http://opensource.org/licenses/mit-license.php
##################################################
# このスクリプトは、コンパイラと標準規格の組み合わせを変えて
# build.cmakeを実行し、テストケースと本体をコンパイルする。
# その後、そのテストケースを実行する。
##################################################
# This script runs build.cmake with different combinations of compilers and
# standards to compile the main source code and test cases.
# After that, this script executes the test cases.
##################################################
set( available_compilers clang++;g++ )
set( available_std_versions 17;20 )
set( test 1 )

include( cmake/ndef_value.cmake )
include( cmake/config.cmake )
include( cmake/build_directory.cmake )

# compile
set( test_directories )
foreach( compiler IN LISTS available_compilers )
  foreach( std_version IN LISTS available_std_versions )
    build_directory( ${test} ${compiler} ${std_version} build_directory )
    list( APPEND test_directories ${build_directory} )

    message( STATUS "Now compiling by ${compiler} with C++${std_version}" )
    execute_process(
      COMMAND ${CMAKE_COMMAND} . -Dtest=1 -Dstd_version=${std_version} -Dcompiler=${compiler} -P build.cmake
      WORKING_DIRECTORY ${project_root}
    )
    message( "" )
  endforeach()
endforeach()

# test
include( cmake/processor_num.cmake )
count_processor( processor_num )

foreach( test_directory IN LISTS test_directories )
  execute_process(
    COMMAND ${CMAKE_CTEST_COMMAND} -j${processor_num}
    WORKING_DIRECTORY ${test_directory}
  )
endforeach()
