/*****************************
 * util/path
 *****************************/

#pragma once

#include "config/config.hpp"
#include "util/util.hpp"

#include <functional>
#include <string>
#include <type_traits>
#include <vector>
#include <type_traits>

namespace path {

void recursive_scan_directory( std::string const &scanning_path, std::vector<std::string> &paths );
std::vector<std::string> recursive_scan_directory( std::string const &scanning_path );

} // path
