/****************************************
 ****************************************/

#include "config/config.hpp"
#include "util/path.hpp"

// std
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

int main( int argc, char const * argv[] ) {
  // スケルトンプログラムを保管しているディレクトリを設定する。
  char const * environment_variable = std::getenv( GET_ENVIRONMENT_VARIABLE );
  if ( environment_variable == nullptr ) {
    std::cerr << "The environment variable " << GET_ENVIRONMENT_VARIABLE << " is not able to be read." << std::endl;
    return -1;
  }
  std::string skeleton_dir = std::string( environment_variable ) + std::string( APPEND_DIRECTORY );

  bool is_project_skeleton_exist = std::filesystem::is_directory( skeleton_dir );

  if ( !is_project_skeleton_exist ) {
    std::cerr << "Tere is NOT project skeleton in " << skeleton_dir << std::endl;
  }

  // コピー元のリストを作成
  std::vector<std::string> file_paths;

  recursive_scan_directory( skeleton_dir, file_paths );

  for ( auto itr : file_paths ) {
    std::cout << "file_path : " << itr << std::endl;
  }

  return 0;
}
