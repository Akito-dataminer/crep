#include "path/branch.hpp"

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <string>
#include <type_traits>

#define TEST( CONDITION ) BOOST_TEST( ( CONDITION ) == true )

BOOST_AUTO_TEST_SUITE( test_branch )

BOOST_AUTO_TEST_CASE( test_case1 ) {
  using namespace path;
  static_assert( std::is_convertible_v<std::string, branch> == true );
  static_assert( std::is_convertible_v<branch, branch> == true );
  static_assert( std::is_convertible_v<int, branch> == false );
}

BOOST_AUTO_TEST_CASE( test_case2 ) {
  using namespace path;

  branch j1( "a" );
  branch const j2( "a" ), j3( "b" );
  branch const connected1( std::string( "a" ) + PATH_SEPARATOR + std::string( "b" ) );
  branch const connected2(
      std::string( "a" ) + PATH_SEPARATOR + std::string( "b" ) + PATH_SEPARATOR + std::string( "c" )
  );
  std::string str1( "c" );

  TEST( j1 == j2 );
  TEST( j1 != j3 );

  j1 += j3;
  TEST( j1 == connected1 );
  TEST( j1 == j2 + j3 );
  TEST( j1 != j1 + j2 );

  j1 += str1;
  TEST( j1 == j2 + j3 + str1 );
  TEST( j1 == connected2 );

  // below codes should be error
  // j1 += 1;
  // j1 += 'a';
}

BOOST_AUTO_TEST_CASE( test_case3 ) {
  using namespace path;
  std::cout << std::endl;

#if _WIN32
  std::string absolute_path( "C:\\Users\\username\\AppData\\Local\\nvim\\init.lua" );
#else
  std::string absolute_path( "/usr/include/c++/11/cstdlib" );
#endif
  branch b( absolute_path );

  std::cout << "b.to_string(): " << b.to_string() << std::endl;
  TEST( absolute_path == b.to_string() );
#if _WIN32
  TEST( b.size() == 7 );
  TEST( b[0] == "C:" );
  TEST( b[1] == "Users" );
  TEST( b[2] == "username" );
  TEST( b[3] == "AppData" );
  TEST( b[4] == "Local" );
  TEST( b[5] == "nvim" );
  TEST( b[6] == "init.lua" );
#else
  BOOST_TEST( ( b.size() == 6 ) == true );
  TEST( b[0] == "/" );
  TEST( b[1] == "usr" );
  TEST( b[2] == "include" );
  TEST( b[3] == "c++" );
  TEST( b[4] == "11" );
  TEST( b[5] == "cstdlib" );
#endif
}

BOOST_AUTO_TEST_SUITE_END()
