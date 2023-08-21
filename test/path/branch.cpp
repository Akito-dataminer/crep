#include "path/branch.hpp"

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <string>
#include <type_traits>

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
  branch const connected2( std::string( "a" ) + PATH_SEPARATOR + std::string( "b" ) + PATH_SEPARATOR + std::string( "c" ) );
  std::string str1( "c" );

  BOOST_TEST( ( j1 == j2 ) == true );
  BOOST_TEST( ( j1 != j3 ) == true );

  j1 += j3;
  BOOST_TEST( ( j1 == connected1 ) == true );
  BOOST_TEST( ( j1 == j2 + j3 ) == true );
  BOOST_TEST( ( j1 != j1 + j2 ) == true );

  j1 += str1;
  BOOST_TEST( ( j1 == j2 + j3 + str1 ) == true );
  BOOST_TEST( ( j1.to_string() == connected2 ) == true );

  // below codes should be error
  // j1 += 1;
  // j1 += 'a';
}

BOOST_AUTO_TEST_CASE( test_case3 ) {
  using namespace path;

  branch j( "a" );
  j.modify( []( std::string &str ) { str += "b"; } );

  BOOST_TEST( ( j == branch( "ab" ) ) == true );
}

BOOST_AUTO_TEST_CASE( test_case4 ) {
  using namespace path;
  using namespace path::detail;

  std::string absolute_path( "/usr/include/c++/11/cstdlib" );
  detail::index arch( absolute_path );
  BOOST_TEST( ( arch.branch_num() == 6 ) == true );

  branch_token token0 = arch[0];
  branch_token token1 = arch[1];
  branch_token token2 = arch[2];
  branch_token token3 = arch[3];

  BOOST_TEST( ( token0.type() == role::ROOT ) == true );
  BOOST_TEST( ( token0.index() == 0 ) == true );
  BOOST_TEST( ( token0.length() == 1 ) == true );

  BOOST_TEST( ( token1.type() == role::BRANCH ) == true );
  BOOST_TEST( ( token1.index() == 1 ) == true );
  BOOST_TEST( ( token1.length() == 3 ) == true );

  BOOST_TEST( ( token2.type() == role::BRANCH ) == true );
  BOOST_TEST( ( token2.index() == 5 ) == true );
  BOOST_TEST( ( token2.length() == 7 ) == true );

  BOOST_TEST( ( token3.type() == role::BRANCH ) == true );
  BOOST_TEST( ( token3.index() == 13 ) == true );
  BOOST_TEST( ( token3.length() == 3 ) == true );
}

BOOST_AUTO_TEST_CASE( test_case5 ) {
  using namespace path;

  std::string absolute_path( "/usr/include/c++/11/cstdlib" );
  branch b0( "/" ), b1( "usr" ), b2( "include" ), b3( "c++" );
  branch b( absolute_path );

  BOOST_TEST( ( b[0] == b0 ) == true );
  BOOST_TEST( ( b[1] == b1 ) == true );
  BOOST_TEST( ( b[2] == b2 ) == true );
  BOOST_TEST( ( b[3] == b3 ) == true );
}

BOOST_AUTO_TEST_SUITE_END()
