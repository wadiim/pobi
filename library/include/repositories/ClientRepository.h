#ifndef CLIENT_REPOSITORY_H
#define CLIENT_REPOSITORY_H

#include "typedefs.h"
#include "repositories/Repository.h"

class ClientRepository : public Repository<Client>
{
public:
	ClientRepository() = default;
	~ClientRepository() override = default;

	ClientPtr getClient(size_t index) const;
	void addClient(ClientPtr client);
	void removeClient(ClientPtr client);

	ClientPtr findByPersonalId(const std::string &id) const;
};

#endif // CLIENT_REPOSITORY_H
