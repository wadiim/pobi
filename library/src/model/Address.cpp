#include "model/Address.h"

Address::Address(std::string city, std::string street, std::string number)
	: city{std::move(city)}, street{std::move(street)}, number{std::move(number)}
{
}

std::string Address::getCity() const
{
	return city;
}

std::string Address::getStreet() const
{
	return street;
}

std::string Address::getNumber() const
{
	return number;
}

std::string Address::getAddressInfo() const
{
	return city + " " + street + " " + number;
}
