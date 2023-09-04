/*****************************
 * util/path
 *****************************/

#pragma once

#include <functional>
#include <string>
#include <type_traits>
#include <vector>

#include "config/config.hpp"
#include "path/branch.hpp"
#include "util/util.hpp"

namespace path {

void recursive_scan_directory( std::string const &scanning_path, std::vector<std::string> & );
std::vector<std::string> recursive_scan_directory( std::string const &scanning_path );
void recursive_scan_directory( path::branch const &scanning_path, std::vector<path::branch> & );
std::vector<path::branch> recursive_scan_directory( path::branch const &scanning_path );

}  // namespace path
