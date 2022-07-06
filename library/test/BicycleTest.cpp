#include "typedefs.h"
#include "model/Bicycle.h"
#include "exceptions/VehicleException.h"

#include <boost/test/unit_test.hpp>

struct TestSuiteVehicleFixture
{
	const std::string plateNumber = "13-954";
	const unsigned int basePrice = 86;
	VehiclePtr bicycle;

	TestSuiteVehicleFixture()
        {
		bicycle = std::make_shared<Bicycle>(plateNumber, basePrice);
	}
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteVehicle, TestSuiteVehicleFixture)

	BOOST_AUTO_TEST_CASE(TestGetPlateNumber)
        {
		BOOST_TEST(bicycle->getPlateNumber() == plateNumber);
	}

        BOOST_AUTO_TEST_CASE(TestGetId)
        {
                BOOST_TEST(bicycle->getId() == bicycle->getPlateNumber());
        }

	BOOST_AUTO_TEST_CASE(TestGetBasePrice)
        {
		BOOST_TEST(bicycle->getBasePrice() == basePrice);
	}

	BOOST_AUTO_TEST_CASE(TestGetActualRentalPrice)
        {
		BOOST_TEST(bicycle->getActualRentalPrice() == bicycle->getBasePrice());
	}

	BOOST_AUTO_TEST_CASE(TestGetVehicleInfo)
        {
		BOOST_TEST(bicycle->getVehicleInfo() == plateNumber + " " + std::to_string(basePrice));
	}

        BOOST_AUTO_TEST_CASE(TestGetInfo)
        {
                BOOST_TEST(bicycle->getInfo() == bicycle->getVehicleInfo());
        }

	BOOST_AUTO_TEST_CASE(TestSetPlateNumberIfNonEmptyStringThenUpdatesThePlateNumber)
        {
		const std::string pNum = "37-564";
		bicycle->setPlateNumber(pNum);
		BOOST_TEST(bicycle->getPlateNumber() == pNum);
	}

	BOOST_AUTO_TEST_CASE(TestSetPlateNumberIfEmptyStringThenThrowsVehicleException)
        {
                BOOST_CHECK_THROW(bicycle->setPlateNumber(""), VehicleException);
	}

	BOOST_AUTO_TEST_CASE(TestSetBasePrice)
        {
		const unsigned int bPrice = 22;
		bicycle->setBasePrice(bPrice);
		BOOST_TEST(bicycle->getBasePrice() == bPrice);
	}

	BOOST_AUTO_TEST_CASE(TestIsArchivedIfInitialStateThenReturnsFalse)
        {
		BOOST_TEST(bicycle->isArchived() == false);
	}

	BOOST_AUTO_TEST_CASE(TestSetArchived)
        {
		bicycle->setArchive(true);
		BOOST_TEST(bicycle->isArchived() == true);
	}

BOOST_AUTO_TEST_SUITE_END()
