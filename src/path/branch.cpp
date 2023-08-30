#include "path/branch.hpp"

#include <iterator>

#include "config/config.hpp"
#include "util/throw_if.hpp"

namespace path {

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
