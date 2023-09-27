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
include( ${PROJECT_SOURCE_DIR}/cmake/compile_option.cmake )
add_compile_option( ${OUTPUT} )

if( WIN32 AND CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT )
  set( CMAKE_INSTALL_PREFIX "C:/Program Files/crep" CACHE PATH "Installation path prefix absorbed the difference of UNIX(Linux) and Windows" FORCE )
endif()

include( ${PROJECT_SOURCE_DIR}/cmake/ndef_value.cmake )
display_value( CMAKE_INSTALL_PREFIX )
install( TARGETS ${OUTPUT} RUNTIME )

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
