#include "model/Car.h"

#include <sstream>

Car::Car(const std::string &plateNumber, unsigned int basePrice, unsigned int engineDisplacement, SegmentType segment)
	: MotorVehicle(plateNumber, basePrice, engineDisplacement), segment{segment}
{
}

SegmentType Car::getSegment() const
{
	return segment;
}

void Car::setSegment(SegmentType segment)
{
	this->segment = segment;
}

double Car::getActualRentalPrice() const
{
	return getBasePrice() * (segment / 10.0);
}

std::string Car::getVehicleInfo() const
{
	std::stringstream ss;
	ss << MotorVehicle::getVehicleInfo() << " " << segment;
	return ss.str();
}