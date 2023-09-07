/****************************************
 * config/config.hpp
 ****************************************/

#pragma once

#include "config/initial.hpp"
#include "path/character.hpp"
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
STATIC_CONSTEXPR char const *APPEND_DIRECTORY = "\\crep\\.cpp_skeleton";
STATIC_CONSTEXPR char const DELIMITER = '\\';
STATIC_CONSTEXPR crep::path::character::character_list invalid_character_list(
    { static_cast<char>( 1 ),
      static_cast<char>( 2 ),
      static_cast<char>( 3 ),
      static_cast<char>( 4 ),
      static_cast<char>( 5 ),
      static_cast<char>( 6 ),
      static_cast<char>( 7 ),
      static_cast<char>( 8 ),
      static_cast<char>( 9 ),
      static_cast<char>( 10 ),
      static_cast<char>( 11 ),
      static_cast<char>( 12 ),
      static_cast<char>( 13 ),
      static_cast<char>( 14 ),
      static_cast<char>( 15 ),
      static_cast<char>( 16 ),
      static_cast<char>( 17 ),
      static_cast<char>( 18 ),
      static_cast<char>( 19 ),
      static_cast<char>( 20 ),
      static_cast<char>( 21 ),
      static_cast<char>( 22 ),
      static_cast<char>( 23 ),
      static_cast<char>( 24 ),
      static_cast<char>( 25 ),
      static_cast<char>( 26 ),
      static_cast<char>( 27 ),
      static_cast<char>( 28 ),
      static_cast<char>( 29 ),
      static_cast<char>( 30 ),
      static_cast<char>( 31 ),
      '"',
      '<',
      '>',
      ':',
      '*',
      '?',
      '\\',
      '/' }
);
#elif __linux__
STATIC_CONSTEXPR char const *GET_ENVIRONMENT_VARIABLE = "HOME";
STATIC_CONSTEXPR char const *APPEND_DIRECTORY = "/.config/crep/.cpp_skeleton";
STATIC_CONSTEXPR char const DELIMITER = '/';
STATIC_CONSTEXPR crep::path::character::character_list invalid_character_list( { '\\', '\0' } );
#endif
