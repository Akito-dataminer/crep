##################################################
# Copyright(c) 2023 Akito Dataminer
#
# This software is released under the MIT License.
# Refer the accompanying LICENSE.txt or the description
# at the provided URL for details.
# http://opensource.org/licenses/mit-license.php
##################################################

include(ProcessorCount)
function( count_processor result )
  ProcessorCount( COUNTED_NUM )

  # Ensure that ProcessorCount has not failed.
  if( NOT COUNTED_NUM EQUAL 0 )
    set( ${result} ${COUNTED_NUM} PARENT_SCOPE )
  else()
    set( ${result} 1 PARENT_SCOPE )
  endif()
endfunction()
