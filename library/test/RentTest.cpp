#include "typedefs.h"
#include "model/Rent.h"
#include "model/Address.h"
#include "model/Client.h"
#include "model/Bicycle.h"
#include "exceptions/RentException.h"

#include <boost/test/unit_test.hpp>

namespace pt = boost::posix_time;

struct TestSuiteRentFixture
{
	RentPtr rent;
	ClientPtr client;
	VehiclePtr vehicle;
        AddressPtr address;
	const unsigned int pricePerDay = 25;
	pt::ptime bTime = pt::second_clock::local_time();

	TestSuiteRentFixture()
        {
                address = std::make_shared<Address>("Tokyo", "Mimorigasaka", "2");
		client = std::make_shared<Client>("Lain", "Iwakura", "22",address);
		vehicle = std::make_shared<Bicycle>("26-037", pricePerDay);
		rent = std::make_shared<Rent>(client, vehicle, bTime);
	}
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRent, TestSuiteRentFixture)

	BOOST_AUTO_TEST_CASE(TestGetId)
        {
		BOOST_TEST(rent->getId() != "");
	}

	BOOST_AUTO_TEST_CASE(TestGetClient)
        {
		const auto c = client;
		BOOST_TEST(rent->getClient() == c);
	}

	BOOST_AUTO_TEST_CASE(TestGetVehicle)
        {
		BOOST_TEST(rent->getVehicle() == vehicle);
	}

	BOOST_AUTO_TEST_CASE(TestGetRentInfoIfNotEnded)
        {
		std::stringstream ss;
		ss << bTime;
		BOOST_TEST(rent->getRentInfo() == rent->getId() + " "
				+ client->getClientInfo() + " "
				+ vehicle->getVehicleInfo() + " "
				+ ss.str());
	}

	BOOST_AUTO_TEST_CASE(TestGetRentInfoIfEnded)
        {
		pt::ptime eTime = bTime + pt::hours(22);
		std::stringstream ss;
		ss << bTime << " " << eTime;
		rent->endRent(eTime);
		BOOST_TEST(rent->getRentInfo() == rent->getId() + " "
				+ client->getClientInfo() + " "
				+ vehicle->getVehicleInfo() + " "
				+ ss.str());
	}

        BOOST_AUTO_TEST_CASE(TestGetInfo)
        {
                BOOST_TEST(rent->getInfo() == rent->getRentInfo());
        }

	BOOST_AUTO_TEST_CASE(TestGetBeginTimeIfNotADateTime)
        {
		pt::ptime now = pt::second_clock::local_time();
		pt::time_period skew = pt::time_period(rent->getBeginTime(), now);
		BOOST_TEST((skew.length().hours() == 0 && skew.length().minutes() == 0));
	}

	BOOST_AUTO_TEST_CASE(TestGetBeginTimeIfProperTime)
        {
		BOOST_TEST(rent->getBeginTime() == bTime);
	}

	BOOST_AUTO_TEST_CASE(TestGetEndTimeIfRentedThenReturnsNotADateTime)
        {
		BOOST_TEST(rent->getEndTime() == pt::not_a_date_time);
	}

	BOOST_AUTO_TEST_CASE(TestGetEndTimeIfRentFinished)
        {
		pt::ptime now = pt::second_clock::local_time();
		rent->endRent(now);
		BOOST_TEST(rent->getEndTime() == now);
	}

	BOOST_AUTO_TEST_CASE(TestEndRentIfNotADateTime)
        {
		rent->endRent(pt::not_a_date_time);
		pt::ptime now = pt::second_clock::local_time();
		pt::time_period skew = pt::time_period(rent->getEndTime(), now);
		BOOST_TEST((skew.length().hours() == 0 && skew.length().minutes() == 0));
	}

	BOOST_AUTO_TEST_CASE(TestEndRentIfEarlierTimeThanBeginTimeThenEndTimeIsSetToBeginTime)
        {
		rent->endRent(rent->getBeginTime() - pt::hours(22));
		BOOST_TEST(rent->getEndTime() == rent->getBeginTime());
	}

	BOOST_AUTO_TEST_CASE(TestEndRentIfAlreadyEndedThenThrowsRentException)
        {
		pt::ptime now = pt::second_clock::local_time() + pt::hours(22);
		rent->endRent(now);
                BOOST_CHECK_THROW(rent->endRent(now - pt::hours(2)), RentException);
	}

	BOOST_AUTO_TEST_CASE(TestGetRentDaysIfNonEndedThenReturns0)
        {
		BOOST_TEST(rent->getRentDays() == 0);
	}

	BOOST_AUTO_TEST_CASE(TestGetRentDaysIfEndedBeforeOneMinElapsedThenReturns0)
        {
		rent->endRent(bTime + pt::seconds(59));
		BOOST_TEST(rent->getRentDays() == 0);
	}

	BOOST_AUTO_TEST_CASE(TestGetRentDaysIfEndedAfterExactlyOneMinThenReturns1)
        {
		rent->endRent(bTime + pt::minutes(1));
		BOOST_TEST(rent->getRentDays() == 1);
	}

	BOOST_AUTO_TEST_CASE(TestGetRentDaysIfEndedAfterAlmostOneDayThenReturns1)
        {
		rent->endRent(bTime + pt::hours(23) + pt::minutes(59));
		BOOST_TEST(rent->getRentDays() == 1);
	}

	BOOST_AUTO_TEST_CASE(TestGetRentDaysIfMultipleDaysThenReturnsTheCorrectNumberOfDays)
        {
		unsigned int days = 7;
		rent->endRent(bTime + pt::hours(24*days) - pt::minutes(2));
		BOOST_TEST(rent->getRentDays() == 7);
	}

	BOOST_AUTO_TEST_CASE(TestGetRentDaysIfExactlyOneDayThenReturns2)
        {
		rent->endRent(bTime + pt::hours(24));
		BOOST_TEST(rent->getRentDays() == 2);
	}

	BOOST_AUTO_TEST_CASE(TestGetRentCostIfZeroDaysThenReturns0)
        {
		rent->endRent(bTime);
		BOOST_TEST(rent->getRentCost() == 0);
	}

	BOOST_AUTO_TEST_CASE(TestGetRentCostIfSeveralDays)
        {
		unsigned int days = 11;
		rent->endRent(bTime + pt::hours(24*days) - pt::minutes(1));
		BOOST_TEST(rent->getRentCost() == days*pricePerDay);
	}

	BOOST_AUTO_TEST_CASE(TestGetRentCostIfCostIsPermanent)
        {
		rent->endRent(bTime + pt::hours(100));
		const double cost = rent->getRentCost();
		vehicle->setBasePrice(pricePerDay + 10000);
		BOOST_TEST(rent->getRentCost() == cost);
	}

	BOOST_AUTO_TEST_CASE(TestGetRentCostIfPlatinumClient)
        {
		auto clientType = std::make_shared<Platinum>();
		client->setClientType(clientType);
		rent->endRent(bTime + pt::hours(2));
		BOOST_TEST(rent->getRentCost() == 0.9*pricePerDay);
	}

BOOST_AUTO_TEST_SUITE_END()
