#ifndef CLIENT_TYPE_H
#define CLIENT_TYPE_H

#include <string>

class ClientType
{
public:
	ClientType() = default;
	virtual ~ClientType() = 0;

	virtual int getMaxVehicles() const = 0;
	virtual double applyDiscount(double price) = 0;
	virtual std::string getTypeInfo() const = 0;
};

class Default : public ClientType
{
public:
	int getMaxVehicles() const final;
	double applyDiscount(double price) final;
	std::string getTypeInfo() const final;
};

class Bronze : public ClientType
{
public:
	int getMaxVehicles() const final;
	double applyDiscount(double price) final;
	std::string getTypeInfo() const final;
};

class Silver : public ClientType
{
public:
	int getMaxVehicles() const final;
	double applyDiscount(double price) final;
	std::string getTypeInfo() const final;
};

class Gold : public ClientType
{
public:
	int getMaxVehicles() const final;
	double applyDiscount(double price) final;
	std::string getTypeInfo() const final;
};

class Platinum : public ClientType
{
public:
	int getMaxVehicles() const final;
	double applyDiscount(double price) final;
	std::string getTypeInfo() const final;
};

class Diamond : public ClientType
{
public:
	int getMaxVehicles() const final;
	double applyDiscount(double price) final;
	std::string getTypeInfo() const final;
};

#endif // CLIENT_TYPE_H
