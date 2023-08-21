#include "path/branch.hpp"

#include <iterator>

#include "config/config.hpp"
#include "util/throw_if.hpp"

namespace path {

BranchIndex::BranchIndex( std::string const &branch_str ) {
  for ( std::string::const_iterator itr = branch_str.begin(); itr != branch_str.end(); ++itr ) {
    std::size_t head_index = std::distance( branch_str.begin(), itr );
    BranchType token_type = type_detection( itr, head_index );
    if ( token_type != BranchType::DELIMITER ) {
      token_sequence_.emplace_back( token_type, head_index );
    }

    switch ( token_type ) {
      case BranchType::ROOT:
#if _WIN32
        ++itr;
        continue;
#else
        continue;
#endif
        break;
      case BranchType::DELIMITER:
        continue;
      case BranchType::BRANCH:
        for ( ;; ++itr ) {
          if ( ( *( itr + 1 ) == PATH_SEPARATOR ) || ( ( itr + 1 ) == branch_str.cend() ) ) {
            break;
          }
        }
    }
  }
}

BranchType BranchIndex::type_detection( std::string::const_iterator &itr, std::size_t const index ) const noexcept {
  BranchType type;
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
      type = BranchType::ROOT;
    } else {
      type = BranchType::DELIMITER;
    }
  } else {
    type = BranchType::BRANCH;
  }
#endif
  return type;
}

branch::branch( std::string const &path_element ) : path_element_( path_element ) { isCorrect( path_element_ ); }

[[deprecated]] void branch::modify( std::function<void( std::string & )> modify_function ) {
  modify_function( path_element_ );
}

void branch::isCorrect( std::string const &path_element ) const {
  util::throw_if<std::invalid_argument>(
      path_element.find( '\0' ) != std::string::npos, "There is prohibited characters"
  );
}

}  // namespace path
