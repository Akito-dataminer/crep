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

void branch::truncate( branch const &truncate_branch ) {
  util::throw_if<std::invalid_argument>( path_element_.size() < truncate_branch.size(), "the argument is too long" );
  container_type::iterator remove_begin, this_end = path_element_.end(), this_itr = path_element_.begin();
  // truncate_branchの最初の要素に一致している要素がどこにあるかを調べるためのループ
  // つまり、remove_beginを求めるためのループ
  // This loop finds the iterator in path_element_ that matches the first element of truncate_branch.
  // i.e. This loop demand remove_begin.
  for ( ; this_itr != this_end; ++this_itr ) {
    if ( *this_itr == truncate_branch[0] ) {
      remove_begin = this_itr;
      if ( static_cast<long>( truncate_branch.size() ) <= std::distance( remove_begin, this_end ) ) {
        break;
      } else {
        throw std::invalid_argument( "the argument is too long" );
      }
    }
  }

  util::throw_if<std::invalid_argument>( this_itr == this_end, "invalid argument was given to branch::truncate" );

  // どこまで一致しているかを調べるためのループ
  // つまり、最終的なthis_itrの位置を求めるためのループ
  // This loop checks how far the elements after remove_begin match with truncate_branch.
  // i.e. This loop demand the last position of this_itr.
  for ( branch::const_iterator truncate_itr = truncate_branch.cbegin(); truncate_itr != truncate_branch.cend();
        ++truncate_itr, ++this_itr ) {
    util::throw_if<std::invalid_argument>(
        *truncate_itr != *this_itr, "invalid argument was given to branch::truncate"
    );
  }

  path_element_.erase( remove_begin, this_itr );
}

std::string branch::buildBranch() const noexcept {
  std::string branch_tmp( "" );
  for ( container_type::const_iterator citr = path_element_.cbegin(); citr != path_element_.cend(); ++citr ) {
    if ( citr == path_element_.cbegin() ) {
      branch_tmp += ( *citr );
      continue;
    } else {
#ifdef _WIN32
      branch_tmp += DELIMITER;
      branch_tmp += ( *citr );
#elif __linux__
      if ( isRoot( *( citr - 1 ) ) == true ) {
        branch_tmp += ( *citr );
      } else {
        branch_tmp += DELIMITER;
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
