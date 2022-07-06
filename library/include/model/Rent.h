#ifndef RENT_H
#define RENT_H

#include "typedefs.h"

#include <string>
#include <boost/date_time.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

class Rent
{
        boost::uuids::uuid id;
	ClientPtr client;
	VehiclePtr vehicle;
	boost::posix_time::ptime beginTime;
	boost::posix_time::ptime endTime;
	double rentCost = 0.0;
public:
	Rent() = delete;
	Rent(ClientPtr client, VehiclePtr vehicle, const boost::posix_time::ptime &beginTime);
	~Rent() = default;

	std::string getId() const;
	ClientPtr getClient() const;
	VehiclePtr getVehicle() const;
	std::string getRentInfo() const;
        std::string getInfo() const;

	unsigned int getRentDays() const;
	const boost::posix_time::ptime &getBeginTime() const;
	const boost::posix_time::ptime &getEndTime() const;
	void endRent(const boost::posix_time::ptime &endTime);

	double getRentCost() const;
};

#endif // RENT_H
