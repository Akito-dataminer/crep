include( cmake/ndef_value.cmake )

function( build_directory test specified_compiler specified_version result )
  if( ${test} )
    set( ${result} ${CMAKE_SOURCE_DIR}/build_for_test/${specified_compiler}/${specified_version} PARENT_SCOPE )
  else()
    set( ${result} ${CMAKE_SOURCE_DIR}/build PARENT_SCOPE )
  endif()
endfunction()

set( project_root ${CMAKE_SOURCE_DIR} )
