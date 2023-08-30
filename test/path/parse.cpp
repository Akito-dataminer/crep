#include "path/parse.hpp"

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <string>
#include <type_traits>

BOOST_AUTO_TEST_SUITE( test_branch )

BOOST_AUTO_TEST_CASE( test_case1 ) {
  using namespace path::parse;

#if _WIN32
  std::string absolute_path( "C:\\Users\\username\\AppData\\Local\\nvim\\init.lua" );
#else
  std::string absolute_path( "/usr/include/c++/11/cstdlib" );
#endif

  branch_parse parser( absolute_path );
  BOOST_TEST( parser[0] == "/" );
  BOOST_TEST( parser[1] == "usr" );
  BOOST_TEST( parser[2] == "include" );
  BOOST_TEST( parser[3] == "c++" );
  BOOST_TEST( parser[4] == "11" );
  BOOST_TEST( parser[5] == "cstdlib" );
}

BOOST_AUTO_TEST_SUITE_END()
