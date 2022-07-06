#ifndef RENT_MANAGER_H
#define RENT_MANAGER_H

#include "typedefs.h"
#include "repositories/RentRepository.h"

#include <boost/date_time.hpp>

class RentManager
{
	RentRepository currentRents;
	RentRepository archiveRents;
public:
	RentManager() = default;
	~RentManager() = default;

	RentPtr rentVehicle(const ClientPtr &client, const VehiclePtr &vehicle, const boost::posix_time::ptime &beginTime);
	void returnVehicle(const VehiclePtr &vehicle);

	std::vector<RentPtr> getAllClientRents(const ClientPtr &client) const;
	RentPtr getVehicleRent(const VehiclePtr &vehicle) const;
        template<class P> std::vector<RentPtr> findRents(const P &predicate) const;
        std::vector<RentPtr> findAllRents() const;

	double checkClientRentBalance(const ClientPtr &client) const;
	void changeClientType(const ClientPtr &client);
};

template<class P>
std::vector<RentPtr> RentManager::findRents(const P &predicate) const
{
        return currentRents.findBy(predicate);
}

#endif // RENT_MANAGER_H
