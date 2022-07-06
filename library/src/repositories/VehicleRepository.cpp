#include "repositories/VehicleRepository.h"
#include "model/Vehicle.h"

VehiclePtr VehicleRepository::getVehicle(size_t index)
{
	return get(index);
}

void VehicleRepository::addVehicle(VehiclePtr vehicle)
{
	add(std::move(vehicle));
}

void VehicleRepository::removeVehicle(VehiclePtr vehicle)
{
	remove(std::move(vehicle));
}

VehiclePtr VehicleRepository::findByPlateNumber(const std::string &plateNumber) const
{
        return findFirst([&plateNumber](const VehiclePtr &v) {
                return v->getPlateNumber() == plateNumber;
        });
}
