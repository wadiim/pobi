#include "model/Vehicle.h"
#include "exceptions/VehicleException.h"

#include <sstream>
#include <utility>

Vehicle::Vehicle(std::string plateNumber, unsigned int basePrice)
	: plateNumber{std::move(plateNumber)}, basePrice{basePrice}, archive{false}
{
}

Vehicle::~Vehicle() = default;

const std::string &Vehicle::getPlateNumber() const
{
	return plateNumber;
}

const std::string &Vehicle::getId() const
{
        return getPlateNumber();
}

void Vehicle::setPlateNumber(const std::string &plateNumber)
{
        if (plateNumber.empty()) throw VehicleException("Plate number was not provided");
	this->plateNumber = plateNumber;
}

unsigned int Vehicle::getBasePrice() const
{
	return basePrice;
}

void Vehicle::setBasePrice(unsigned int basePrice)
{
	this->basePrice = basePrice;
}

double Vehicle::getActualRentalPrice() const
{
	return static_cast<double>(getBasePrice());
}

std::string Vehicle::getVehicleInfo() const
{
	std::stringstream ss;
	ss << plateNumber << " " << basePrice;
	return ss.str();
}

std::string Vehicle::getInfo() const
{
        return std::move(getVehicleInfo());
}

bool Vehicle::isArchived() const
{
	return archive;
}

void Vehicle::setArchive(bool archive)
{
	this->archive = archive;
}
