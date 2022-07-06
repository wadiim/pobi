#include "typedefs.h"
#include "model/Address.h"

#include <boost/test/unit_test.hpp>

struct TestSuiteAddressFixture
{
	const std::string city = "Tokyo";
	const std::string street = "Mimorigasaka";
	const std::string number = "2";
	AddressPtr address;

	TestSuiteAddressFixture()
        {
		address = std::make_shared<Address>(city, street, number);
	}
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteAddress, TestSuiteAddressFixture)

	BOOST_AUTO_TEST_CASE(TestGetCity)
        {
		BOOST_TEST(address->getCity() == city);
	}

	BOOST_AUTO_TEST_CASE(TestGetStreet)
        {
		BOOST_TEST(address->getStreet() == street);
	}

	BOOST_AUTO_TEST_CASE(TestGetNumber)
        {
		BOOST_TEST(address->getNumber() == number);
	}

	BOOST_AUTO_TEST_CASE(TestGetAddressInfo)
        {
		BOOST_TEST(address->getAddressInfo() == city + " " + street + " " + number);
	}

BOOST_AUTO_TEST_SUITE_END()
