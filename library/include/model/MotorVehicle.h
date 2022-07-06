#ifndef MOTOR_VEHICLE_H
#define MOTOR_VEHICLE_H

#include "Vehicle.h"

class MotorVehicle : public Vehicle
{
	unsigned int engineDisplacement;
public:
	MotorVehicle() = delete;
	MotorVehicle(const std::string &plateNumber, unsigned int basePrice, unsigned int engineDisplacement);
	~MotorVehicle() override = 0;

	virtual unsigned int getEngineDisplacement() const;
	virtual void setEngineDisplacement(unsigned int engineDisplacement);

	double getActualRentalPrice() const override;

	std::string getVehicleInfo() const override;
};

#endif // MOTOR_VEHICLE_H
