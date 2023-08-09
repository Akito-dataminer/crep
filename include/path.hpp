/*****************************
 * path
 *****************************/

#include <vector>
#include <string>

#pragma once

void recursive_scan_directory( std::string const &, std::vector<std::string> & );
std::vector<std::string> recursive_scan_directory( std::string const & );
