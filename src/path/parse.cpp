#include "path/parse.hpp"

namespace path {

namespace parse {

branch_parse::branch_parse( std::string const &branch_str ) : original_string_( branch_str ) {
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

role branch_parse::type_detection( std::string::const_iterator &itr, std::size_t const index ) const {
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

}  // namespace parse

}  // namespace path
