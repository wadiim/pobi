#include "model/MotorVehicle.h"

#include <sstream>

MotorVehicle::MotorVehicle(const std::string &plateNumber, unsigned int basePrice, unsigned int engineDisplacement)
	: Vehicle(plateNumber, basePrice), engineDisplacement{engineDisplacement}
{
}

MotorVehicle::~MotorVehicle() = default;

unsigned int MotorVehicle::getEngineDisplacement() const
{
	return engineDisplacement;
}

void MotorVehicle::setEngineDisplacement(unsigned int engineDisplacement)
{
	this->engineDisplacement = engineDisplacement;
}

double MotorVehicle::getActualRentalPrice() const
{
	auto rentalPrice = static_cast<double>(getBasePrice());
	if (engineDisplacement > 2000)
	{
		rentalPrice *= 1.5;
	}
	else if (engineDisplacement > 1000)
	{
		rentalPrice *= (engineDisplacement*0.5)/1000.0 + 0.5;
	}
	return rentalPrice;
}

std::string MotorVehicle::getVehicleInfo() const
{
	std::stringstream ss;
	ss << Vehicle::getVehicleInfo() << " " << engineDisplacement;
	return ss.str();
}