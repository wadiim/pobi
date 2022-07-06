#include "model/ClientType.h"

ClientType::~ClientType() = default;

int Default::getMaxVehicles() const
{
	return 1;
}

double Default::applyDiscount(double price)
{
	return price;
}

std::string Default::getTypeInfo() const
{
	return "Default 1 $0.00";
}

int Bronze::getMaxVehicles() const
{
	return 2;
}

double Bronze::applyDiscount(double price)
{
	double discount = 3.0;
	return (price > discount) ? price - discount : price;
}

std::string Bronze::getTypeInfo() const
{
	return "Bronze 2 $3.00";
}

int Silver::getMaxVehicles() const
{
	return 3;
}

double Silver::applyDiscount(double price)
{
	double discount = 6.0;
	return (price > discount) ? price - discount : price;
}

std::string Silver::getTypeInfo() const
{
	return "Silver 3 $6.00";
}

int Gold::getMaxVehicles() const
{
	return 4;
}

double Gold::applyDiscount(double price)
{
	double percent = 0.95;
	return price * percent;
}

std::string Gold::getTypeInfo() const
{
	return "Gold 4 5%";
}

int Platinum::getMaxVehicles() const
{
	return 5;
}

double Platinum::applyDiscount(double price)
{
	double percent = 0.9;
	return price * percent;
}

std::string Platinum::getTypeInfo() const
{
	return "Platinum 5 10%";
}

int Diamond::getMaxVehicles() const
{
	return 10;
}

double Diamond::applyDiscount(double price)
{
	if (price > 500.0) return 0.6 * price;
	else if (price > 250.0) return 0.7 * price;
	else if (price > 125.0) return 0.8 * price;
	else return 0.9 * price;
}

std::string Diamond::getTypeInfo() const
{
	return "Diamond 10 10%/20%/30%/40%";
}
