#include "model/Moped.h"

Moped::Moped(const std::string &plateNumber, unsigned int basePrice, unsigned int engineDisplacement)
	: MotorVehicle(plateNumber, basePrice, engineDisplacement)
{
}