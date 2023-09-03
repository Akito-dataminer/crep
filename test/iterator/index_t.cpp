#include "iterator/npos.hpp"

#include <boost/test/unit_test.hpp>
#include <utility>

#define TEST( CONDITION ) BOOST_TEST( ( CONDITION ) == true )

BOOST_AUTO_TEST_SUITE( test_branch )

BOOST_AUTO_TEST_CASE( test_case1_npos_value ) {
  using namespace crep;
  static_assert( npos_v<std::size_t> == -1 );
}

BOOST_AUTO_TEST_CASE( test_case2_index_t ) {
  using namespace crep;
  using size_type = std::size_t;

  static_assert( static_cast<size_type>( index_t<size_type>() ) == -1 );
}

BOOST_AUTO_TEST_CASE( test_case3_index_t_constructed_by_itr ) {
  using namespace crep;
  using size_type = std::size_t;

  std::vector<char> char_list( { '\\', '\0' } );
  index_t<size_type> test_index( char_list, char_list.cbegin() );

  TEST( static_cast<size_type>( test_index ) == 1 );
}

BOOST_AUTO_TEST_SUITE_END()
