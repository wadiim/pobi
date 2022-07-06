#include "predicates/LastNamePredicate.h"
#include "model/Client.h"

LastNamePredicate::LastNamePredicate(const std::string &pattern)
        : pattern{pattern}
{
}

bool LastNamePredicate::operator()(const ClientPtr &client) const
{
        return boost::regex_match(client->getLastName(), pattern);
}