#include "typedefs.h"
#include "model/Car.h"

#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

struct TestSuiteCarFixture
{
	const std::string plateNumber = "13-954";
	const unsigned int basePrice = 86;
	const unsigned int engineDisplacement = 1587;
	SegmentType segment = SegmentType::A;
	std::shared_ptr<Car> car;

	TestSuiteCarFixture()
	{
		car = std::make_shared<Car>(plateNumber, basePrice, engineDisplacement, segment);
	}
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteCar, TestSuiteCarFixture)

	BOOST_AUTO_TEST_CASE(TestGetSegment)
	{
		BOOST_TEST(car->getSegment() == segment);
	}

	BOOST_AUTO_TEST_CASE(TestSetSegment)
	{
		auto s = SegmentType::D;
		car->setSegment(s);
		BOOST_TEST(car->getSegment() == s);
	}

        BOOST_AUTO_TEST_CASE(TestGetActualRentalPriceIfSegmentIsA)
        {
                car->setSegment(SegmentType::A);
                BOOST_TEST(car->getActualRentalPrice() == car->getBasePrice(), tt::tolerance(0.01));
        }

        BOOST_AUTO_TEST_CASE(TestGetActualRentalPriceIfSegmentIsB)
        {
                car->setSegment(SegmentType::B);
                BOOST_TEST(car->getActualRentalPrice() == car->getBasePrice() * 1.1, tt::tolerance(0.01));
        }

	BOOST_AUTO_TEST_CASE(TestGetActualRentalPriceIfSegmentIsC)
	{
		car->setSegment(SegmentType::C);
		BOOST_TEST(car->getActualRentalPrice() == car->getBasePrice() * 1.2, tt::tolerance(0.01));
	}

        BOOST_AUTO_TEST_CASE(TestGetActualRentalPriceIfSegmentIsD)
        {
                car->setSegment(SegmentType::D);
                BOOST_TEST(car->getActualRentalPrice() == car->getBasePrice() * 1.3, tt::tolerance(0.01));
        }

        BOOST_AUTO_TEST_CASE(TestGetActualRentalPriceIfSegmentIsE)
        {
                car->setSegment(SegmentType::E);
                BOOST_TEST(car->getActualRentalPrice() == car->getBasePrice() * 1.4, tt::tolerance(0.01));
        }

	BOOST_AUTO_TEST_CASE(TestGetVehicleInfo)
	{
		BOOST_TEST(car->getVehicleInfo() == plateNumber
                                + " " + std::to_string(basePrice)
                                + " " + std::to_string(engineDisplacement)
                                + " " + std::to_string(segment));
	}

        BOOST_AUTO_TEST_CASE(TestGetInfo)
        {
                BOOST_TEST(car->getInfo() == car->getVehicleInfo());
        }

BOOST_AUTO_TEST_SUITE_END()