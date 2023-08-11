/*****************************
 * util/throw_if.hpp
 *****************************/

#pragma once

#include <functional>
#include <stdexcept>
#include <string>
#include <concepts>
#include <utility>

namespace util {

template<typename T>
concept OneOfException = std::is_base_of_v<std::exception, T>;

template <OneOfException T>
void throw_if( std::function<bool( void )> throw_condition, std::string const &error_message ) {
  if ( throw_condition() ) {
    throw T( error_message );
  }
}

template <OneOfException T>
void throw_if( bool const throw_condition, std::string const &error_message ) {
  if ( throw_condition ) {
    throw T( error_message );
  }
}

}  // namespace util
