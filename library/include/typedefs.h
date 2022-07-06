#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <memory>

class Address;
class Client;
class Rent;
class Vehicle;
class ClientType;

typedef std::shared_ptr<Address> AddressPtr;
typedef std::shared_ptr<Client> ClientPtr;
typedef std::shared_ptr<Rent> RentPtr;
typedef std::shared_ptr<Vehicle> VehiclePtr;
typedef std::shared_ptr<ClientType> ClientTypePtr;

#endif // TYPEDEFS_H
