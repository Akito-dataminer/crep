/*****************************
 * util/path
 *****************************/

#pragma once

#include <string>
#include <vector>

void recursive_scan_directory( std::string const &scanning_path, std::vector<std::string> &paths );
std::vector<std::string> recursive_scan_directory( std::string const &scanning_path );
