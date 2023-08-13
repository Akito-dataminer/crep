#include "path/branch.hpp"

#include "config/config.hpp"
#include "util/throw_if.hpp"

namespace path {

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
