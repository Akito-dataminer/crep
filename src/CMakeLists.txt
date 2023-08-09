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
set( msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>" )
set( target_if_msys2 "" )

if(MINGW)
  # -target x86_64-w64-windows-gnuというオプションが
  # windows上のすべての環境に必要なのかどうかが分からないので、
  # とりあえずMSYS2環境では有効となるようにしている。
  set( target_if_msys2 -target x86_64-w64-windows-gnu )
endif()

target_compile_options(${OUTPUT} PUBLIC
  $<${gcc_like_cxx}:-Wall -Wextra -Wshadow -Wformat=2 -Wunused>
  "$<${msvc_cxx}:-W3>"
  "${target_if_msys2}"
)

# C++標準規格の指定 cxx_std_20はcmake3.12以降で指定可能
target_compile_features( ${OUTPUT} PUBLIC cxx_std_20 )

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
