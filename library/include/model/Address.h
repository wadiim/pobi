#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

class Address {
	std::string city;
	std::string street;
	std::string number;
public:
	Address() = delete;
	Address(std::string city, std::string street, std::string number);
	~Address() = default;

	std::string getCity() const;
	std::string getStreet() const;
	std::string getNumber() const;
	std::string getAddressInfo() const;
};

#endif // ADDRESS_H
