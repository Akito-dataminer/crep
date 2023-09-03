/****************************************
 ****************************************/

#include "config/config.hpp"
#include "path/branch.hpp"
#include "util/path.hpp"
#include "util/throw_if.hpp"

// std
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

int main( int const argc, char const *argv[] ) {
  int return_value = 0;
  try {
    // スケルトンプログラムを保管しているディレクトリを設定する。
    char const *environment_variable = std::getenv( GET_ENVIRONMENT_VARIABLE );
    util::throw_if<std::runtime_error>(
        environment_variable == nullptr, std::string( "The environment variable " ) +
                                             std::string( GET_ENVIRONMENT_VARIABLE ) +
                                             std::string( "is not able to be read." )
    );

    path::branch skeleton_dir( std::string( environment_variable ) + std::string( APPEND_DIRECTORY ) );
    util::throw_if<std::runtime_error>(
        !std::filesystem::is_directory( skeleton_dir.to_string() ),
        std::string( "There is NOT project skeleton in " ) + skeleton_dir.to_string()
    );
    std::cout << "skeleton_dir.to_string: " << skeleton_dir.to_string() << std::endl;

    std::vector<path::branch> const original_branches = path::recursive_scan_directory( skeleton_dir );
    std::vector<std::pair<path::branch, path::branch>> source_to_dest;
    std::vector<path::branch> const ignore_list{
        path::branch( ".git" ), path::branch( "build" ), path::branch( "LICENSE.md" ) };

    auto ignore_branch = [&ignore_list]( path::branch const &maybe_ignored ) -> bool {
      using size_type = path::branch::index_type::value_type;

      bool is_member_of_ignore_list = false;
      for ( decltype( ignore_list )::const_iterator citr = ignore_list.cbegin(); citr != ignore_list.cend(); ++citr ) {
        if ( static_cast<size_type>( maybe_ignored.contains( *citr ) ) != crep::npos_v<size_type> ) {
          is_member_of_ignore_list = true;
          break;
        }
      }
      return is_member_of_ignore_list;
    };

    for ( decltype( original_branches )::const_iterator citr = original_branches.cbegin();
          citr != original_branches.end(); ++citr ) {
      if ( ignore_branch( *citr ) ) {
        continue;
      }

      path::branch dest_name( "./" );
      path::branch original_branch = *citr;

      original_branch.truncate( skeleton_dir );
      dest_name += original_branch;

      std::cout << citr->to_string() << "  ->  " << dest_name.to_string() << std::endl;

      source_to_dest.emplace_back( *citr, dest_name );
    }

    // for ( auto itr : source_to_dest ) {
    //   if ( std::filesystem::is_directory( static_cast<std::filesystem::path>( itr.first ) ) ) {
    //     std::filesystem::create_directory( static_cast<std::filesystem::path>( itr.second ) );
    //   } else {
    //     std::filesystem::copy(
    //         static_cast<std::filesystem::path>( itr.first ), static_cast<std::filesystem::path>( itr.second )
    //     );
    //   }
    // }
    return_value = 0;
  } catch ( std::exception &e ) {
    std::cerr << e.what() << std::endl;
    return_value = -1;
  }
  return return_value;
}
