cmake_minimum_required( VERSION 3.22.1 )

if( NOT DEFINED build_type )
  set( build_type Debug )
endif()

message( STATUS "build_type: ${build_type}" )

if( NOT DEFINED slib )
  set( slib libstdc++ )
endif()

if( NOT DEFINED std_version )
  set( std_version 20 )
endif()

if( NOT DEFINED compiler )
  set( compiler clang++ )
endif()

set( build_dir ${CMAKE_CURRENT_LIST_DIR}/build/${compiler}/${std_version} )
message( STATUS "build directory: ${build_dir}" )

if( NOT EXISTS ${build_dir} )
  file( MAKE_DIRECTORY ${build_dir} )
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} ../../../ -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -Dslib=${slib} -Dstd_version=${std_version} -Dcompiler=${compiler}
  WORKING_DIRECTORY ${build_dir}
)

execute_process(
  COMMAND ${CMAKE_COMMAND} --build . -j8
  WORKING_DIRECTORY ${build_dir}
)
