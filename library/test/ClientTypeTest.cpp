#include "model/ClientType.h"

#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

struct TestSuiteClientTypeFixture
{
	const double price = 220.50;

	ClientType *defaultClient;
	ClientType *bronzeClient;
	ClientType *silverClient;
	ClientType *goldClient;
	ClientType *platinumClient;
	ClientType *diamondClient;

	TestSuiteClientTypeFixture()
	{
		defaultClient = new Default();
		bronzeClient = new Bronze();
		silverClient = new Silver();
		goldClient = new Gold();
		platinumClient = new Platinum();
		diamondClient = new Diamond();
	}

	~TestSuiteClientTypeFixture()
	{
		delete defaultClient;
		delete bronzeClient;
		delete silverClient;
		delete goldClient;
		delete platinumClient;
		delete diamondClient;
	}
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteClientType, TestSuiteClientTypeFixture)

	BOOST_AUTO_TEST_CASE(TestGetMaxVehiclesIfDefaultClientThenReturns1)
	{
		BOOST_TEST(defaultClient->getMaxVehicles() == 1);
	}

	BOOST_AUTO_TEST_CASE(TestApplyDiscountIfDefaultClientThenReturnsUnchangedPrice)
	{
		BOOST_TEST(defaultClient->applyDiscount(price) == price, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(TestGetTypeInfoIfDefaultClient)
	{
		BOOST_TEST(defaultClient->getTypeInfo() == "Default 1 $0.00");
	}

	BOOST_AUTO_TEST_CASE(TestGetMaxVehiclesIfBronzeClientThenReturns2)
	{
		BOOST_TEST(bronzeClient->getMaxVehicles() == 2);
	}

	BOOST_AUTO_TEST_CASE(TestApplyDiscountIfBrozneClientThenReturnsPriceReducedBy3)
	{
		BOOST_TEST(bronzeClient->applyDiscount(price) == price - 3.0, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(TestApplyDiscountIfBronzeClientAndPriceLessThanDiscountThenReturnsUnchangedPrice)
	{
		const double newPrice = 2.5;
		BOOST_TEST(bronzeClient->applyDiscount(newPrice) == newPrice, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(TestApplyDiscountIfBronzeClientAndPriceEqualDiscountThenReturnsUnchangedPrice)
	{
		const double newPrice = 3.0;
		BOOST_TEST(bronzeClient->applyDiscount(newPrice) == newPrice, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(TestGetTypeInfoIfBronzeClient)
	{
		BOOST_TEST(bronzeClient->getTypeInfo() == "Bronze 2 $3.00");
	}

	BOOST_AUTO_TEST_CASE(TestGetMaxVehiclesIfSilverClientThenReturns3)
	{
		BOOST_TEST(silverClient->getMaxVehicles() == 3);
	}

	BOOST_AUTO_TEST_CASE(TestApplyDiscountIfSilverClientThenReturnsPriceReducedBy6)
	{
		BOOST_TEST(silverClient->applyDiscount(price) == price - 6.0, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(TestApplyDiscountIfSilverClientAndPriceLessThanDiscountThenReturnsUnchangedPrice)
	{
		const double newPrice = 2.5;
		BOOST_TEST(silverClient->applyDiscount(newPrice) == newPrice, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(TestApplyDiscountIfSilverClientAndPriceEqualDiscountThenReturnsUnchangedPrice)
	{
		const double newPrice = 6.0;
		BOOST_TEST(silverClient->applyDiscount(newPrice) == newPrice, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(TestGetTypeInfoIfSilverClient)
	{
		BOOST_TEST(silverClient->getTypeInfo() == "Silver 3 $6.00");
	}

	BOOST_AUTO_TEST_CASE(TestGetMaxVehiclesIfGoldClientThenReturns4)
	{
		BOOST_TEST(goldClient->getMaxVehicles() == 4);
	}

	BOOST_AUTO_TEST_CASE(TestApplyDiscountIfGoldClientThenReturnsPriceReducedBy5Percent)
	{
		BOOST_TEST(goldClient->applyDiscount(price) == 0.95*price, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(TestGetTypeInfoIfGold)
	{
		BOOST_TEST(goldClient->getTypeInfo() == "Gold 4 5%");
	}

	BOOST_AUTO_TEST_CASE(TestGetMaxVehiclesIfPlatinumClientThenReturns5)
	{
		BOOST_TEST(platinumClient->getMaxVehicles() == 5);
	}

	BOOST_AUTO_TEST_CASE(TestApplyDiscountIfPlatinumClientThenReturnsPriceReducedBy10Percent)
	{
		BOOST_TEST(platinumClient->applyDiscount(price) == 0.9*price, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(TestGetTypeInfoIfPlatinum)
	{
		BOOST_TEST(platinumClient->getTypeInfo() == "Platinum 5 10%");
	}

	BOOST_AUTO_TEST_CASE(TestGetMaxVehiclesIfDiamondClientThenReturns10)
	{
		BOOST_TEST(diamondClient->getMaxVehicles() == 10);
	}

	BOOST_AUTO_TEST_CASE(TestApplyDiscountIfDiamondClientAndPriceLessThan125ThenReturnsPriceReducedBy10Percent)
	{
		const double p = 50.0;
		BOOST_TEST(diamondClient->applyDiscount(p) == 0.9*p, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(TestApplyDiscountIfDiamondClientAndPriceEquals125ThenReturnsPriceReducedBy10Percent)
	{
		const double p = 125.0;
		BOOST_TEST(diamondClient->applyDiscount(p) == 0.9*p, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(TestApplyDiscountIfDiamondClientAndPriceIsBetween125And250ThenReturnsPriceReducedBy20Percent)
	{
		const double p = 200.0;
		BOOST_TEST(diamondClient->applyDiscount(p) == 0.8*p, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(TestApplyDiscountIfDiamondClientAndPriceEquals250ThenReturnsPriceReducedBy20Percent)
	{
		const double p = 250.0;
		BOOST_TEST(diamondClient->applyDiscount(p) == 0.8*p, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(TestApplyDiscountIfDiamondClientAndPriceIsBetween250And500ThenReturnsPriceReducedBy30Percent)
	{
		const double p = 300.75;
		BOOST_TEST(diamondClient->applyDiscount(p) == 0.7*p, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(TestApplyDiscountIfDiamondClientAndPriceEquals500ThenReturnsPriceReducedBy30Percent)
	{
		const double p = 500.0;
		BOOST_TEST(diamondClient->applyDiscount(p) == 0.7*p, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(TestApplyDiscountIfDiamondClientAndPriceGreaterThan500ThenReturnsPriceReducedBy40Percent)
	{
		const double p = 1337.0;
		BOOST_TEST(diamondClient->applyDiscount(p) == 0.6*p, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(TestGetTypeInfoIfDiamondClient)
	{
		BOOST_TEST(diamondClient->getTypeInfo() == "Diamond 10 10%/20%/30%/40%");
	}

BOOST_AUTO_TEST_SUITE_END()
