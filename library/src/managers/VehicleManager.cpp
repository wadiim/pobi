#include "managers/VehicleManager.h"
#include "model/Bicycle.h"
#include "model/Moped.h"
#include "model/Car.h"

VehiclePtr VehicleManager::getVehicle(const std::string &plateNumber) const
{
	return vehicleRepository.findByPlateNumber(plateNumber);
}

VehiclePtr VehicleManager::registerBicycle(const std::string &plateNumber, unsigned int basePrice)
{
	auto temp = getVehicle(plateNumber);
	if (temp) return temp;
	VehiclePtr newVehicle = std::make_shared<Bicycle>(plateNumber, basePrice);
	vehicleRepository.addVehicle(newVehicle);
	return newVehicle;
}

VehiclePtr VehicleManager::registerMoped(const std::string &plateNumber, unsigned int basePrice, unsigned int engineDisplacement)
{
	auto temp = getVehicle(plateNumber);
	if (temp) return temp;
	VehiclePtr newVehicle = std::make_shared<Moped>(plateNumber, basePrice, engineDisplacement);
	vehicleRepository.addVehicle(newVehicle);
	return newVehicle;
}

VehiclePtr VehicleManager::registerCar(const std::string &plateNumber, unsigned int basePrice, unsigned int engineDisplacement, SegmentType segment)
{
	auto temp = getVehicle(plateNumber);
	if (temp) return temp;
	VehiclePtr newVehicle = std::make_shared<Car>(plateNumber, basePrice, engineDisplacement, segment);
	vehicleRepository.addVehicle(newVehicle);
	return newVehicle;
}

void VehicleManager::unregisterVehicle(const std::string &plateNumber)
{
	auto vehicle = getVehicle(plateNumber);
	if (vehicle) vehicle->setArchive(true);
}

std::vector<VehiclePtr> VehicleManager::findAllVehicles() const
{
	return findVehicles([](const VehiclePtr &v) { return true; });
}
