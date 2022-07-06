#ifndef VEHICLE_MANAGER_H
#define VEHICLE_MANAGER_H

#include "typedefs.h"
#include "repositories/VehicleRepository.h"
#include "model/Car.h"

#include <string>

class VehicleManager
{
	VehicleRepository vehicleRepository;
public:
	VehicleManager() = default;
	~VehicleManager() = default;

	VehiclePtr getVehicle(const std::string &plateNumber) const;
	VehiclePtr registerBicycle(const std::string &plateNumber, unsigned int basePrice);
	VehiclePtr registerMoped(const std::string &plateNumber, unsigned int basePrice, unsigned int engineDisplacement);
	VehiclePtr registerCar(const std::string &plateNumber, unsigned int basePrice, unsigned int engineDisplacement, SegmentType segment);
	void unregisterVehicle(const std::string &plateNumber);
	template<class P> std::vector<VehiclePtr> findVehicles(const P &predicate) const;
	std::vector<VehiclePtr> findAllVehicles() const;
};

template<class P>
std::vector<VehiclePtr> VehicleManager::findVehicles(const P &predicate) const
{
        auto temp = vehicleRepository.findBy(predicate);
        auto result = std::vector<VehiclePtr>();
        std::copy_if(temp.begin(), temp.end(), std::back_inserter(result), [](const VehiclePtr &v) {
                return !v->isArchived();
        });
        return result;
}

#endif // VEHICLE_MANAGER_H
