#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include "typedefs.h"
#include "model/Client.h"
#include "repositories/ClientRepository.h"

#include <string>

class ClientManager
{
	ClientRepository clientRepository;
public:
	ClientManager() = default;
	~ClientManager() = default;

	ClientPtr getClient(const std::string &id) const;
	ClientPtr registerClient(const std::string &firstName, const std::string &lastName, const std::string &id, const AddressPtr &address);
	void unregisterClient(const std::string &id);
        template<class P> std::vector<ClientPtr> findClients(const P &predicate) const;
	std::vector<ClientPtr> findAllClients() const;
};

template<class P>
std::vector<ClientPtr> ClientManager::findClients(const P &predicate) const
{
        auto temp = clientRepository.findBy(predicate);
        auto result = std::vector<ClientPtr>();
        std::copy_if(temp.begin(), temp.end(), std::back_inserter(result), [](const ClientPtr &c) {
                return !c->isArchived();
        });
        return result;
}

#endif // CLIENT_MANAGER_H
