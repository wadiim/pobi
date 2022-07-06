#ifndef VEHICLE_REPOSITORY_H
#define VEHICLE_REPOSITORY_H

#include "typedefs.h"
#include "repositories/Repository.h"

class VehicleRepository : public Repository<Vehicle>
{
public:
	VehicleRepository() = default;
	~VehicleRepository() override = default;

	VehiclePtr getVehicle(size_t index);
	void addVehicle(VehiclePtr vehicle);
	void removeVehicle(VehiclePtr vehicle);

	VehiclePtr findByPlateNumber(const std::string &plateNumber) const;
};

#endif // VEHICLE_REPOSITORY_H
