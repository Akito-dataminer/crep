#include "path/branch.hpp"

#include <iostream>
#include <iterator>

#include "config/config.hpp"
#include "util/throw_if.hpp"

namespace path {

namespace detail {

index::index( std::string const &branch_str ) {
  for ( std::string::const_iterator itr = branch_str.begin(); itr != branch_str.end(); ++itr ) {
    std::size_t head_index = std::distance( branch_str.begin(), itr );
    role token_type = type_detection( itr, head_index );
    std::size_t length = 0;

    switch ( token_type ) {
      case role::ROOT:
#if _WIN32
        length = 2;
        ++itr;
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
        for ( ;; ++itr ) {
          ++length;
          if ( ( *( itr + 1 ) == PATH_SEPARATOR ) || ( ( itr + 1 ) == branch_str.cend() ) ) {
            break;
          }
        }
      default:
        break;
    }

    std::cout << "head_index: " << head_index << std::endl;
    if ( token_type != role::DELIMITER ) {
      token_sequence_.emplace_back( token_type, head_index, length );
    }
  }
}

role index::type_detection( std::string::const_iterator &itr, std::size_t const index ) const noexcept {
  role type;
#if _WIN32
  // ただし、このタイプ判定が期待通りに働くためには
  // 必ず2文字目にアクセス可能で、かつブランチの途中でこの関数が呼び出されない
  // という条件が成り立っている必要がある。
  // 例えばC:\\Users\\...のようなパスがあった場合、
  // その2文字目を指すイテレータが、この関数に渡されてはいけない。
  if ( *( itr + 1 ) == ':' ) {
    if ( *itr >= 'A' && *itr <= 'Z' ) {
      type = ROOT;
    }
  } else if ( *itr == PATH_SEPARATOR ) {
    type = Type::DELIMITER;
  } else {
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

}  // namespace path
