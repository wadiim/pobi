#ifndef MOPED_H
#define MOPED_H

#include "MotorVehicle.h"

class Moped : public MotorVehicle
{
public:
	Moped() = delete;
	Moped(const std::string &plateNumber, unsigned int basePrice, unsigned int engineDisplacement);
	~Moped() override = default;
};

#endif // MOPED_H
