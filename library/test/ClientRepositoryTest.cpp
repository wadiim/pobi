#include "repositories/ClientRepository.h"
#include "model/Client.h"
#include "model/Address.h"

#include <boost/test/unit_test.hpp>

#define NUM_OF_CLIENTS 3

struct TestSuiteClientRepositoryFixture
{
        AddressPtr address[NUM_OF_CLIENTS];
        ClientPtr client[NUM_OF_CLIENTS];
	ClientRepository *clientRepo;

        const std::string firstName[NUM_OF_CLIENTS] = { "Lain", "Reika", "Mika" };
        const std::string lastName[NUM_OF_CLIENTS] = { "Iwakura", "Yamamoto", "Iwakura" };
        const std::string id[NUM_OF_CLIENTS] = { "1094795585", "2105376125", "3200171710" };

	TestSuiteClientRepositoryFixture()
	{
		clientRepo = new ClientRepository();
                address[0] = std::make_shared<Address>("Tokyo", "Mimorigasaka", "2");
                address[1] = std::make_shared<Address>("Kyoto", "Kiyamachi", "16");
                address[2] = address[0];
                for (size_t i = 0; i < NUM_OF_CLIENTS; ++i)
                {
                        client[i] = std::make_shared<Client>(firstName[i], lastName[i], id[i], address[i]);
                }
	}

	~TestSuiteClientRepositoryFixture()
	{
		delete clientRepo;
	}
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteClientRepository, TestSuiteClientRepositoryFixture)

	BOOST_AUTO_TEST_CASE(TestGetClientIfNoClientsThenReturnsNull)
	{
		BOOST_TEST(clientRepo->getClient(0) == nullptr);
	}

	BOOST_AUTO_TEST_CASE(TestSizeIfNoClientsThenReturns0)
	{
		BOOST_TEST(clientRepo->size() == 0);
	}

	BOOST_AUTO_TEST_CASE(TestAddClientIfNullThenNoClientIsAdded)
	{
		clientRepo->addClient(nullptr);
		BOOST_TEST(clientRepo->size() == 0);
	}

	BOOST_AUTO_TEST_CASE(TestAddClientIfNoClientsWereAddedBeforeThenOnlyThatClientIsStored)
	{
		clientRepo->addClient(client[0]);
		BOOST_TEST(clientRepo->getClient(0) == client[0]);
	}

	BOOST_AUTO_TEST_CASE(TestAddClientIfAddingMultipleClientsThenAllOfThemAreStored)
	{
                for (auto &c : client) clientRepo->addClient(c);
                for (size_t i = 0; i < NUM_OF_CLIENTS; ++i) BOOST_TEST(clientRepo->getClient(i) == client[i]);
	}

	BOOST_AUTO_TEST_CASE(TestGetClientIfIncorrectIndexThenReturnsNull)
	{
		clientRepo->addClient(client[0]);
		BOOST_TEST(clientRepo->getClient(1) == nullptr);
	}

	BOOST_AUTO_TEST_CASE(TestSizeIfMultipleClientsWereAddedThenReturnsCorrectNumberOfClients)
	{
                for (auto &c : client) clientRepo->addClient(c);
		BOOST_TEST(clientRepo->size() == NUM_OF_CLIENTS);
	}

	BOOST_AUTO_TEST_CASE(TestRemoveClientIfNullThenNoClientsAreRemoved)
	{
		clientRepo->addClient(client[0]);
		clientRepo->removeClient(nullptr);
		BOOST_TEST(clientRepo->getClient(0) == client[0]);
	}

	BOOST_AUTO_TEST_CASE(TestRemoveClientIfCorrectPointerThenTheSpecifiedClientIsRemoved)
	{
		clientRepo->addClient(client[0]);
		clientRepo->removeClient(client[0]);
		BOOST_TEST(clientRepo->size() == 0);
	}

	BOOST_AUTO_TEST_CASE(TestRemoveClientIfMultipleClientsThenTheSizeIsDecremented)
	{
                for (auto &c : client) clientRepo->addClient(c);
		clientRepo->removeClient(client[1]);
		BOOST_TEST(clientRepo->size() == NUM_OF_CLIENTS - 1);
	}

	BOOST_AUTO_TEST_CASE(TestReportIfNoClientsThenReturnsEmptyString)
	{
		BOOST_TEST(clientRepo->report() == "");
	}

	BOOST_AUTO_TEST_CASE(TestReportIfMultipleClients)
	{
		clientRepo->addClient(client[0]);
		clientRepo->addClient(client[1]);
		BOOST_TEST(clientRepo->report() == client[0]->getClientInfo() + " " + client[1]->getClientInfo());
	}

	BOOST_AUTO_TEST_CASE(TestFindByIfOnlyOneMatchThenReturnsOnlyOneClient)
	{
                for (auto &c : client) clientRepo->addClient(c);
                const std::string fn = firstName[0];
		std::vector<ClientPtr> result = clientRepo->findBy([&fn](const ClientPtr &c) {
                        return c->getFirstName() == fn;
                });
		BOOST_TEST(result.size() == 1);
	}

        BOOST_AUTO_TEST_CASE(TestFindByIfOnlyOneMatchThenReturnsTheMatchingClient)
        {
                for (auto &c : client) clientRepo->addClient(c);
                const std::string fn = firstName[0];
                std::vector<ClientPtr> result = clientRepo->findBy([&fn](const ClientPtr &c) {
                        return c->getFirstName() == fn;
                });
                BOOST_TEST(result[0]->getFirstName() == fn);
        }

	BOOST_AUTO_TEST_CASE(TestFindByIfMultipleMatchesThenReturnsCorrectNumberOfClients)
	{
                for (auto &c : client) clientRepo->addClient(c);
                const std::string ln = lastName[0];
		std::vector<ClientPtr> result = clientRepo->findBy([&ln](const ClientPtr &c) {
                        return c->getLastName() == ln;
                });
		BOOST_TEST(result.size() == 2);
	}

        BOOST_AUTO_TEST_CASE(TestFindByIfMultipleMatchesThenReturnsTheMatchingClients)
        {
                for (auto &c : client) clientRepo->addClient(c);
                const std::string ln = lastName[0];
                std::vector<ClientPtr> result = clientRepo->findBy([&ln](const ClientPtr &c) {
                        return c->getLastName() == ln;
                });
                for (auto &r : result) BOOST_TEST(r->getLastName() == ln);
        }

        BOOST_AUTO_TEST_CASE(TestFindFirstIfNoMatchesThenReturnsNull)
        {
                for (auto &c : client) clientRepo->addClient(c);
                BOOST_TEST(clientRepo->findFirst([](const ClientPtr &c) {
                        return c->getFirstName() == "Naomi";
                }) == nullptr);
        }

        BOOST_AUTO_TEST_CASE(TestFindFirstIfSingleMatchThenReturnsNonNull)
        {
                for (auto &c : client) clientRepo->addClient(c);
                const std::string id_ = id[2];
                BOOST_TEST(clientRepo->findFirst([&id_](const ClientPtr &c) {
                        return c->getPersonalId() == id_;
                }) != nullptr);
        }

        BOOST_AUTO_TEST_CASE(TestFindFirstIfSingleMatchThenReturnsMatchingClient)
        {
                for (auto &c : client) clientRepo->addClient(c);
                const std::string id_ = id[2];
                BOOST_TEST(clientRepo->findFirst([&id_](const ClientPtr &c) {
                        return c->getPersonalId() == id_;
                })->getPersonalId() == id_);
        }

        BOOST_AUTO_TEST_CASE(TestFindFirstIfMultipleMatchesThenReturnsTheFirstOne)
        {
                for (auto &c : client) clientRepo->addClient(c);
                const std::string ln = lastName[0];
                BOOST_TEST(clientRepo->findFirst([&ln](const ClientPtr &c) {
                        return c->getLastName() == ln;
                })->getPersonalId() == client[0]->getPersonalId());
        }

        BOOST_AUTO_TEST_CASE(TestFindAllIfNoClientsThenReturnsEmptyContainer)
        {
                BOOST_TEST(clientRepo->findAll().size() == 0);
        }

	BOOST_AUTO_TEST_CASE(TestFindAllIfMultipleClientsThenReturnsCorrectNumberOfClients)
	{
                for (auto &c : client) clientRepo->addClient(c);
		std::vector<ClientPtr> result = clientRepo->findAll();
		BOOST_TEST(result.size() == clientRepo->size());
	}

        BOOST_AUTO_TEST_CASE(TestFindAllIfMultipleClientsThenReturnsAllClients)
        {
                for (auto &c : client) clientRepo->addClient(c);
                std::vector<ClientPtr> result = clientRepo->findAll();
                for (size_t i = 0; i < result.size(); ++i) BOOST_TEST(result[i] == clientRepo->getClient(i));
        }

	BOOST_AUTO_TEST_CASE(TestFindByPersonalIdIfIncorrectIdThenReturnsNull)
	{
                for (auto &c : client) clientRepo->addClient(c);
		BOOST_TEST(clientRepo->findByPersonalId("###") == nullptr);
	}

	BOOST_AUTO_TEST_CASE(TestFindByPersonalIdIfCorrectIdThenReturnsTheClientWithThatId)
	{
                for (auto &c : client) clientRepo->addClient(c);
		BOOST_TEST(clientRepo->findByPersonalId(id[1])->getPersonalId() == id[1]);
	}

BOOST_AUTO_TEST_SUITE_END()
