#include "util/path.hpp"

#include <string>
#include <vector>

#include "config/config.hpp"
#include "util/throw_if.hpp"

namespace crep {

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

void recursive_scan_directory( path::branch const &scanning_path, std::vector<path::branch> &branches ) {
  for ( const auto &entry :
        std::filesystem::directory_iterator( static_cast<std::filesystem::path>( scanning_path ) ) ) {
    branches.emplace_back( entry.path().string() );
    if ( std::filesystem::is_directory( entry ) ) {
      recursive_scan_directory( entry.path().string(), branches );
    }
  }
}

std::vector<path::branch> recursive_scan_directory( path::branch const &scanning_path ) {
  std::vector<path::branch> branches;

  for ( const auto &entry :
        std::filesystem::directory_iterator( static_cast<std::filesystem::path>( scanning_path ) ) ) {
    branches.emplace_back( entry.path().string() );
    if ( std::filesystem::is_directory( entry ) ) {
      recursive_scan_directory( entry.path().string(), branches );
    }
  }

  return branches;
}

}  // namespace path

}  // namespace crep
