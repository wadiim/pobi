#include "managers/VehicleManager.h"
#include "model/Bicycle.h"
#include "model/Car.h"

#include <boost/test/unit_test.hpp>

#define NUM_OF_VEHICLES 3

struct TestSuiteVehicleManagerFixture
{
        const std::string plateNumber[NUM_OF_VEHICLES] = { "13-954", "13-137", "26-037" };
        const unsigned int basePrice[NUM_OF_VEHICLES] = { 86, 207, 25 };
        const unsigned int engineDisplacement[NUM_OF_VEHICLES] = { 1587, 1308, 0 };
	VehicleManager *vehicleManager;

	TestSuiteVehicleManagerFixture()
	{
		vehicleManager = new VehicleManager();
	}

	~TestSuiteVehicleManagerFixture()
	{
		delete vehicleManager;
	}

        void registerVehicles()
        {
                vehicleManager->registerCar(plateNumber[0], basePrice[0], engineDisplacement[0], SegmentType::A);
                vehicleManager->registerMoped(plateNumber[1], basePrice[1], engineDisplacement[1]);
                vehicleManager->registerBicycle(plateNumber[2], basePrice[2]);
        }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteVehicleManager, TestSuiteVehicleManagerFixture)

	BOOST_AUTO_TEST_CASE(TestGetVehicleIfNoVehiclesThenReturnsNull)
	{
		BOOST_TEST(vehicleManager->getVehicle("0") == nullptr);
	}

	BOOST_AUTO_TEST_CASE(TestRegisterBicycleIfCorrectPlateNumberThenReturnsNonNull)
	{
		BOOST_TEST(vehicleManager->registerBicycle(plateNumber[2], basePrice[2]) != nullptr);
	}

        BOOST_AUTO_TEST_CASE(TestRegisterBicycleIfCorrectPlateNumberThenSetsThePlateNumberCorrectly)
        {
                BOOST_TEST(vehicleManager->registerBicycle(plateNumber[2], basePrice[2])->getPlateNumber() == plateNumber[2]);
        }

        BOOST_AUTO_TEST_CASE(TestRegisterBicycleIfCorrectPlateNumberThenSetsTheBasePriceCorrectly)
        {
                BOOST_TEST(vehicleManager->registerBicycle(plateNumber[2], basePrice[2])->getBasePrice() == basePrice[2]);
        }

	BOOST_AUTO_TEST_CASE(TestRegisterMopedIfCorrectPlateNumberReturnsNonNull)
	{
		BOOST_TEST(vehicleManager->registerMoped(plateNumber[1], basePrice[1], engineDisplacement[1]) != nullptr);
	}

        BOOST_AUTO_TEST_CASE(TestRegisterMopedIfCorrectPlateNumberThenSetsThePlateNumberCorrectly)
        {
                BOOST_TEST(vehicleManager->registerMoped(plateNumber[1], basePrice[1], engineDisplacement[1])->getPlateNumber() == plateNumber[1]);
        }

        BOOST_AUTO_TEST_CASE(TestRegisterMopedIfCorrectPlateNumberThenSetsTheBasePriceCorrectly)
        {
                BOOST_TEST(vehicleManager->registerMoped(plateNumber[1], basePrice[1], engineDisplacement[1])->getBasePrice() == basePrice[1]);
        }

	BOOST_AUTO_TEST_CASE(TestRegisterCarIfCorrectPlateNumberThenReturnsNonNull)
	{
		BOOST_TEST(vehicleManager->registerCar(plateNumber[0], basePrice[0], engineDisplacement[0], SegmentType::E) != nullptr);
	}

        BOOST_AUTO_TEST_CASE(TestRegisterCarIfCorrectPlateNumberThenSetsThePlateNumberCorrectly)
        {
                BOOST_TEST(vehicleManager->registerCar(plateNumber[0], basePrice[0], engineDisplacement[0], SegmentType::E)->getPlateNumber() == plateNumber[0]);
        }

        BOOST_AUTO_TEST_CASE(TestRegisterCarIfCorrectPlateNumberThenSetsTheBasePriceCorrectly)
        {
                BOOST_TEST(vehicleManager->registerCar(plateNumber[0], basePrice[0], engineDisplacement[0], SegmentType::E)->getBasePrice() == basePrice[0]);
        }

	BOOST_AUTO_TEST_CASE(TestRegisterVehicleIfDuplicatedPlateNumberThenReturnsTheAlreadyRegisteredVehicle)
	{
		auto v1 = vehicleManager->registerBicycle(plateNumber[2], basePrice[2]);
		auto v2 = vehicleManager->registerMoped(plateNumber[2], basePrice[1], engineDisplacement[1]);
		BOOST_TEST(v1 == v2);
	}

	BOOST_AUTO_TEST_CASE(TestGetVehicleIfIncorrectPlateNumberThenReturnsNull)
	{
		vehicleManager->registerBicycle(plateNumber[2], basePrice[2]);
		BOOST_TEST(vehicleManager->getVehicle("-1") == nullptr);
	}

	BOOST_AUTO_TEST_CASE(TestGetVehicleIfCorrectPlateNumberThenReturnsTheMatchingVehicle)
	{
		const auto v = vehicleManager->registerBicycle(plateNumber[2], basePrice[2]);
		BOOST_TEST(vehicleManager->getVehicle(plateNumber[2]) == v);
	}

	BOOST_AUTO_TEST_CASE(TestUnregisterVehicleIfCorrectPlateNumberThenArchivesTheSelectedVehicle)
	{
		vehicleManager->registerBicycle(plateNumber[2], basePrice[2]);
		vehicleManager->unregisterVehicle(plateNumber[2]);
		BOOST_TEST(vehicleManager->getVehicle(plateNumber[2])->isArchived() == true);
	}

        BOOST_AUTO_TEST_CASE(TestFindVehiclesIfNoVehicleMeetsTheCriteriaThenReturnsNoVehicles)
        {
                registerVehicles();
                BOOST_TEST(vehicleManager->findVehicles([](const VehiclePtr &v) {
                        return false;
                }).empty() == true);
        }

        BOOST_AUTO_TEST_CASE(TestFindVehiclesIfAllVehiclesHaveBeenUnregisteredThenReturnsNoVehicles)
        {
                registerVehicles();
                for (const auto & pn : plateNumber) vehicleManager->unregisterVehicle(pn);
                BOOST_TEST(vehicleManager->findVehicles([](const VehiclePtr &v) {
                        return true;
                }).empty() == true);
        }

        BOOST_AUTO_TEST_CASE(TestFindVehiclesIfSingleVehicleMeetsTheCriteriaThenReturnsSingleVehicle)
        {
                registerVehicles();
                const auto pn = plateNumber[0];
                BOOST_TEST(vehicleManager->findVehicles([&pn](const VehiclePtr &v) {
                        return v->getPlateNumber() == pn;
                }).size() == 1);
        }

        BOOST_AUTO_TEST_CASE(TestFindVehiclesIfSingleVehicleMeetsTheCriteriaThenReturnsCorrectVehicle)
        {
                registerVehicles();
                const auto pn = plateNumber[0];
                BOOST_TEST(vehicleManager->findVehicles([&pn](const VehiclePtr &v) {
                        return v->getPlateNumber() == pn;
                }).back()->getPlateNumber() == pn);
        }

        BOOST_AUTO_TEST_CASE(TestFindVehiclesIfMultipleVehiclesMeetTheCriteriaThenReturnsCorrectNumberOfVehicles)
        {
                registerVehicles();
                BOOST_TEST(vehicleManager->findVehicles([](const VehiclePtr &v) {
                        return v->getBasePrice() < 100;
                }).size() == 2);
        }

        BOOST_AUTO_TEST_CASE(TestFindVehiclesIfMultipleVehiclesMeetTheCriteriaThenReturnsCorrectVehicles)
        {
                registerVehicles();
                auto result = vehicleManager->findVehicles([](const VehiclePtr &v) {
                        return v->getBasePrice() < 100;
                });
                for (auto &r : result) BOOST_TEST(r->getBasePrice() < 100);
        }

        BOOST_AUTO_TEST_CASE(TestFindVehiclesIfOneOfTheMatchingVehiclesHasBeenUnregisteredThenReturnsOneVehicleLess)
        {
                registerVehicles();
                vehicleManager->unregisterVehicle(plateNumber[1]);
                BOOST_TEST(vehicleManager->findVehicles([](const VehiclePtr &v) {
                        return true;
                }).size() == NUM_OF_VEHICLES - 1);
        }

        BOOST_AUTO_TEST_CASE(TestFindVehiclesIfOneOfTheMatchingVehiclesHasBeenUnregisteredThenThatVehicleIsNotReturned)
        {
                registerVehicles();
                vehicleManager->unregisterVehicle(plateNumber[NUM_OF_VEHICLES - 1]);
                auto result = vehicleManager->findVehicles([](const VehiclePtr &v) {
                        return true;
                });
                for (size_t i = 0; i < result.size(); ++i)
                {
                        BOOST_TEST(result[i]->getPlateNumber() == plateNumber[i]);
                }
        }

        BOOST_AUTO_TEST_CASE(TestFindAllVehiclesIfNoVehiclesThenReturnsNoVehicles)
        {
                BOOST_TEST(vehicleManager->findAllVehicles().empty() == true);
        }

        BOOST_AUTO_TEST_CASE(TestFindAllVehiclesIfAllOfTheVehiclesHaveBeenUnregisteredThenReturnsNoVehicles)
        {
                registerVehicles();
                for (auto &pn : plateNumber) vehicleManager->unregisterVehicle(pn);
                BOOST_TEST(vehicleManager->findAllVehicles().empty() == true);
        }

        BOOST_AUTO_TEST_CASE(TestFindAllVehiclesIfMultipleVehiclesThenReturnsCorrectNumberOfVehicles)
        {
                registerVehicles();
                BOOST_TEST(vehicleManager->findAllVehicles().size() == NUM_OF_VEHICLES);
        }

        BOOST_AUTO_TEST_CASE(TestFindAllvehiclesIfMultipleVehiclesThenReturnsAllVehicles)
        {
                registerVehicles();
                auto result = vehicleManager->findAllVehicles();
                for (size_t i = 0; i < result.size(); ++i)
                {
                        BOOST_TEST(result[i]->getPlateNumber() == plateNumber[i]);
                }
        }

        BOOST_AUTO_TEST_CASE(TestFindAllVehiclesIfOneOfTheVehiclesHasBeenUnregisteredThenReturnsOneVehicleLess)
        {
                registerVehicles();
                vehicleManager->unregisterVehicle(plateNumber[NUM_OF_VEHICLES - 1]);
                BOOST_TEST(vehicleManager->findAllVehicles().size() == NUM_OF_VEHICLES - 1);
        }

        BOOST_AUTO_TEST_CASE(TestFindAllVehiclesIfOneOfTheVehiclesHasBeenUnregisteredThenThatVehicleIsNotReturned)
        {
                registerVehicles();
                vehicleManager->unregisterVehicle(plateNumber[NUM_OF_VEHICLES - 1]);
                auto result = vehicleManager->findAllVehicles();
                for (size_t i = 0; i < result.size(); ++i)
                {
                        BOOST_TEST(result[i]->getPlateNumber() == plateNumber[i]);
                }
        }

BOOST_AUTO_TEST_SUITE_END()
