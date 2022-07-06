#include "predicates/FirstNamePredicate.h"
#include "model/Client.h"

FirstNamePredicate::FirstNamePredicate(const std::string &pattern)
        : pattern{pattern}
{
}

bool FirstNamePredicate::operator()(const ClientPtr &client) const
{
        return boost::regex_match(client->getFirstName(), pattern);
}