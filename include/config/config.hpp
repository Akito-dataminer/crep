/****************************************
 * config/config.hpp
 ****************************************/

#pragma once

#include "config/initial.hpp"
#include "version.h"

#if defined( MSC_VER ) && defined( _MSVC_LANG )
#  define CXX_STD _MSVC_LANG
#else
#  define CXX_STD __cplusplus
#endif

/* C++17 was when filesystems entered the c++ standard. */
#if CXX_STD >= 201703
#  include <filesystem>
#endif

#if CXX_STD >= 202002
#  include <concepts>
#endif

#ifdef _WIN32
STATIC_CONSTEXPR char const *GET_ENVIRONMENT_VARIABLE = "LocalAppData";
STATIC_CONSTEXPR char const *APPEND_DIRECTORY = "/crep/.cpp_skeleton";
STATIC_CONSTEXPR char const PATH_SEPARATOR = '\\';
#elif __linux__
STATIC_CONSTEXPR char const *GET_ENVIRONMENT_VARIABLE = "HOME";
STATIC_CONSTEXPR char const *APPEND_DIRECTORY = "/.config/crep/.cpp_skeleton";
STATIC_CONSTEXPR char const PATH_SEPARATOR = '/';
#endif
