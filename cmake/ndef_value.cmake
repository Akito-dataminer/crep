##################################################
# Copyright(c) 2023 Akito Dataminer
#
# This software is released under the MIT License.
# Refer the accompanying LICENSE.txt or the description
# at the provided URL for details.
# http://opensource.org/licenses/mit-license.php
##################################################
macro( ifndef_default variable_name default_value )
  if( NOT DEFINED ${variable_name} )
    set( ${variable_name} ${default_value} )
  endif()
endmacro()

macro( display_value variable_name )
  message( STATUS "${variable_name}: ${${variable_name}}" )
endmacro()

