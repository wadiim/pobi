#include "repositories/VehicleRepository.h"
#include "model/Bicycle.h"

#include <boost/test/unit_test.hpp>

#define NUM_OF_VEHICLES 3

struct TestSuiteVehicleRepositoryFixture
{
        const std::string plateNumber[NUM_OF_VEHICLES] = { "13-954", "13-137", "26-037" };
        const unsigned int basePrice[NUM_OF_VEHICLES] = { 86, 207, 25 };
	VehiclePtr vehicle[NUM_OF_VEHICLES];
	VehicleRepository *vehicleRepo;

	TestSuiteVehicleRepositoryFixture()
	{
		for (size_t i = 0; i < NUM_OF_VEHICLES; ++i)
                {
                        vehicle[i] = std::make_shared<Bicycle>(plateNumber[i], basePrice[i]);
                }
		vehicleRepo = new VehicleRepository();
	}

	~TestSuiteVehicleRepositoryFixture()
	{
		delete vehicleRepo;
	}
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteVehicleRepository, TestSuiteVehicleRepositoryFixture)

	BOOST_AUTO_TEST_CASE(TestGetVehicleIfNoVehiclesThenReturnsNull)
	{
		BOOST_TEST(vehicleRepo->getVehicle(0) == nullptr);
	}

	BOOST_AUTO_TEST_CASE(TestSizeIfNoVehiclesThenReturns0)
	{
		BOOST_TEST(vehicleRepo->size() == 0);
	}

	BOOST_AUTO_TEST_CASE(TestAddVehicleIfNullThenNoVehicleIsAdded)
	{
		vehicleRepo->addVehicle(nullptr);
		BOOST_TEST(vehicleRepo->size() == 0);
	}

	BOOST_AUTO_TEST_CASE(TestAddVehicleIfNoVehiclesAddsTheNewOne)
	{
		vehicleRepo->addVehicle(vehicle[0]);
		BOOST_TEST(vehicleRepo->getVehicle(0) == vehicle[0]);
	}

	BOOST_AUTO_TEST_CASE(TestAddVehicleWithMultipleVehicles)
	{
		for (auto &v : vehicle) vehicleRepo->addVehicle(v);
		for (size_t i = 0; i < NUM_OF_VEHICLES; ++i) BOOST_TEST(vehicleRepo->getVehicle(i) == vehicle[i]);
	}

	BOOST_AUTO_TEST_CASE(TestGetVehicleIfIncorrectIndexThenReturnsNull)
	{
		vehicleRepo->addVehicle(vehicle[0]);
		BOOST_TEST(vehicleRepo->getVehicle(1) == nullptr);
	}

	BOOST_AUTO_TEST_CASE(TestSizeIfNonEmptyThenReturnsCorrectNumberOfVehicles)
	{
                for (auto &v : vehicle) vehicleRepo->addVehicle(v);
		BOOST_TEST(vehicleRepo->size() == NUM_OF_VEHICLES);
	}

	BOOST_AUTO_TEST_CASE(TestRemoveVehicleIfNullThenNoVehicleIsRemoved)
	{
		vehicleRepo->addVehicle(vehicle[0]);
		vehicleRepo->removeVehicle(nullptr);
		BOOST_TEST(vehicleRepo->getVehicle(0) == vehicle[0]);
	}

	BOOST_AUTO_TEST_CASE(TestRemoveVehicleIfCorrectVehicleThenTheNumberOfVehiclesIsDecremented)
	{
                for (auto &v : vehicle) vehicleRepo->addVehicle(v);
		vehicleRepo->removeVehicle(vehicle[1]);
		BOOST_TEST(vehicleRepo->size() == NUM_OF_VEHICLES - 1);
	}

	BOOST_AUTO_TEST_CASE(TestReportIfNoVehiclesThenReturnsEmptyString)
	{
		BOOST_TEST(vehicleRepo->report() == "");
	}

	BOOST_AUTO_TEST_CASE(TestReportIfMultipleVehicles)
	{
		vehicleRepo->addVehicle(vehicle[0]);
		vehicleRepo->addVehicle(vehicle[1]);
		BOOST_TEST(vehicleRepo->report() == vehicle[0]->getVehicleInfo() + " " + vehicle[1]->getVehicleInfo());
	}

	BOOST_AUTO_TEST_CASE(TestFindByIfSingleMatchThenReturnsOnlyOneVehicle)
	{
                for (auto &v : vehicle) vehicleRepo->addVehicle(v);
                const std::string pn = plateNumber[0];
		auto result = vehicleRepo->findBy([&pn](const VehiclePtr &v) {
                        return v->getPlateNumber() == pn;
                });
		BOOST_TEST(result.size() == 1);
	}

        BOOST_AUTO_TEST_CASE(TestFindByIfSingleMatchThenReturnsTheMatchingVehicle)
        {
                for (auto &v : vehicle) vehicleRepo->addVehicle(v);
                const std::string pn = plateNumber[0];
                auto result = vehicleRepo->findBy([&pn](const VehiclePtr &v) {
                        return v->getPlateNumber() == pn;
                });
                BOOST_TEST(result.back()->getPlateNumber() == pn);
        }

        BOOST_AUTO_TEST_CASE(TestFindByIfMultipleMatchesThenReturnsCorrectNumberOfVehicles)
        {
                for (auto &v : vehicle) vehicleRepo->addVehicle(v);
                BOOST_TEST(vehicleRepo->findBy([](const VehiclePtr &v) {
                        return v->getBasePrice() < 100;
                }).size() == 2);
        }

        BOOST_AUTO_TEST_CASE(TestFindByIfMultipleMatchesThenReturnsAllMatchingVehicles)
        {
                for (auto &v : vehicle) vehicleRepo->addVehicle(v);
                auto result = vehicleRepo->findBy([](const VehiclePtr &v) {
                        return v->getBasePrice() < 100;
                });
                for (auto &r : result) BOOST_TEST(r->getBasePrice() < 100);
        }

        BOOST_AUTO_TEST_CASE(TestFindAllIfMultipleVehiclesThenReturnsCorrectNumberOfVehicles)
        {
                for (auto &v : vehicle) vehicleRepo->addVehicle(v);
                BOOST_TEST(vehicleRepo->findAll().size() == NUM_OF_VEHICLES);
        }

        BOOST_AUTO_TEST_CASE(TestFindAllIfMultipleVehiclesThenReturnsAllVehicles)
        {
                for (auto &v : vehicle) vehicleRepo->addVehicle(v);
                auto result = vehicleRepo->findAll();
                for (size_t i = 0; i < result.size(); ++i) BOOST_TEST(result[i] == vehicle[i]);
        }

	BOOST_AUTO_TEST_CASE(TestFindByPlateNumberIfIncorrectIdThenReturnsNull)
	{
                for (auto &v : vehicle) vehicleRepo->addVehicle(v);
		BOOST_TEST(vehicleRepo->findByPlateNumber("###") == nullptr);
	}

	BOOST_AUTO_TEST_CASE(TestFindByPlateNumberIfCorrectIdThenReturnsVehicleWithThatPlateNumber)
	{
                for (auto &v : vehicle) vehicleRepo->addVehicle(v);
		BOOST_TEST(vehicleRepo->findByPlateNumber(plateNumber[1])->getPlateNumber() == plateNumber[1]);
	}

BOOST_AUTO_TEST_SUITE_END()
