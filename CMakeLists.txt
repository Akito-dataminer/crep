# cmakeの最小バージョンを指定
cmake_minimum_required( VERSION 3.22.1 )

# プロジェクト名と使用する言語を指定
project( crep LANGUAGES CXX )

# compile_commands.jsonを出力するように設定
set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )

set( is_valid_compiler false )
set( supported_compilers "clang++;g++" )
foreach( supported_compiler IN LISTS supported_compilers )
  if( "${supported_compiler}" STREQUAL "${compiler}" )
    set( is_valid_compiler true )
    break()
  endif()
endforeach()
if( NOT is_valid_compiler )
  message( FATAL_ERROR "${compiler} is not supported" )
endif()

set( is_valid_version false )
set( supported_versions 17;20 )
foreach( supported_version IN LISTS supported_versions )
  if( supported_version EQUAL ${std_version} )
    set( is_valid_version true )
    break()
  endif()
endforeach()
if( NOT is_valid_version )
  message( FATAL_ERROR "C++${std_version} is not supported." )
endif()

set( CMAKE_CXX_COMPILER ${compiler} )
message( STATUS "used compiler: ${compiler}" )

set( CMAKE_CXX_STANDARD ${std_version} )
message( STATUS "std version: ${std_version}" )

# CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDESがONになっていないと
# unixスタイルのインクルードパス指定になるため、
# clangdがインクルードパスを読み込んでくれない。
#
# しかし、CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDESをONにして、
# インクルードパスを別ファイルに出力するようにしていると、
# その別ファイルにはWindowsスタイルでパスが書き込まれるため、
# その問題をクリアできる。
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES ON)

# サブディレクトリを追加
add_subdirectory( src )

# Enable the testing features
enable_testing()
add_subdirectory( test )
