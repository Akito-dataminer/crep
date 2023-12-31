#include "util/throw_if.hpp"

#include <boost/test/unit_test.hpp>

#include <iostream>

BOOST_AUTO_TEST_SUITE( test_throw_if )

BOOST_AUTO_TEST_CASE( test_case1 ) {
  BOOST_CHECK_THROW( crep::throw_if<std::runtime_error>( true, "error" ), std::runtime_error );
  // crep::throw_if<std::string>( false, "error" ); // error( this error is correct )
}

BOOST_AUTO_TEST_SUITE_END()
