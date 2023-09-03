#include "path/branch.hpp"

#include <array>
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

#include "iterator/index_t.hpp"

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
  branch const connected1( std::string( "a" ) + DELIMITER + std::string( "b" ) );
  branch const connected2( std::string( "a" ) + DELIMITER + std::string( "b" ) + DELIMITER + std::string( "c" ) );
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

  std::string absolute_path( TEST_ABSOLUTE_PATH );
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

BOOST_AUTO_TEST_CASE( test_case4_branch_truncate_single ) {
#undef CORRECT_BRANCH_LIST
#undef TRUNCATE_BRANCH
#if _WIN32
#  define CORRECT_BRANCH_LIST "C:", "Users", "username", "AppData", "Local", "init.lua"
#  define TRUNCATE_BRANCH "nvim"
#else
#  define CORRECT_BRANCH_LIST "/", "usr", "include", "c++", "cstdlib"
#  define TRUNCATE_BRANCH "11"
#endif

  using namespace path;

  std::string absolute_path( TEST_ABSOLUTE_PATH );
  branch b( absolute_path );
  std::vector<std::string> truncated_single_branches = { CORRECT_BRANCH_LIST };

  b.truncate( std::string( TRUNCATE_BRANCH ) );

  std::cout << std::endl;
  for ( auto [branch_itr, correct_itr] = std::pair{ b.begin(), truncated_single_branches.begin() };
        branch_itr != b.end(); ++branch_itr, ++correct_itr ) {
    std::cout << "*array_itr: " << *correct_itr << std::endl;
    std::cout << "*branch_itr: " << *branch_itr << std::endl;
    TEST( *branch_itr == *correct_itr );
  }
}

BOOST_AUTO_TEST_CASE( test_case4_branch_truncate_multiple ) {
#undef CORRECT_BRANCH_LIST
#undef TRUNCATE_BRANCH
#if _WIN32
#  define CORRECT_BRANCH_LIST "C:", "Users", "username", "AppData", "init.lua"
#  define TRUNCATE_BRANCH "Local\\nvim"
#else
#  define CORRECT_BRANCH_LIST "/", "usr", "include", "cstdlib"
#  define TRUNCATE_BRANCH "c++/11"
#endif

  using namespace path;

  std::string absolute_path( TEST_ABSOLUTE_PATH );
  branch b( absolute_path );

  std::vector<std::string> truncated_single_branches = { CORRECT_BRANCH_LIST };

#if _WIN32
  b.truncate( std::string( "Local\\nvim" ) );
#else
  b.truncate( std::string( "c++/11" ) );
#endif

  std::cout << std::endl;
  for ( auto [branch_itr, correct_itr] = std::pair{ b.begin(), truncated_single_branches.begin() };
        branch_itr != b.end(); ++branch_itr, ++correct_itr ) {
    std::cout << "*array_itr: " << *correct_itr << std::endl;
    std::cout << "*branch_itr: " << *branch_itr << std::endl;
    TEST( *branch_itr == *correct_itr );
  }
}

BOOST_AUTO_TEST_CASE( test_case4_branch_truncate_error ) {
#undef TRUNCATE_BRANCH
#if _WIN32
#  define TRUNCATE_BRANCH "Local\\nvim\\init.lua\\length_over"
#else
#  define TRUNCATE_BRANCH "c++/11/cstdlib/error/length_over"
#endif

  using namespace path;

  branch b( std::string( TEST_ABSOLUTE_PATH ) );
  BOOST_CHECK_THROW( b.truncate( branch( TRUNCATE_BRANCH ) ), std::invalid_argument );
}

BOOST_AUTO_TEST_CASE( test_case5_to_string_relative_path ) {
  using namespace path;
  std::cout << std::endl;

  std::string relative_path( TEST_RELATIVE_PATH );
  branch b( relative_path );

  std::cout << "b.to_string(): " << b.to_string() << std::endl;
  TEST( relative_path == b.to_string() );
  TEST( b[0] == "." );
  TEST( b[1] == "build" );
  TEST( b[2] == "src" );
  TEST( b[3] == "crep" );
}

BOOST_AUTO_TEST_CASE( test_case5_to_string_branch ) {
  using namespace path;
  std::cout << std::endl;

  std::string branch_string( BRANCH_NOT_COMPLETELY_PATH );
  branch b( branch_string );

  std::cout << "b.to_string(): " << b.to_string() << std::endl;
  TEST( branch_string == b.to_string() );
  TEST( b[0] == "test" );
  TEST( b[1] == "template" );
}

BOOST_AUTO_TEST_CASE( test_case6_contain ) {
  using namespace path;
  std::cout << std::endl;

  std::string branch_string( TEST_RELATIVE_PATH );
  branch b( branch_string );

  std::cout << "src/crep index: " << b.contains( branch( std::string( "src" ) + DELIMITER + std::string( "crep" ) ) )
            << std::endl;
  TEST( static_cast<std::size_t>( b.contains( branch( "crep" ) ) ) == 3 );
  TEST(
      static_cast<std::size_t>( b.contains( branch( std::string( "src" ) + DELIMITER + std::string( "crep" ) ) ) ) == 2
  );
  TEST(
      static_cast<std::size_t>( b.contains( branch( std::string( "src" ) + DELIMITER + std::string( "crep" ) ) ) ) == 2
  );
}

BOOST_AUTO_TEST_CASE( test_case6_not_contain ) {
  using namespace path;
  using size_type = path::branch::index_type::value_type;
  std::cout << std::endl;

  std::string branch_string( TEST_RELATIVE_PATH );
  branch b( branch_string );

  std::cout << "not_contain index: " << b.contains( branch( "not_contain" ) ) << std::endl;
  std::cout << "crep::npos_v: " << crep::npos_v<size_type> << std::endl;
  std::cout << "static_cast<size_type>( crep::index_t<size_type>() ): "
            << static_cast<size_type>( crep::index_t<size_type>() ) << std::endl;
  TEST( static_cast<size_type>( crep::index_t<size_type>() ) == crep::npos_v<size_type> );
  TEST( static_cast<size_type>( b.contains( branch( "not_contain" ) ) ) == crep::npos_v<size_type> );
}

BOOST_AUTO_TEST_SUITE_END()
