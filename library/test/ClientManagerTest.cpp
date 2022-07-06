#include "managers/ClientManager.h"
#include "model/Client.h"
#include "model/Address.h"

#include <boost/test/unit_test.hpp>

struct TestSuiteClientManagerFixture
{
        static const int NUM_OF_CLIENTS = 3;
	AddressPtr address[NUM_OF_CLIENTS];
        ClientPtr client[NUM_OF_CLIENTS];
	ClientManager *clientManager;

        const std::string firstName[NUM_OF_CLIENTS] = { "Lain", "Reika", "Mika" };
        const std::string lastName[NUM_OF_CLIENTS] = { "Iwakura", "Yamamoto", "Iwakura" };
        const std::string id[NUM_OF_CLIENTS] = { "1094795585", "2105376125", "3200171710" };

	TestSuiteClientManagerFixture()
	{
                clientManager = new ClientManager();
                address[0] = std::make_shared<Address>("Tokyo", "Mimorigasaka", "2");
		address[1] = std::make_shared<Address>("Kyoto", "Kiyamachi", "16");
                address[2] = address[0];
                for (size_t i = 0; i < NUM_OF_CLIENTS; ++i)
                {
                        client[i] = clientManager->registerClient(firstName[i], lastName[i], id[i], address[i]);
                }
	}

	~TestSuiteClientManagerFixture()
	{
		delete clientManager;
	}
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteClientManager, TestSuiteClientManagerFixture)

	BOOST_AUTO_TEST_CASE(TestGetClientIfNoClientsThenReturnsNull)
	{
                auto emptyClientManager = std::make_shared<ClientManager>();
		BOOST_TEST(emptyClientManager->getClient("0") == nullptr);
	}

	BOOST_AUTO_TEST_CASE(TestRegisterClientIfCorrectIdThenReturnsNonNull)
	{
		BOOST_TEST(client[0] != nullptr);
	}

        BOOST_AUTO_TEST_CASE(TestRegisterClientIfCorrectIdThenSetsFirstNameCorrectly)
        {
                BOOST_TEST(client[0]->getFirstName() == firstName[0]);
        }

        BOOST_AUTO_TEST_CASE(TestRegisterClientIfCorrectIdThenSetsTheLastNameCorrectly)
        {
                BOOST_TEST(client[0]->getLastName() == lastName[0]);
        }

        BOOST_AUTO_TEST_CASE(TestRegisterClientIfCorrectIdThenSetsTheIdCorrectly)
        {
                BOOST_TEST(client[0]->getPersonalId() == id[0]);
        }

        BOOST_AUTO_TEST_CASE(TestRegisterClientIfCorrectIdThenSetsTheAddressCorrectly)
        {
                BOOST_TEST(client[0]->getAddress() == address[0]);
        }

	BOOST_AUTO_TEST_CASE(TestRegisterClientIfDuplicatedIdThenReturnsPointerToAlreadyRegisteredClient)
	{
		BOOST_TEST(clientManager->registerClient("Masami", "Eiri", id[0], address[0]) == client[0]);
	}

	BOOST_AUTO_TEST_CASE(TestGetClientIfIncorrectIdThenReturnsNull)
	{
		BOOST_TEST(clientManager->getClient("-1") == nullptr);
	}

	BOOST_AUTO_TEST_CASE(TestGetClientIfCorrectIdThenReturnsClientWithThatId)
	{
		BOOST_TEST(clientManager->getClient(id[0]) == client[0]);
	}

	BOOST_AUTO_TEST_CASE(TestUnregisterClientIfCorrectIdThenArchiveThatClient)
	{
		clientManager->unregisterClient(id[0]);
		BOOST_TEST(clientManager->getClient(id[0])->isArchived() == true);
	}

        BOOST_AUTO_TEST_CASE(TestFindClientsIfNoClientMeetsTheCriteriaThenReturnsNoClients)
        {
                BOOST_TEST(clientManager->findClients([](const ClientPtr &c) {
                        return false;
                }).empty() == true);
        }

        BOOST_AUTO_TEST_CASE(TestFindClientsIfAllClientsHaveBeenUnregisteredThenReturnsNoClients)
        {
                for (const auto & i : id) clientManager->unregisterClient(i);
                BOOST_TEST(clientManager->findClients([](const ClientPtr &c) {
                        return true;
                }).empty() == true);
        }

        BOOST_AUTO_TEST_CASE(TestFindClietsIfSingleClientMeetsTheCriteriaThenReturnsSingleClient)
        {
                const std::string id_ = id[0];
                BOOST_TEST(clientManager->findClients([&id_](const ClientPtr &c) {
                        return c->getPersonalId() == id_;
                }).size() == 1);
        }

        BOOST_AUTO_TEST_CASE(TestFindClietsIfSingleClientsMeetTheCriteriaThenReturnsCorrectClient)
        {
                const std::string id_ = id[0];
                BOOST_TEST(clientManager->findClients([&id_](const ClientPtr &c) {
                        return c->getPersonalId() == id_;
                }).back()->getPersonalId() == id_);
        }

        BOOST_AUTO_TEST_CASE(TestFindClientsIfMultipleClientsMeetTheCriteriaThenReturnsCorrectNumberOfClients)
        {
                const std::string ln = lastName[0];
                BOOST_TEST(clientManager->findClients([&ln](const ClientPtr &c) {
                        return c->getLastName() == ln;
                }).size() == 2);
        }

        BOOST_AUTO_TEST_CASE(TestFindClientsIfMultipleClientsMeetTheCriteriaThenReturnsCorrectClients)
        {
                const std::string ln = lastName[0];
                auto result = clientManager->findClients([&ln](const ClientPtr &c) {
                        return c->getLastName() == ln;
                });
                for (const auto &r : result) BOOST_TEST(r->getLastName() == ln);
        }

        BOOST_AUTO_TEST_CASE(TestFindClientsIfOneOfTheClientsHasBeenUnregisteredThenReturnsOneClientLess)
        {
                clientManager->unregisterClient(id[0]);
                const std::string ln = lastName[0];
                BOOST_TEST(clientManager->findClients([&ln](const ClientPtr &c) {
                        return c->getLastName() == ln;
                }).size() == 1);
        }

        BOOST_AUTO_TEST_CASE(TestFindClientsIfOneOfTheClientsHasBeenUnregisteredThenThatClientIsNotReturned)
        {
                clientManager->unregisterClient(id[0]);
                const std::string ln = lastName[0];
                BOOST_TEST(clientManager->findClients([&ln](const ClientPtr &c) {
                        return c->getLastName() == ln;
                }).back()->getPersonalId() != id[0]);
        }

        BOOST_AUTO_TEST_CASE(TestFindAllClientsIfNoClientsThenReturnsEmptyCointainer)
        {
                auto emptyClientManager = std::make_shared<ClientManager>();
                BOOST_TEST(emptyClientManager->findAllClients().empty() == true);
        }

        BOOST_AUTO_TEST_CASE(TestFindAllClientsIfAllOfTheClientsHaveBeenUnregisteredThenReturnsNoClients)
        {
                for (const auto & i : id) clientManager->unregisterClient(i);
                BOOST_TEST(clientManager->findAllClients().empty() == true);
        }

        BOOST_AUTO_TEST_CASE(TestFindAllClientsIfMultipleClientsThenReturnsCorrectNumberOfClients)
        {
                BOOST_TEST(clientManager->findAllClients().size() == 3);
        }

        BOOST_AUTO_TEST_CASE(TestFindAllClientsIfMultipleClientsThenReturnsAllClients)
        {
                auto result = clientManager->findAllClients();
                for (size_t i = 0; i < NUM_OF_CLIENTS; ++i) BOOST_TEST(result[i] == client[i]);
        }

        BOOST_AUTO_TEST_CASE(TestFindAllClientsIfOneOfTheClientsHasBeenUnregisteredThenReturnsOneClientLess)
        {
                clientManager->unregisterClient(id[2]);
                BOOST_TEST(clientManager->findAllClients().size() == 2);
        }

        BOOST_AUTO_TEST_CASE(TestFindAllClientsIfOneOfTheClientsHasBeenUnregisteredThenThatClientIsNotReturned)
        {
                clientManager->unregisterClient(id[2]);
                auto result = clientManager->findAllClients();
                for (auto & i : result) BOOST_TEST(i->getId() != id[2]);
        }

BOOST_AUTO_TEST_SUITE_END()
