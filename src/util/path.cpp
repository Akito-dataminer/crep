#include "config/config.hpp"
#include "util/path.hpp"

#include <vector>
#include <string>

void recursive_scan_directory( std::string const &scanning_path, std::vector<std::string> &paths ) {
  for ( const auto &entry : std::filesystem::directory_iterator( scanning_path ) ) {
    paths.emplace_back( entry.path().string() );
    if ( std::filesystem::is_directory( entry ) ) {
      recursive_scan_directory( entry.path().string(), paths );
    }
  }
}

