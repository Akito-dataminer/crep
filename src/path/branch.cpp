#include "path/branch.hpp"

#include <iterator>

#include "config/config.hpp"
#include "util/throw_if.hpp"

namespace path {

namespace detail {

index::index( std::string const &branch_str ) {
  for ( std::string::const_iterator citr = branch_str.begin(); citr != branch_str.end(); ++citr ) {
    std::size_t head_index = std::distance( branch_str.begin(), citr );
    role token_type = type_detection( citr, head_index );
    std::size_t length = 0;

    switch ( token_type ) {
      case role::ROOT:
#if _WIN32
        length = 2;
        ++citr;
        break;
#else
        length = 1;
        break;
#endif
        break;
      case role::DELIMITER:
        length = 1;
        break;
      case role::BRANCH:
        for ( ;; ++citr ) {
          ++length;
          if ( ( *( citr + 1 ) == PATH_SEPARATOR ) || ( ( citr + 1 ) == branch_str.cend() ) ) {
            break;
          }
        }
      default:
        break;
    }

    if ( token_type != role::DELIMITER ) {
      token_sequence_.emplace_back( token_type, head_index, length );
    }
  }
}

role index::type_detection( std::string::const_iterator &itr, std::size_t const index ) const {
  role type;
#if _WIN32
  // ただし、このタイプ判定が期待通りに働くためには
  // 必ず2文字目にアクセス可能で、かつブランチの途中でこの関数が呼び出されない
  // という条件が成り立っている必要がある。
  // 例えばC:\\Users\\...のようなパスがあった場合、
  // その2文字目を指すイテレータが、この関数に渡されてはいけない。
  if ( *( itr + 1 ) == ':' ) {
    if ( *itr >= 'A' && *itr <= 'Z' ) {
      type = role::ROOT;
    } else {
      type = role::TYPE_NUM;
      throw std::invalid_argument( "A character was used that should not be in a branch." );
    }
  } else if ( *itr == PATH_SEPARATOR ) {
    type = role::DELIMITER;
  } else {
    type = role::BRANCH;
  }
#else
  if ( *itr == PATH_SEPARATOR ) {
    if ( index == 0 ) {
      type = role::ROOT;
    } else {
      type = role::DELIMITER;
    }
  } else {
    type = role::BRANCH;
  }
#endif
  return type;
}

}  // namespace detail

branch::branch( std::string const &path_element ) : path_element_( path_element ), index_( path_element ) {
  isCorrect( path_element_ );
}

[[deprecated]] void branch::modify( std::function<void( std::string & )> modify_function ) {
  modify_function( path_element_ );
}

void branch::isCorrect( std::string const &path_element ) const {
  util::throw_if<std::invalid_argument>(
      path_element.find( '\0' ) != std::string::npos, "There is prohibited characters"
  );
}

std::string branch::buildBranch() const noexcept {
  std::string branch( "" );
  for ( decltype( path_element_ )::const_iterator citr = path_element_.cbegin(); citr != path_element_.cend();
        ++citr ) {
    if ( isRoot( *citr ) == true ) {
      branch += ( *citr );
    } else {
      branch += PATH_SEPARATOR;
      branch += ( *citr );
    }
  }
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
