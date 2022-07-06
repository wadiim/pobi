#include "model/Rent.h"
#include "model/Client.h"
#include "model/Vehicle.h"
#include "exceptions/RentException.h"

#include <sstream>
#include <utility>
#include <boost/uuid/uuid_io.hpp>

namespace pt = boost::posix_time;

Rent::Rent(ClientPtr client, VehiclePtr vehicle, const pt::ptime &beginTime)
	: id{boost::uuids::random_generator()()}, client{std::move(client)}, vehicle{std::move(vehicle)}, endTime{pt::not_a_date_time}
{
	if (beginTime == pt::not_a_date_time)
	{
		this->beginTime = pt::second_clock::local_time();
	}
	else
	{
		this->beginTime = beginTime;
	}
}

std::string Rent::getId() const
{
	return boost::uuids::to_string(id);
}

ClientPtr Rent::getClient() const
{
	return client;
}

VehiclePtr Rent::getVehicle() const
{
	return vehicle;
}

std::string Rent::getRentInfo() const
{
	std::stringstream ss;
	ss << id << " " << client->getClientInfo() << " " << vehicle->getVehicleInfo()
		<< " " << beginTime;
	if (endTime != pt::not_a_date_time)
	{
		ss << " " << endTime;
	}
	return ss.str();
}

std::string Rent::getInfo() const
{
        return std::move(getRentInfo());
}

unsigned int Rent::getRentDays() const
{
	if (endTime == pt::not_a_date_time)
	{
		return 0;
	}
	pt::time_period period(beginTime, endTime);
	if (period.length().minutes() < 1 && period.length().hours() == 0)
	{
		return 0;
	}
	return (period.length().hours() / 24) + 1;
}

const pt::ptime &Rent::getBeginTime() const
{
	return beginTime;
}

const pt::ptime &Rent::getEndTime() const
{
	return endTime;
}

void Rent::endRent(const pt::ptime &endTime)
{
	if (this->endTime != pt::not_a_date_time)
	{
		throw RentException("The rent has already ended");
	}
	else if (endTime == pt::not_a_date_time)
	{
		this->endTime = pt::second_clock::local_time();
	}
	else if (endTime < beginTime)
	{
		this->endTime = beginTime;
	}
	else
	{
		this->endTime = endTime;
	}
	rentCost = client->applyDiscount(getRentDays()*vehicle->getBasePrice());
}

double Rent::getRentCost() const
{
	return rentCost;
}
