#include "managers/ClientManager.h"
#include "model/Client.h"

ClientPtr ClientManager::getClient(const std::string &id) const
{
	return clientRepository.findByPersonalId(id);
}

ClientPtr ClientManager::registerClient(const std::string &firstName, const std::string &lastName, const std::string &id, const AddressPtr &address)
{
	auto temp = getClient(id);
	if (temp) return temp;
	auto newClient = std::make_shared<Client>(firstName, lastName, id, address);
	clientRepository.addClient(newClient);
	return newClient;
}

void ClientManager::unregisterClient(const std::string &id)
{
	auto client = getClient(id);
	if (client) client->setArchive(true);
}

std::vector<ClientPtr> ClientManager::findAllClients() const
{
	return findClients([](const ClientPtr &c) { return true; });
}
