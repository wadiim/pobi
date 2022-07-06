#include "managers/RentManager.h"
#include "model/Client.h"
#include "model/Vehicle.h"
#include "model/Rent.h"

namespace pt = boost::posix_time;

RentPtr RentManager::rentVehicle(const ClientPtr &client, const VehiclePtr &vehicle, const boost::posix_time::ptime &beginTime)
{
        if (client->isArchived() || vehicle->isArchived() || getAllClientRents(client).size() >= client->getMaxVehicles()
            || getVehicleRent(vehicle))
        {
                return nullptr;
        }
        auto rent = std::make_shared<Rent>(client, vehicle, beginTime);
        currentRents.addRent(rent);
        return rent;
}

void RentManager::returnVehicle(const VehiclePtr &vehicle)
{
        auto rent = getVehicleRent(vehicle);
        rent->endRent(pt::second_clock::local_time());
        archiveRents.addRent(rent);
        currentRents.removeRent(rent);
        vehicle->setArchive(true);
        changeClientType(rent->getClient());
}

std::vector<RentPtr> RentManager::getAllClientRents(const ClientPtr &client) const
{
        return findRents([&client](const RentPtr &r) { return r->getClient() == client; });
}

RentPtr RentManager::getVehicleRent(const VehiclePtr &vehicle) const
{
        auto rents = findRents([&vehicle](const RentPtr &r) { return r->getVehicle() == vehicle; });
        return (rents.empty()) ? nullptr : rents.back();
}

std::vector<RentPtr> RentManager::findAllRents() const
{
        return findRents([](const RentPtr &r) { return true; });
}

double RentManager::checkClientRentBalance(const ClientPtr &client) const
{
        auto rents = archiveRents.findBy([&client](const RentPtr &r) { return r->getClient() == client; });
        double cost = 0.0;
        for (const auto &r : rents)
        {
                cost += r->getRentCost();
        }
        return cost;
}

void RentManager::changeClientType(const ClientPtr &client)
{
        double balance = checkClientRentBalance(client);
        if (balance >= 1600.0) client->setClientType(std::make_shared<Diamond>());
        else if (balance >= 800.0) client->setClientType(std::make_shared<Platinum>());
        else if (balance >= 400.0) client->setClientType(std::make_shared<Gold>());
        else if (balance >= 200.0) client->setClientType(std::make_shared<Silver>());
        else if (balance >= 100.0) client->setClientType(std::make_shared<Bronze>());
        else client->setClientType(std::make_shared<Default>());
}