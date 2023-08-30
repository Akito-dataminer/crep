#include "path/branch.hpp"

#include <algorithm>
#include <iterator>

#include "config/config.hpp"
#include "util/throw_if.hpp"

namespace path {

branch::branch( std::string const &path_element ) : path_element_( 0 ) {
  parse::branch_parse parser( path_element );

  std::size_t branch_num = parser.size();
  for ( size_t i = 0; i < branch_num; ++i ) {
    path_element_.emplace_back( parser[i] );
  }
}

void branch::truncate( std::string const &truncate_branch ) noexcept {
  auto truncate_condition = [&truncate_branch]( std::string const &value ) -> bool { return value == truncate_branch; };

  decltype( path_element_ )::iterator new_end_itr =
      std::remove_if( path_element_.begin(), path_element_.end(), truncate_condition );

  path_element_.erase( new_end_itr, path_element_.end() );
}

std::string branch::buildBranch() const noexcept {
  std::string branch_tmp( "" );
  for ( decltype( path_element_ )::const_iterator citr = path_element_.cbegin(); citr != path_element_.cend();
        ++citr ) {
    if ( isRoot( *citr ) == true ) {
      branch_tmp += ( *citr );
    } else {
#ifdef _WIN32
      branch_tmp += PATH_SEPARATOR;
      branch_tmp += ( *citr );
#elif __linux__
      if ( citr != path_element_.cbegin() ) {
        if ( isRoot( *( citr - 1 ) ) == true ) {
          branch_tmp += ( *citr );
        } else {
          branch_tmp += PATH_SEPARATOR;
          branch_tmp += ( *citr );
        }
      } else {
        branch_tmp += PATH_SEPARATOR;
        branch_tmp += ( *citr );
      }
#endif
    }
  }
  return branch_tmp;
}

bool branch::isRoot( std::string const &maybe_root ) const noexcept {
  bool is_root = false;
#ifdef _WIN32
  if ( maybe_root[0] >= 'A' && maybe_root[0] <= 'Z' ) {
    if ( maybe_root[1] == ':' ) {
      is_root = true;
    }
  }
#elif __linux__
  if ( maybe_root == "/" ) {
    is_root = true;
  }
#endif
  return is_root;
}

}  // namespace path
