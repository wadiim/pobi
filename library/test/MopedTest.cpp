#include "model/Moped.h"

#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

struct TestSuiteMotorVehicleFixture
{
	const std::string plateNumber = "13-954";
	const unsigned int basePrice = 86;
	const unsigned int engineDisplacement = 1587;
	MotorVehicle *moped;

	TestSuiteMotorVehicleFixture()
        {
		moped = new Moped(plateNumber, basePrice, engineDisplacement);
	}

	~TestSuiteMotorVehicleFixture()
        {
		delete moped;
	}
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteMotorVehicle, TestSuiteMotorVehicleFixture)

	BOOST_AUTO_TEST_CASE(TestGetEngineDisplacement)
	{
		BOOST_TEST(moped->getEngineDisplacement() == engineDisplacement);
	}

	BOOST_AUTO_TEST_CASE(TestSetEngineDisplacement)
	{
		const unsigned int newDisplacement = 1000;
		moped->setEngineDisplacement(newDisplacement);
		BOOST_TEST(moped->getEngineDisplacement() == newDisplacement);
	}

	BOOST_AUTO_TEST_CASE(TestGetActualRentalPriceIfEngineDisplacementIsLessThan1000)
	{
		moped->setEngineDisplacement(500);
		BOOST_TEST(moped->getActualRentalPrice() == moped->getBasePrice(), tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(TestGetActualRentalPriceIfEngineDisplacementIsGreaterThan2000)
	{
		moped->setEngineDisplacement(3000);
		BOOST_TEST(moped->getActualRentalPrice() == moped->getBasePrice() * 1.5, tt::tolerance(0.01));
	}

	BOOST_AUTO_TEST_CASE(TestGetActualRentalPriceIfEngineDisplacementIsBetween1000And2000)
	{
		for (unsigned int d = 1000, m = 0; d <= 2000; d += 200, m += 1)
		{
			moped->setEngineDisplacement(d);
			BOOST_TEST(moped->getActualRentalPrice() == moped->getBasePrice() * (1.0 + m / 10.0), tt::tolerance(0.01));
		}
	}

	BOOST_AUTO_TEST_CASE(TestGetVehicleInfo)
	{
		BOOST_TEST(moped->getVehicleInfo() == plateNumber
                                + " " + std::to_string(basePrice)
                                + " " + std::to_string(engineDisplacement));
	}

        BOOST_AUTO_TEST_CASE(TestGetInfo)
        {
                BOOST_TEST(moped->getInfo() == moped->getVehicleInfo());
        }

BOOST_AUTO_TEST_SUITE_END()