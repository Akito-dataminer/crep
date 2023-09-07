#include "path/parse.hpp"

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <string>
#include <type_traits>

BOOST_AUTO_TEST_SUITE( test_branch )

BOOST_AUTO_TEST_CASE( test_case1 ) {
  using namespace crep::path::parse;

#if _WIN32
  std::string absolute_path( "C:\\Users\\username\\AppData\\Local\\nvim\\init.lua" );
  branch_parse parser( absolute_path );
  BOOST_TEST( parser[0] == "C:" );
  BOOST_TEST( parser[1] == "Users" );
  BOOST_TEST( parser[2] == "username" );
  BOOST_TEST( parser[3] == "AppData" );
  BOOST_TEST( parser[4] == "Local" );
  BOOST_TEST( parser[5] == "nvim" );
  BOOST_TEST( parser[6] == "init.lua" );
#else
  std::string absolute_path( "/usr/include/c++/11/cstdlib" );

  branch_parse parser( absolute_path );
  BOOST_TEST( parser[0] == "/" );
  BOOST_TEST( parser[1] == "usr" );
  BOOST_TEST( parser[2] == "include" );
  BOOST_TEST( parser[3] == "c++" );
  BOOST_TEST( parser[4] == "11" );
  BOOST_TEST( parser[5] == "cstdlib" );
#endif
}

BOOST_AUTO_TEST_SUITE_END()
