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
  branch const connected( "a/b" );
  std::string str1( "c" );

  BOOST_TEST( ( j1 == j2 ) == true );
  BOOST_TEST( ( j1 != j3 ) == true );

  j1 += j3;
  BOOST_TEST( ( j1 == connected ) == true );
  BOOST_TEST( ( j1 == j2 + j3 ) == true );
  BOOST_TEST( ( j1 != j1 + j2 ) == true );

  j1 += str1;
  BOOST_TEST( ( j1 == j2 + j3 + str1 ) == true );
  BOOST_TEST( ( j1.to_string() == std::string( "a/b/c" ) ) == true );

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

BOOST_AUTO_TEST_CASE( test_case4 ) { using namespace path; }

BOOST_AUTO_TEST_SUITE_END()
