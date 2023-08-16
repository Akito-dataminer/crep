file( GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp )

# 生成するファイル名の指定
set( OUTPUT ${PROJECT_NAME} )

# 実行ファイル生成のターゲットを生成する
set( INCLUDE_DIRECTORY ${PROJECT_SOURCE_DIR}/include ) # インクルードディレクトリの設定
set( VERSION_INFORMATION_HEADER ${INCLUDE_DIRECTORY}/version.h ) # バージョン情報ヘッダを出力するための設定

# ここでVERSION_INFORMATION_HEADERを指定しておかないと、ビルド時に生成されない
add_executable( ${OUTPUT} ${SOURCES} ${VERSION_INFORMATION_HEADER} )
target_include_directories( ${OUTPUT} PUBLIC ${INCLUDE_DIRECTORY} )

# コンパイルフラグを追加
# MSVCとgcc系のコンパイラでは、オプションの指定方法が違うので、
# それに対応するためにジェネレータ式を利用している。
set( gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>" )
set( clang_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang>" )
set( msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>" )
set( warning_options_for_clang_like -Wall -Wextra -Wshadow -Wformat=2 -Wunused )
set( warning_options_for_msvc -W3 )
set( warning_options
  $<${gcc_like_cxx}:${warning_options_for_clang_like}>
  $<${msvc_cxx}:${warning_options_for_msvc}>
)

set( target_if_msys2 "" )

if(MINGW)
  # -target x86_64-w64-windows-gnuというオプションが
  # windows上のすべての環境に必要なのかどうかが分からないので、
  # とりあえずMSYS2環境では有効となるようにしている。
  set( target_if_msys2 $<${clang_cxx}:-target x86_64-w64-windows-gnu> )
endif()

# slib : command line argument
set_target_properties(${OUTPUT} PROPERTIES
  STANDARD_LIBRARY $<$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang>:-stdlib=${slib}>
)

set( stdlib $<TARGET_GENEX_EVAL:${OUTPUT},$<TARGET_PROPERTY:${OUTPUT},STANDARD_LIBRARY>> )
message( STATUS "used standard library: ${slib}" )

target_compile_options(${OUTPUT} PUBLIC
  ${warning_options}
  ${stdlib_option}
  ${target_if_msys2}
)

target_link_options(${OUTPUT} PUBLIC
  ${stdlib_option}
)

# C++標準規格の指定 cxx_std_20はcmake3.12以降で指定可能
target_compile_features( ${OUTPUT} PUBLIC cxx_std_17 )

##############################
# バージョン情報を定義したヘッダファイルを生成する
##############################
set( CMAKE_SCRIPT_PATH ${PROJECT_SOURCE_DIR}/cmake )
set( VERSION_SCRIPT_PATH ${CMAKE_SCRIPT_PATH}/version.cmake )
set( VERSION_CONFIGURE_PATH ${CMAKE_SCRIPT_PATH}/version.h.in )

add_custom_command(OUTPUT ${VERSION_INFORMATION_HEADER}
  DEPENDS ${VERSION_SCRIPT_PATH} ${VERSION_CONFIGURE_PATH}
  COMMAND ${CMAKE_COMMAND} -P ${VERSION_SCRIPT_PATH}
  WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
)
