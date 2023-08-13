/****************************************
 ****************************************/

#include "config/config.hpp"
#include "util/path.hpp"

// std
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

int main( int const argc, char const * argv[] ) {
  // スケルトンプログラムを保管しているディレクトリを設定する。
  char const * environment_variable = std::getenv( GET_ENVIRONMENT_VARIABLE );
  if ( environment_variable == nullptr ) {
    std::cerr << "The environment variable " << GET_ENVIRONMENT_VARIABLE << " is not able to be read." << std::endl;
    return -1;
  }
  std::string skeleton_dir = std::string( environment_variable ) + std::string( APPEND_DIRECTORY );

  bool is_project_skeleton_exist = std::filesystem::is_directory( skeleton_dir );

  if ( !is_project_skeleton_exist ) {
    std::cerr << "There is NOT project skeleton in " << skeleton_dir << std::endl;
  }

  std::vector<std::string> const original_paths = path::recursive_scan_directory( skeleton_dir );
  int skeleton_dir_length = skeleton_dir.length() + 1; // skeleton_dirは、末尾が'/'になっていないので、+1しておく
  std::vector<std::pair<std::string, std::string>> source_to_dest;

  for ( auto itr : original_paths ) {
    std::string dest_name = itr.substr( skeleton_dir_length );
    if ( dest_name.substr( 0, 4 ) == ".git" ) { continue; }
    if ( dest_name.substr( 0, 6 ) == "build/" ) { continue; }
    if ( dest_name.substr( 0, 7 ) == "LICENSE" ) { continue; }
    source_to_dest.emplace_back( itr, dest_name );
  }

  for ( auto itr : source_to_dest ) {
    if ( std::filesystem::is_directory( itr.first ) ) {
      std::filesystem::create_directory( itr.second );
    } else {
      std::filesystem::copy( itr.first, itr.second );
    }
  }

  return 0;
}
