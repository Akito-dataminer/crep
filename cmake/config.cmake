##################################################
# Copyright(c) 2023 Akito Dataminer
#
# This software is released under the MIT License.
# Refer the accompanying LICENSE.txt or the description
# at the provided URL for details.
# http://opensource.org/licenses/mit-license.php
##################################################
# This script defines the default values for arguments
# passed to cmake during the configuration phase.
##################################################
include( cmake/ndef_value.cmake )

ifndef_default( build_type Debug )
ifndef_default( compiler clang++ )
ifndef_default( std_version 20 )
ifndef_default( slib libstdc++ )
