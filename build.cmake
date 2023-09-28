cmake_minimum_required( VERSION 3.22.1 )

include( cmake/ndef_value.cmake )
include( cmake/config.cmake )
include( cmake/build_directory.cmake )

display_value( build_type )
display_value( compiler )
display_value( std_version )
display_value( slib )

build_directory( "${test}" ${compiler} ${std_version} build_dir )

display_value( build_dir )

if( NOT EXISTS ${build_dir} )
  file( MAKE_DIRECTORY ${build_dir} )
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} ${project_root} -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -Dslib=${slib} -Dstd_version=${std_version} -Dcompiler=${compiler}
  RESULT_VARIABLE is_error_occured
  WORKING_DIRECTORY ${build_dir}
)

include( cmake/processor_num.cmake )
count_processor( processor_num )
message( STATUS "processor num: ${processor_num}" )

if( ${is_error_occured} EQUAL 0 )
  execute_process(
    COMMAND ${CMAKE_COMMAND} --build . -j${processor_num}
    WORKING_DIRECTORY ${build_dir}
  )
endif()
