#include "model/Client.h"
#include "model/Address.h"
#include "exceptions/ClientException.h"

#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

struct TestSuiteClientFixture
{
	const std::string firstName = "Lain";
	const std::string lastName = "Iwakura";
	const std::string id = "1094795585";
	ClientPtr client;

	const std::string city = "Tokyo";
	const std::string street = "Mimorigasaka";
	const std::string number = "2";
	AddressPtr address;

	TestSuiteClientFixture()
        {
                address = std::make_shared<Address>(city, street, number);
		client = std::make_shared<Client>(firstName, lastName, id, address);
	}
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteClient, TestSuiteClientFixture)

	BOOST_AUTO_TEST_CASE(TestGetFirstName)
        {
		BOOST_TEST(client->getFirstName() == firstName);
	}

	BOOST_AUTO_TEST_CASE(TestGetLastName)
        {
		BOOST_TEST(client->getLastName() == lastName);
	}

	BOOST_AUTO_TEST_CASE(TestGetPersonalID)
        {
		BOOST_TEST(client->getPersonalId() == id);
	}

        BOOST_AUTO_TEST_CASE(TestGetId)
        {
                BOOST_TEST(client->getId() == client->getPersonalId());
        }

	BOOST_AUTO_TEST_CASE(TestGetClientInfo)
        {
		std::string exp = firstName + " " + lastName + " " + id + " "
                                  + city + " " + street + " " + number + " "
                                  + "Default 1 $0.00";
		BOOST_TEST(client->getClientInfo() == exp);
	}

        BOOST_AUTO_TEST_CASE(TestGetInfo)
        {
                BOOST_TEST(client->getInfo() == client->getClientInfo());
        }

	BOOST_AUTO_TEST_CASE(TestSetFirstNameIfNonEmptyStringThenChangesTheFirstName)
        {
		const std::string fn("Mika");
		client->setFirstName(fn);
		BOOST_TEST(client->getFirstName() == fn);
	}

	BOOST_AUTO_TEST_CASE(TestSetLastNameIfNonEmptyStringThenChangesTheLastName)
        {
		const std::string ln("Yamamoto");
		client->setLastName(ln);
		BOOST_TEST(client->getLastName() == ln);
	}

	BOOST_AUTO_TEST_CASE(TestSetFirstNameIfEmptyStringThenThrowsClientException)
        {
                BOOST_CHECK_THROW(client->setFirstName(""), ClientException);
	}

	BOOST_AUTO_TEST_CASE(TestSetLastNameIfEmptyStringThenThrowsClientException)
        {
                BOOST_CHECK_THROW(client->setLastName(""), ClientException);
	}

	BOOST_AUTO_TEST_CASE(TestGetAddress)
        {
		BOOST_TEST(client->getAddress() == address);
	}

	BOOST_AUTO_TEST_CASE(TestSetAddressIfNonNullThenChangesAddress)
        {
		auto a = std::make_shared<Address>("Kyoto", "Kiyamachi", "16");
		client->setAddress(a);
		BOOST_TEST(client->getAddress() == a);
	}

	BOOST_AUTO_TEST_CASE(TestSetAddressIfNullThenThrowsClientException)
        {
                BOOST_CHECK_THROW(client->setAddress(nullptr), ClientException);
	}

	BOOST_AUTO_TEST_CASE(TestGetMaxVehiclesIfDefaultClientTypeThenReturns1)
        {
		BOOST_TEST(client->getMaxVehicles() == 1);
	}

	BOOST_AUTO_TEST_CASE(TestSetClientTypeIfPlatiniumThenMaxVehiclesIncreasesTo5)
        {
		client->setClientType(std::make_shared<Platinum>());
		BOOST_TEST(client->getMaxVehicles() == 5);
	}

	BOOST_AUTO_TEST_CASE(TestApplyDiscountIfGoldClientTypeThenApplies5PercentDiscount)
        {
		const double price = 22.0;
		client->setClientType(std::make_shared<Gold>());
		BOOST_TEST(client->applyDiscount(price) == 0.95*price, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(TestIsArchivedIfInitialStateThenReturnsFalse)
        {
		BOOST_TEST(client->isArchived() == false);
	}

	BOOST_AUTO_TEST_CASE(TestSetArchived)
        {
		client->setArchive(true);
		BOOST_TEST(client->isArchived() == true);
	}

BOOST_AUTO_TEST_SUITE_END()
