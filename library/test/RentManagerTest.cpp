#include "managers/RentManager.h"
#include "model/Address.h"
#include "model/Bicycle.h"
#include "model/Car.h"
#include "model/Client.h"
#include "model/Moped.h"
#include "model/Rent.h"

#include <boost/test/unit_test.hpp>

namespace pt = boost::posix_time;
namespace tt = boost::test_tools;

#define NUM_OF_CLIENTS 3

struct TestSuiteRentManagerFixture
{
        pt::ptime time = pt::second_clock::local_time();
        AddressPtr address[NUM_OF_CLIENTS];
        ClientPtr client[NUM_OF_CLIENTS];
        VehiclePtr vehicle[NUM_OF_CLIENTS];
        RentManager *rentManager;

        TestSuiteRentManagerFixture()
        {
                address[0] = std::make_shared<Address>("Tokyo", "Mimorigasaka", "2");
                address[1] = std::make_shared<Address>("Kyoto", "Kiyamachi", "16");
                address[2] = address[0];

                client[0] = std::make_shared<Client>("Lain", "Iwakura", "1094795585", address[0]);
                client[1] = std::make_shared<Client>("Mika", "Iwakura", "3200171710", address[1]);
                client[2] = std::make_shared<Client>("Reika", "Yamamoto", "2105376125", address[2]);

                vehicle[0] = std::make_shared<Car>("13-954", 86, 1587, SegmentType::A);
                vehicle[1] = std::make_shared<Moped>("13-137", 207, 1308);
                vehicle[2] = std::make_shared<Bicycle>("26-037", 25);

                rentManager = new RentManager();
        }

        ~TestSuiteRentManagerFixture()
        {
                delete rentManager;
        }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRentManager, TestSuiteRentManagerFixture)

        BOOST_AUTO_TEST_CASE(TestRentVehicleIfClientArchivedThenReturnsNull)
        {
                client[0]->setArchive(true);
                BOOST_TEST(rentManager->rentVehicle(client[0], vehicle[0], time) == nullptr);
        }

        BOOST_AUTO_TEST_CASE(TestRentVehicleIfVehicleArchivedThenReturnsNull)
        {
                vehicle[0]->setArchive(true);
                BOOST_TEST(rentManager->rentVehicle(client[0], vehicle[0], time) == nullptr);
        }

        BOOST_AUTO_TEST_CASE(TestRentVehicleIfRentingPossibleThenReturnsNonNull)
        {
                auto rent = rentManager->rentVehicle(client[0], vehicle[0], time);
                BOOST_TEST_REQUIRE(rent != nullptr);
        }

        BOOST_AUTO_TEST_CASE(TestRentVehicleIfRentingPossibleThenStoresTheClient)
        {
                auto rent = rentManager->rentVehicle(client[0], vehicle[0], time);
                BOOST_TEST(rent->getClient() == client[0]);
        }

        BOOST_AUTO_TEST_CASE(TestRentVehicleIfRentingPossibleThenStoresTheVehicle)
        {
                auto rent = rentManager->rentVehicle(client[0], vehicle[0], time);
                BOOST_TEST(rent->getVehicle() == vehicle[0]);
        }

        BOOST_AUTO_TEST_CASE(TestRentVehicleIfMultipleRentsOfDifferentVehiclesThenNonOfThemIsNull)
        {
                std::shared_ptr<Rent> rents[NUM_OF_CLIENTS];
                for (size_t i = 0; i < NUM_OF_CLIENTS; ++i)
                {
                        rents[i] = rentManager->rentVehicle(client[i], vehicle[i], time + pt::hours(i));
                }
                for (auto &r : rents) BOOST_TEST(r != nullptr);
        }

        BOOST_AUTO_TEST_CASE(TestGetAllClientRentsIfNoRentThenReturnsNoClients)
        {
                BOOST_TEST(rentManager->getAllClientRents(client[0]).empty());
        }

        BOOST_AUTO_TEST_CASE(TestGetAllClientRentsIfSingleRentThenReturnsSingleRent)
        {
                auto rent = rentManager->rentVehicle(client[0], vehicle[0], time);
                auto result = rentManager->getAllClientRents(client[0]);
                BOOST_TEST_REQUIRE(result.size() == 1);
        }

        BOOST_AUTO_TEST_CASE(TestGetAllClientRentsIfSingleRentThenReturnsCorrectRent)
        {
                auto rent = rentManager->rentVehicle(client[0], vehicle[0], time);
                auto result = rentManager->getAllClientRents(client[0]);
                BOOST_TEST(result.back() == rent);
        }

        BOOST_AUTO_TEST_CASE(TestGetAllClientRentIfSingleRentOfTheSpecifiedClientButMultipleClientsThenReturnsSingleRent)
        {
                std::shared_ptr<Rent> rent[NUM_OF_CLIENTS];
                for (size_t i = 0; i < NUM_OF_CLIENTS; ++i)
                {
                        rent[i] = rentManager->rentVehicle(client[i], vehicle[i], time + pt::hours(i));
                }
                auto result = rentManager->getAllClientRents(client[1]);
                BOOST_TEST_REQUIRE(result.size() == 1);
        }

        BOOST_AUTO_TEST_CASE(TestGetAllClientRentIfSingleRentOfTheSpecifiedClientButMultipleClientsThenReturnsCorrectRent)
        {
                std::shared_ptr<Rent> rent[NUM_OF_CLIENTS];
                for (size_t i = 0; i < NUM_OF_CLIENTS; ++i)
                {
                        rent[i] = rentManager->rentVehicle(client[i], vehicle[i], time + pt::hours(i));
                }
                auto result = rentManager->getAllClientRents(client[1]);
                BOOST_TEST(result.back() == rent[1]);
        }

        BOOST_AUTO_TEST_CASE(TestGetAllClientRentsIfMultipleRentsThenReturnsAllOfThem)
        {
                client[0]->setClientType(std::make_shared<Diamond>());
                std::vector<RentPtr> rents;
                for (size_t i = 0; i < NUM_OF_CLIENTS; ++i)
                {
                        rents.push_back(rentManager->rentVehicle(client[0], vehicle[i], time + pt::hours(i)));
                }
                std::sort(rents.begin(), rents.end());
                auto result = rentManager->getAllClientRents(client[0]);
                std::sort(result.begin(), result.end());
                BOOST_TEST(rents == result);
        }

        BOOST_AUTO_TEST_CASE(TestRentVehicleIfTooManyRentsThenReturnsNull)
        {
                rentManager->rentVehicle(client[0], vehicle[0], time);
                auto rent = rentManager->rentVehicle(client[0], vehicle[1], time);
                BOOST_TEST(rent == nullptr);
        }

        BOOST_AUTO_TEST_CASE(TestGetVehicleRentIfNoRentsThenReturnsNull)
        {
                BOOST_TEST(rentManager->getVehicleRent(vehicle[0]) == nullptr);
        }

        BOOST_AUTO_TEST_CASE(TestGetVehicleRentIfSingleRentThenReturnsTheRent)
        {
                auto rent = rentManager->rentVehicle(client[0], vehicle[0], time);
                BOOST_TEST(rentManager->getVehicleRent(vehicle[0]) == rent);
        }

        BOOST_AUTO_TEST_CASE(TestGetVehicleRentIfNoMatchingRentThenReturnsNull)
        {
                rentManager->rentVehicle(client[0], vehicle[0], time);
                BOOST_TEST(rentManager->getVehicleRent(vehicle[1]) == nullptr);
        }

        BOOST_AUTO_TEST_CASE(TestRentVehicleIfVehicleAlreadyRentedThenReturnsNull)
        {
                rentManager->rentVehicle(client[0], vehicle[0], time);
                auto rent = rentManager->rentVehicle(client[1], vehicle[0], time + pt::hours(2));
                BOOST_TEST(rent == nullptr);
        }

        BOOST_AUTO_TEST_CASE(TestFindRentsIfNoRentsThenReturnsNoRents)
        {
                BOOST_TEST(rentManager->findRents([](const RentPtr &r) { return true; }).size() == 0);
        }

        BOOST_AUTO_TEST_CASE(TestFindRentsIfMatchingRentsReturnsCorrectNumberOfRents)
        {
                for (size_t i = 0; i < NUM_OF_CLIENTS; ++i)
                {
                        rentManager->rentVehicle(client[i], vehicle[i], time + pt::hours(i));
                }
                const std::string ln = client[0]->getLastName();
                auto rents = rentManager->findRents([&ln](const RentPtr &r) {
                        return r->getClient()->getLastName() == ln;
                });
                BOOST_TEST(rents.size() == 2);
        }

        BOOST_AUTO_TEST_CASE(TestFindRentsIfMatchingRentsReturnsCorrectRents)
        {
                for (size_t i = 0; i < NUM_OF_CLIENTS; ++i)
                {
                        rentManager->rentVehicle(client[i], vehicle[i], time + pt::hours(i));
                }
                const std::string ln = client[0]->getLastName();
                auto rents = rentManager->findRents([&ln](const RentPtr &r) {
                        return r->getClient()->getLastName() == ln;
                });
                for (auto &r : rents) BOOST_TEST(r->getClient()->getLastName() == ln);
        }

        BOOST_AUTO_TEST_CASE(TestFindAllRentsIfMultipleRentsThenReturnsAllOfThem)
        {
                std::vector<RentPtr> rents;
                for (size_t i = 0; i < NUM_OF_CLIENTS; ++i)
                {
                        rents.push_back(rentManager->rentVehicle(client[i], vehicle[i], time + pt::hours(i)));
                }
                std::sort(rents.begin(), rents.end());
                auto result = rentManager->findAllRents();
                std::sort(result.begin(), result.end());
                BOOST_TEST(rents == result);
        }

        BOOST_AUTO_TEST_CASE(TestReturnVehicleIfCorrectVehicleThenArchiveTheVehicle)
        {
                client[0]->setClientType(std::make_shared<Diamond>());
                std::shared_ptr<Rent> rent[NUM_OF_CLIENTS];
                for (size_t i = 0; i < NUM_OF_CLIENTS; ++i)
                {
                        rent[i] = rentManager->rentVehicle(client[0], vehicle[i], time + pt::hours(i));
                }
                rentManager->returnVehicle(vehicle[1]);
                BOOST_TEST(vehicle[1]->isArchived() == true);
        }

        BOOST_AUTO_TEST_CASE(TestReturnVehicleIfCorrectVehicleThenUpdatesTheEndTime)
        {
                client[0]->setClientType(std::make_shared<Diamond>());
                std::shared_ptr<Rent> rent[NUM_OF_CLIENTS];
                for (size_t i = 0; i < NUM_OF_CLIENTS; ++i)
                {
                        rent[i] = rentManager->rentVehicle(client[0], vehicle[i], time + pt::hours(i));
                }
                rentManager->returnVehicle(vehicle[1]);
                BOOST_TEST(rent[1]->getEndTime() != pt::not_a_date_time);
        }

        BOOST_AUTO_TEST_CASE(TestReturnVehicleIfCorrectVehicleThenFunctionGetVehicleRentReturnsNull)
        {
                client[0]->setClientType(std::make_shared<Diamond>());
                std::shared_ptr<Rent> rent[NUM_OF_CLIENTS];
                for (size_t i = 0; i < NUM_OF_CLIENTS; ++i)
                {
                        rent[i] = rentManager->rentVehicle(client[0], vehicle[i], time + pt::hours(i));
                }
                rentManager->returnVehicle(vehicle[1]);
                BOOST_TEST(rentManager->getVehicleRent(vehicle[1]) == nullptr);
        }

        BOOST_AUTO_TEST_CASE(TestCheckClientRentBalanceIfNoRentsYetThenReturns0)
        {
                BOOST_TEST(rentManager->checkClientRentBalance(client[0]) == 0.0, tt::tolerance(0.01));
        }

        BOOST_AUTO_TEST_CASE(TestCheckClientRentBalanceIfNoneOfTheRentsIsArchivedThenReturns0)
        {
                rentManager->rentVehicle(client[0], vehicle[0], time);
                BOOST_TEST(rentManager->checkClientRentBalance(client[0]) == 0.0, tt::tolerance(0.01));
        }

        BOOST_AUTO_TEST_CASE(TestCheckClientRentBalanceIfSomeRentsAreArchivedReturnsTheCostOfOnlyTheArchivedOnes)
        {
                client[0]->setClientType(std::make_shared<Diamond>());
                std::shared_ptr<Rent> rent[NUM_OF_CLIENTS];
                for (size_t i = 0; i < NUM_OF_CLIENTS; ++i)
                {
                        rent[i] = rentManager->rentVehicle(client[0], vehicle[i], time - pt::hours(NUM_OF_CLIENTS - i));
                }
                rentManager->returnVehicle(vehicle[0]);
                rentManager->returnVehicle(vehicle[2]);
                BOOST_TEST(rentManager->checkClientRentBalance(client[0]) == rent[0]->getRentCost() + rent[2]->getRentCost());
        }

        BOOST_AUTO_TEST_CASE(TestChangeClientTypeIfBalanceLessThan100)
        {
                auto tmpVehicle = std::make_shared<Bicycle>("DEFAULT", 50);
                rentManager->rentVehicle(client[0], tmpVehicle, time - pt::hours(1));
                rentManager->returnVehicle(tmpVehicle);
                rentManager->changeClientType(client[0]);
                BOOST_TEST(client[0]->getMaxVehicles() == Default().getMaxVehicles());
        }

        BOOST_AUTO_TEST_CASE(TestChangeClientTypeIfBalanceBetween100And200)
        {
                auto tmpVehicle = std::make_shared<Bicycle>("BRONZE", 150);
                rentManager->rentVehicle(client[0], tmpVehicle, time - pt::hours(1));
                rentManager->returnVehicle(tmpVehicle);
                rentManager->changeClientType(client[0]);
                BOOST_TEST(client[0]->getMaxVehicles() == Bronze().getMaxVehicles());
        }

        BOOST_AUTO_TEST_CASE(TestChangeClientTypeIfBalanceBetween200And400)
        {
                auto tmpVehicle = std::make_shared<Bicycle>("SILVER", 275);
                rentManager->rentVehicle(client[0], tmpVehicle, time - pt::hours(1));
                rentManager->returnVehicle(tmpVehicle);
                rentManager->changeClientType(client[0]);
                BOOST_TEST(client[0]->getMaxVehicles() == Silver().getMaxVehicles());
        }

        BOOST_AUTO_TEST_CASE(TestChangeClientTypeIfBalanceBetween400And800)
        {
                auto tmpVehicle = std::make_shared<Bicycle>("GOLD", 500);
                rentManager->rentVehicle(client[0], tmpVehicle, time - pt::hours(1));
                rentManager->returnVehicle(tmpVehicle);
                rentManager->changeClientType(client[0]);
                BOOST_TEST(client[0]->getMaxVehicles() == Gold().getMaxVehicles());
        }

        BOOST_AUTO_TEST_CASE(TestChangeClientTypeIfBalanceBetween800And1600)
        {
                auto tmpVehicle = std::make_shared<Bicycle>("PLATINUM", 1000);
                rentManager->rentVehicle(client[0], tmpVehicle, time - pt::hours(1));
                rentManager->returnVehicle(tmpVehicle);
                rentManager->changeClientType(client[0]);
                BOOST_TEST(client[0]->getMaxVehicles() == Platinum().getMaxVehicles());
        }

        BOOST_AUTO_TEST_CASE(TestChangeClientTypeIfBalanceGreaterThan1600)
        {
                auto tmpVehicle = std::make_shared<Bicycle>("DIAMOND", 3000);
                rentManager->rentVehicle(client[0], tmpVehicle, time - pt::hours(1));
                rentManager->returnVehicle(tmpVehicle);
                rentManager->changeClientType(client[0]);
                BOOST_TEST(client[0]->getMaxVehicles() == Diamond().getMaxVehicles());
        }

        BOOST_AUTO_TEST_CASE(TestReturnVehicleIfBalanceBigEnoughThenChangesClientType)
        {
                auto tmpVehicle = std::make_shared<Bicycle>("SILVER", 275);
                rentManager->rentVehicle(client[0], tmpVehicle, time - pt::hours(1));
                rentManager->returnVehicle(tmpVehicle);
                BOOST_TEST(client[0]->getMaxVehicles() == Silver().getMaxVehicles());
        }

BOOST_AUTO_TEST_SUITE_END()