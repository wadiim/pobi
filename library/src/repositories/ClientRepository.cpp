#include "repositories/ClientRepository.h"
#include "model/Client.h"

ClientPtr ClientRepository::getClient(size_t index) const
{
	return get(index);
}

void ClientRepository::addClient(ClientPtr client)
{
	add(std::move(client));
}

void ClientRepository::removeClient(ClientPtr client)
{
	remove(std::move(client));
}

ClientPtr ClientRepository::findByPersonalId(const std::string &id) const
{
	return findFirst([&id](const ClientPtr &c) {
                return c->getPersonalId() == id;
        });
}
