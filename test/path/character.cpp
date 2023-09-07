#include "path/character.hpp"

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <stdexcept>
#include <string>

#define TEST( CONDITION ) BOOST_TEST( ( CONDITION ) == true )

#if _WIN32
#  define TEST_ABSOLUTE_PATH "C:\\Users\\username\\AppData\\Local\\nvim\\init.lua"
#  define TEST_RELATIVE_PATH ".\\build\\src\\crep"
#  define BRANCH_NOT_COMPLETELY_PATH "test\\template"
#  define BRANCH_LIST "C:", "Users", "username", "AppData", "Local", "nvim", "init.lua"
#else
#  define TEST_ABSOLUTE_PATH "/usr/include/c++/11/cstdlib"
#  define TEST_RELATIVE_PATH "./build/src/crep"
#  define BRANCH_NOT_COMPLETELY_PATH "test/template"
#  define BRANCH_LIST "/", "usr", "include", "c++", "11", "cstdlib"
#endif

BOOST_AUTO_TEST_SUITE( test_character )

BOOST_AUTO_TEST_CASE( test_case1_character_list_feature ) {
  using namespace crep::character;
  using namespace crep::character::detail;

  constexpr character_list_impl<char, 2> list_impl( { '\\', '\0' }, std::make_index_sequence<2>() );
  static_assert( std::is_trivially_destructible_v<decltype( list_impl )> );
  static_assert( std::is_trivially_move_constructible_v<decltype( list_impl )> );
  static_assert( std::is_trivially_copy_constructible_v<decltype( list_impl )> );

  constexpr character_list devil_char_list( { '\\', '\0' } );
  static_assert( std::is_trivially_destructible_v<decltype( devil_char_list )> );
  static_assert( std::is_trivially_move_constructible_v<decltype( devil_char_list )> );
  static_assert( std::is_trivially_copy_constructible_v<decltype( devil_char_list )> );
}

BOOST_AUTO_TEST_CASE( test_case1_character_list_functions ) {
  using namespace crep::character;

  constexpr char const list[] = { '\\', '\0' };
  constexpr character_list devil_char_list( { '\\', '\0' } );
  static_assert( devil_char_list.size() == 2 );
  static_assert( devil_char_list[0] == list[0] );
  static_assert( devil_char_list[1] == list[1] );

  static_assert( devil_char_list.is_there( '\\' ) == true );
}

BOOST_AUTO_TEST_SUITE_END()
