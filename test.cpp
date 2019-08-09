#define BOOST_TEST_MODULE test_allocator

#include <boost/test/unit_test.hpp>
#include "factorial.h"

BOOST_AUTO_TEST_SUITE(test_lib)

BOOST_AUTO_TEST_CASE(test_allocator)
{  
  BOOST_CHECK(my_lib::factorial(1) == 1);
  BOOST_CHECK(my_lib::factorial(2) == 2);
  BOOST_CHECK(my_lib::factorial(3) == 6);
  BOOST_CHECK(my_lib::factorial(4) == 24);
  BOOST_CHECK(my_lib::factorial(5) == 120);  
}

BOOST_AUTO_TEST_SUITE_END()