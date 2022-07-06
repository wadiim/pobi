#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

class Vehicle
{
	std::string plateNumber;
	unsigned int basePrice;
	bool archive;
public:
	Vehicle() = delete;
	Vehicle(std::string plateNumber, unsigned int basePrice);
	virtual ~Vehicle() = 0;

        virtual const std::string &getId() const;
	virtual const std::string &getPlateNumber() const;
	virtual void setPlateNumber(const std::string &plateNumber);

	virtual unsigned int getBasePrice() const;
	virtual void setBasePrice(unsigned int basePrice);

	virtual double getActualRentalPrice() const;

	virtual std::string getVehicleInfo() const;
        virtual std::string getInfo() const;

	virtual bool isArchived() const;
	virtual void setArchive(bool archive);
};

#endif // VEHICLE_H
