#include "config/config.hpp"
#include "util/path.hpp"
#include "util/throw_if.hpp"

#include <vector>
#include <string>

namespace path {

void recursive_scan_directory( std::string const &scanning_path, std::vector<std::string> &paths ) {
  for ( const auto &entry : std::filesystem::directory_iterator( scanning_path ) ) {
    paths.emplace_back( entry.path().string() );
    if ( std::filesystem::is_directory( entry ) ) {
      recursive_scan_directory( entry.path().string(), paths );
    }
  }
}

std::vector<std::string> recursive_scan_directory( std::string const &scanning_path ) {
  std::vector<std::string> paths;
  for ( const auto &entry : std::filesystem::directory_iterator( scanning_path ) ) {
    paths.emplace_back( entry.path().string() );
    if ( std::filesystem::is_directory( entry ) ) {
      recursive_scan_directory( entry.path().string(), paths );
    }
  }

  return paths;
}

branch::branch( std::string const & path_element ) : path_element_( path_element ) {
  isCorrect( path_element_ );
}

[[deprecated]] void branch::modify( std::function<void ( std::string & )> modify_function ) {
  modify_function( path_element_ );
}

void branch::isCorrect( std::string const & path_element ) const {
  util::throw_if<std::invalid_argument>(
      (bool)( ( path_element.find( '\0' ) != std::string::npos ) ),
      "There is prohibited characters"
  );
}

}  // path
