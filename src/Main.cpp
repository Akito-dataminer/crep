/****************************************
 ****************************************/

#include "config/config.hpp"
#include "util/path.hpp"
#include "util/throw_if.hpp"

// std
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

int main( int const argc, char const *argv[] ) {
  try {
    // スケルトンプログラムを保管しているディレクトリを設定する。
    char const *environment_variable = std::getenv( GET_ENVIRONMENT_VARIABLE );
    util::throw_if<std::runtime_error>(
        environment_variable == nullptr, std::string( "The environment variable " ) +
                                             std::string( GET_ENVIRONMENT_VARIABLE ) +
                                             std::string( "is not able to be read." )
    );
    std::string skeleton_dir = std::string( environment_variable ) + std::string( APPEND_DIRECTORY );

    util::throw_if<std::runtime_error>(
        !std::filesystem::is_directory( skeleton_dir ),
        std::string( "There is NOT project skeleton in " ) + skeleton_dir
    );

    std::vector<std::string> const original_paths = path::recursive_scan_directory( skeleton_dir );
    int skeleton_dir_length = skeleton_dir.length() + 1;  // skeleton_dirは、末尾が'/'になっていないので、+1しておく
    std::vector<std::pair<std::string, std::string>> source_to_dest;

    for ( auto itr : original_paths ) {
      std::string dest_name = itr.substr( skeleton_dir_length );
      if ( dest_name.substr( 0, 4 ) == ".git" ) {
        continue;
      }
      if ( dest_name.substr( 0, 6 ) == "build/" ) {
        continue;
      }
      if ( dest_name.substr( 0, 7 ) == "LICENSE" ) {
        continue;
      }
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
  } catch ( std::exception &e ) {
    std::cerr << e.what() << std::endl;
  }
}
