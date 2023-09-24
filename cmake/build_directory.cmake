include( cmake/ndef_value.cmake )

if( DEFINED ${test} )
  set( build_dir ${CMAKE_SOURCE_DIR}/build_for_test/${compiler}/${std_version} )
  set( project_root ${CMAKE_SOURCE_DIR} )
else()
  set( build_dir ${CMAKE_SOURCE_DIR}/build )
  set( project_root ${CMAKE_SOURCE_DIR} )
endif()
