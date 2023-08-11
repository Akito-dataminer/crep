#include "util/path.hpp"

#include <boost/test/unit_test.hpp>

#include <iostream>
#include <type_traits>

BOOST_AUTO_TEST_SUITE( test_joint )

BOOST_AUTO_TEST_CASE( test_case1 ) {
  using namespace path;
  static_assert( std::is_convertible_v<std::string, joint> == true );
  static_assert( std::is_convertible_v<joint, joint> == true );
  static_assert( std::is_convertible_v<int, joint> == false );
}

BOOST_AUTO_TEST_CASE( test_case2 ) {
  using namespace path;

  joint j1( "a" );
  joint const j2( "a" ), j3( "b" );
  joint const concatenated( "a/b" );

  BOOST_TEST( ( j1 == j2 ) == true );
  BOOST_TEST( ( j1 != j3 ) == true );

  j1 += j3;
  BOOST_TEST( ( j1 == concatenated ) == true );
  BOOST_TEST( ( j1 == j2 + j3 ) == true );
  BOOST_TEST( ( j1 != j1 + j2 ) == true );
}

BOOST_AUTO_TEST_CASE( test_case3 ) {
  using namespace path;

  joint j( "a" );
  j.modify( []( std::string & str ) { str += "b"; } );

  BOOST_TEST( ( j == joint( "ab" ) ) == true );
}

BOOST_AUTO_TEST_CASE( test_case4 ) {
  using namespace path;
}

BOOST_AUTO_TEST_SUITE_END()
