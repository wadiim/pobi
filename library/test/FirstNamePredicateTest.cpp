#include "predicates/FirstNamePredicate.h"
#include "model/Address.h"
#include "model/Client.h"

#include <boost/test/unit_test.hpp>
#include <memory>

class TestSuiteFirstNamePredicateFixture
{
public:
        ClientPtr client;

        TestSuiteFirstNamePredicateFixture()
        {
                client = std::make_shared<Client>("Lain", "Iwakura", "1094795585", nullptr);
        }
};

BOOST_FIXTURE_TEST_SUITE(TestFirstNamePredicate, TestSuiteFirstNamePredicateFixture)

        BOOST_AUTO_TEST_CASE(TestFirstNamePredicateIfInitializedWithClientNameThenReturnsTrue)
        {
                FirstNamePredicate predicate{"Lain"};
                BOOST_TEST(predicate(client) == true);
        }

        BOOST_AUTO_TEST_CASE(TestFirstNamePredicateIfInitializedWithNonMatchingNameThenReturnsFalse)
        {
                FirstNamePredicate predicate{"Ryuk"};
                BOOST_TEST(predicate(client) == false);
        }

        BOOST_AUTO_TEST_CASE(TestFirstNamePredicateIfInitializedWithMatchingRegexThenReturnsTrue)
        {
                FirstNamePredicate predicate{"(La|Re)in"};
                BOOST_TEST(predicate(client) == true);
        }

        BOOST_AUTO_TEST_CASE(TestFirstNamePredicateIfInitializedWithNonMatchingRegexThenReturnsFalse)
        {
                FirstNamePredicate predicate{"([0-9]+)(\\-| |$)(.*)"};
                BOOST_TEST(predicate(client) == false);
        }

BOOST_AUTO_TEST_SUITE_END()