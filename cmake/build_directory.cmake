include( cmake/ndef_value.cmake )

macro( build_directory specified_compiler specified_version result )
  if( DEFINED ${test} )
    set( ${result} ${CMAKE_SOURCE_DIR}/build_for_test/${specified_compiler}/${specified_version} )
  else()
    set( ${result} ${CMAKE_SOURCE_DIR}/build )
  endif()
endmacro()

set( project_root ${CMAKE_SOURCE_DIR} )
