/*****************************
 * util/util.hpp
 *****************************/

#pragma once

#include <utility>

namespace util {

template<bool Cond> using if_nullp_c = std::enable_if_t<Cond, std::nullptr_t>;

} // util
