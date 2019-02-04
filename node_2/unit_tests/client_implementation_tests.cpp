#include "client_implementation.hpp"
#define BOOST_TEST_MODULE ClientImplementationTest
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( input_parameter_test )
{
		// empty input
    ClientImplementation c1("c1", 1);
		std::string address1;
		BOOST_CHECK_EQUAL(-1, c1.connect(address1));

		// lacking separator and port number
		ClientImplementation c2("c2", 2);
		std::string address2 = "127.0.0.1";
		BOOST_CHECK_EQUAL(-2, c2.connect(address2));
}
