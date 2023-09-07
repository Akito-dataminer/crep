/*****************************
 * util/throw_if.hpp
 *****************************/

#pragma once

#include <stdexcept>
#include <string>
#include <utility>

#include "config/config.hpp"
#include "util/util.hpp"

namespace crep {

namespace util {

#ifdef __cpp_concepts
template <typename T>
concept one_of_exception = std::is_base_of_v<std::exception, T>;
#else
template <typename T>
STATIC_CONSTEXPR bool const is_exception = std::is_base_of_v<std::exception, T>;
#endif

#ifdef __cpp_concepts
#  define TEMPLATE_HEAD_THROW_IF template <one_of_exception T>
#else
#  define TEMPLATE_HEAD_THROW_IF template <typename T, crep::if_nullp_c<is_exception<T>> * = nullptr>
#endif

TEMPLATE_HEAD_THROW_IF
void throw_if( bool const throw_condition, std::string const &error_message ) {
  if ( throw_condition ) {
    throw T( error_message );
  }
}

}  // namespace util

}  // namespace crep
