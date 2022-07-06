#ifndef CAR_H
#define CAR_H

#include "MotorVehicle.h"

enum SegmentType { A = 10, B, C, D, E };

class Car : public MotorVehicle
{
	SegmentType segment;
public:
	Car() = delete;
	Car(const std::string &plateNumber, unsigned int basePrice, unsigned int engineDisplacement, SegmentType segment);
	~Car() override = default;

	SegmentType getSegment() const;
	void setSegment(SegmentType segment);

	double getActualRentalPrice() const override;

	std::string getVehicleInfo() const override;
};

#endif // CAR_H
