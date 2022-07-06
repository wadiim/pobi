#ifndef CLIENT_H
#define CLIENT_H

#include "typedefs.h"
#include "model/ClientType.h"

#include <string>
#include <vector>

class Client
{
	std::string firstName;
	std::string lastName;
	std::string personalId;
	AddressPtr address;
	ClientTypePtr clientType;
	bool archive;
public:
	Client() = delete;
	Client(std::string firstName, std::string lastName, std::string id, AddressPtr address);
	~Client() = default;

	const std::string &getFirstName() const;
	void setFirstName(const std::string &firstName);

	const std::string &getLastName() const;
	void setLastName(const std::string &lastName);

	const std::string &getPersonalId() const;
        const std::string &getId() const;

	AddressPtr getAddress();
	void setAddress(AddressPtr address);

	std::string getClientInfo() const;
        std::string getInfo() const;

	int getMaxVehicles() const;
	double applyDiscount(double price);
	void setClientType(const ClientTypePtr &clientType);

	bool isArchived() const;
	void setArchive(bool archive);
};

#endif // CLIENT_H
