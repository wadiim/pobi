#include "model/Client.h"
#include "model/Address.h"
#include "model/Rent.h"
#include "exceptions/ClientException.h"

#include <sstream>
#include <utility>

Client::Client(std::string firstName, std::string lastName, std::string id, AddressPtr address)
	: firstName{std::move(firstName)}, lastName{std::move(lastName)}, personalId{std::move(id)}, address{std::move(address)}, archive{false}
{
	clientType = std::make_shared<Default>();
}

const std::string &Client::getFirstName() const
{
	return firstName;
}

void Client::setFirstName(const std::string &firstName)
{
	if (firstName.empty()) throw ClientException("First name was not provided");
        this->firstName = firstName;
}

const std::string &Client::getLastName() const
{
	return lastName;
}

void Client::setLastName(const std::string &lastName)
{
	if (lastName.empty()) throw ClientException("Last name was not provided");
        this->lastName = lastName;
}

const std::string &Client::getPersonalId() const
{
	return personalId;
}

const std::string &Client::getId() const
{
        return getPersonalId();
}

AddressPtr Client::getAddress()
{
	return address;
}

void Client::setAddress(AddressPtr address)
{
	if (address == nullptr) throw ClientException("Address was not provided");
        this->address = address;
}

std::string Client::getClientInfo() const
{
	std::stringstream ss;
	ss << firstName << " " << lastName << " " << personalId << " "
		<< address->getAddressInfo() <<  " " << clientType->getTypeInfo();
	return ss.str();
}

std::string Client::getInfo() const
{
        return std::move(getClientInfo());
}

int Client::getMaxVehicles() const
{
	return clientType->getMaxVehicles();
}

double Client::applyDiscount(double price)
{
	return clientType->applyDiscount(price);
}

void Client::setClientType(const ClientTypePtr &clientType)
{
	this->clientType = clientType;
}

bool Client::isArchived() const
{
	return archive;
}

void Client::setArchive(bool archive)
{
	this->archive = archive;
}
