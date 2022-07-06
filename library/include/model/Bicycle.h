#ifndef BICYCLE_H
#define BICYCLE_H

#include "Vehicle.h"

class Bicycle : public Vehicle
{
public:
	Bicycle() = delete;
	Bicycle(const std::string &plateNumber, unsigned int basePrice);
	~Bicycle() override = default;
};

#endif // BICYCLE_H
