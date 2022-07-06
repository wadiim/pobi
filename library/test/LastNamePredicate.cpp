#include "predicates/LastNamePredicate.h"
#include "model/Address.h"
#include "model/Client.h"

#include <boost/test/unit_test.hpp>
#include <memory>

class TestSuiteLastNamePredicateFixture
{
public:
        ClientPtr client;

        TestSuiteLastNamePredicateFixture()
        {
                client = std::make_shared<Client>("Lain", "Iwakura", "1094795585", nullptr);
        }
};

BOOST_FIXTURE_TEST_SUITE(TestLastNamePredicate, TestSuiteLastNamePredicateFixture)

        BOOST_AUTO_TEST_CASE(TestLastNamePredicateIfInitializedWithClientNameThenReturnsTrue)
        {
                LastNamePredicate predicate{"Iwakura"};
                BOOST_TEST(predicate(client) == true);
        }

        BOOST_AUTO_TEST_CASE(TestLastNamePredicateIfInitializedWithNonMatchingNameThenReturnsFalse)
        {
                LastNamePredicate predicate{"Mizuki"};
                BOOST_TEST(predicate(client) == false);
        }

        BOOST_AUTO_TEST_CASE(TestLastNamePredicateIfInitializedWithMatchingRegexThenReturnsTrue)
        {
                LastNamePredicate predicate{"I-?wa-?ku-?ra"};
                BOOST_TEST(predicate(client) == true);
        }

        BOOST_AUTO_TEST_CASE(TestLastNamePredicateIfInitializedWithNonMatchingRegexThenReturnsFalse)
        {
                LastNamePredicate predicate{"([0-9]+)(\\-| |$)(.*)"};
                BOOST_TEST(predicate(client) == false);
        }

BOOST_AUTO_TEST_SUITE_END()