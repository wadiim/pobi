#include "repositories/RentRepository.h"
#include "model/Car.h"
#include "model/Rent.h"
#include "model/Moped.h"
#include "model/Client.h"
#include "model/Bicycle.h"
#include "model/Address.h"

#include <boost/test/unit_test.hpp>

namespace pt = boost::posix_time;

#define NUM_OF_RENTS 3

struct TestSuiteRentRepositoryFixture
{
        pt::ptime time = pt::second_clock::local_time();
	RentPtr rent[NUM_OF_RENTS];
	ClientPtr client[NUM_OF_RENTS];
	VehiclePtr vehicle[NUM_OF_RENTS];
	AddressPtr address[NUM_OF_RENTS];
	RentRepository *rentRepo;

	TestSuiteRentRepositoryFixture()
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

                for (size_t i = 0; i < NUM_OF_RENTS; ++i)
                {
                        rent[i] = std::make_shared<Rent>(client[i], vehicle[i], time + pt::hours(i));
                }

		rentRepo = new RentRepository();
	}

	~TestSuiteRentRepositoryFixture()
	{
		delete rentRepo;
	}
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRentRepository, TestSuiteRentRepositoryFixture)

	BOOST_AUTO_TEST_CASE(TestGetRentIfNoRentsThenReturnsNull)
	{
		BOOST_TEST(rentRepo->getRent(0) == nullptr);
	}

	BOOST_AUTO_TEST_CASE(TestSizeIfNoRentsThenReturns0)
	{
		BOOST_TEST(rentRepo->size() == 0);
	}

	BOOST_AUTO_TEST_CASE(TestAddRentIfNullThenAddsNoRent)
	{
		rentRepo->addRent(nullptr);
		BOOST_TEST(rentRepo->size() == 0);
	}

	BOOST_AUTO_TEST_CASE(TestAddRentIfNoRentsThenAddsNewRent)
	{
		rentRepo->addRent(rent[0]);
		BOOST_TEST(rentRepo->getRent(0) == rent[0]);
	}

	BOOST_AUTO_TEST_CASE(TestAddRentIfMultipleRentsThenAddsAllOfThem)
	{
                for (auto &r : rent) rentRepo->addRent(r);
                for (size_t i = 0; i < NUM_OF_RENTS; ++i) BOOST_TEST(rentRepo->getRent(i) == rent[i]);
	}

	BOOST_AUTO_TEST_CASE(TestGetRentIfIncorrectIndexThenReturnsNull)
	{
		rentRepo->addRent(rent[0]);
		BOOST_TEST(rentRepo->getRent(1) == nullptr);
	}

	BOOST_AUTO_TEST_CASE(TestSizeIfNonEmptyThenReturnsNumberOfRents)
	{
                for (auto &r : rent) rentRepo->addRent(r);
		BOOST_TEST(rentRepo->size() == NUM_OF_RENTS);
	}

	BOOST_AUTO_TEST_CASE(TestRemoveRentIfNullThenNoRentIsRemoved)
	{
		rentRepo->addRent(rent[0]);
		rentRepo->removeRent(nullptr);
		BOOST_TEST(rentRepo->getRent(0) == rent[0]);
	}

	BOOST_AUTO_TEST_CASE(TestRemoveRentIfCorrectRentThenDecreasesTheNumberOfRents)
	{
                for (auto &r : rent) rentRepo->addRent(r);
		rentRepo->removeRent(rent[1]);
		BOOST_TEST(rentRepo->size() == NUM_OF_RENTS - 1);
	}

	BOOST_AUTO_TEST_CASE(TestReportIfNoRentsThenReturnsEmptyString)
	{
		BOOST_TEST(rentRepo->report() == "");
	}

	BOOST_AUTO_TEST_CASE(TestReportIfMultipleRents)
	{
		rentRepo->addRent(rent[0]);
		rentRepo->addRent(rent[1]);
		BOOST_TEST(rentRepo->report() == rent[0]->getRentInfo() + " " + rent[1]->getRentInfo());
	}

	BOOST_AUTO_TEST_CASE(TestFindByIfSingleMatchThenReturnsOnlyOneRent)
	{
                for (auto &r : rent) rentRepo->addRent(r);
                const std::string fn = client[0]->getFirstName();
		std::vector<RentPtr> result = rentRepo->findBy([&fn](const RentPtr &r) {
                        return r->getClient()->getFirstName() == fn;
                });
		BOOST_TEST(result.size() == 1);
	}

        BOOST_AUTO_TEST_CASE(TestFindByIfSingleMatchThenReturnsTheMatchingRent)
        {
                for (auto &r : rent) rentRepo->addRent(r);
                const std::string fn = client[0]->getFirstName();
                std::vector<RentPtr> result = rentRepo->findBy([&fn](const RentPtr &r) {
                        return r->getClient()->getFirstName() == fn;
                });
                BOOST_TEST(result.back()->getClient()->getFirstName() == fn);
        }

	BOOST_AUTO_TEST_CASE(TestFindByIfMultipleMatchesThenReturnsCorrectNumberOfRents)
	{
                for (auto &r : rent) rentRepo->addRent(r);
                const std::string ln = client[0]->getLastName();
                std::vector<RentPtr> result = rentRepo->findBy([&ln](const RentPtr &r) {
                        return r->getClient()->getLastName() == ln;
                });
		BOOST_TEST(result.size() == 2);
	}

	BOOST_AUTO_TEST_CASE(TestFindByIfMultipleMatchesThenReturnsAllMatchingRents)
	{
                for (auto &r : rent) rentRepo->addRent(r);
                const std::string ln = client[0]->getLastName();
                std::vector<RentPtr> result = rentRepo->findBy([&ln](const RentPtr &r) {
                        return r->getClient()->getLastName() == ln;
                });
		for (auto &r : result) BOOST_TEST(r->getClient()->getLastName() == ln);
	}

	BOOST_AUTO_TEST_CASE(TestFindAllIfMultipleRentsThenReturnsCorrectNumberOfRents)
	{
                for (auto &r : rent) rentRepo->addRent(r);
		BOOST_TEST(rentRepo->findAll().size() == rentRepo->size());
	}

	BOOST_AUTO_TEST_CASE(TestFindAllIfMultipleRentsThenReturnsAllRents)
	{
                for (auto &r : rent) rentRepo->addRent(r);
		std::vector<RentPtr> result = rentRepo->findAll();
		for (size_t i = 0; i < NUM_OF_RENTS; ++i) BOOST_TEST(result[i] == rentRepo->getRent(i));
	}

BOOST_AUTO_TEST_SUITE_END()
