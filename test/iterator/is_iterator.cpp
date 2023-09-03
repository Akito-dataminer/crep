#include "iterator/is_iterator.hpp"

#include <boost/test/unit_test.hpp>
#include <type_traits>
#include <utility>
#include <vector>

#define TEST( CONDITION ) BOOST_TEST( ( CONDITION ) == true )

BOOST_AUTO_TEST_SUITE( test_branch )

BOOST_AUTO_TEST_CASE( test_case1_npos_value ) {
  using namespace crep;
  using namespace crep::detail;
  std::vector<char> char_list( { '\0', '\\' } );
  using itr_type = decltype( char_list.cbegin() );

  static_assert( std::is_invocable_v<decltype( &itr_type::operator* ), itr_type> );

  static_assert( has_iterator_category_t<itr_type>::value );
#if CXX_STD < 202002
  static_assert( does_satisfy_minimum_iterator_requirement_v<itr_type> );
#endif
}

BOOST_AUTO_TEST_SUITE_END()
