#ifndef LAST_NAME_PREDICATE_H
#define LAST_NAME_PREDICATE_H

#include "typedefs.h"

#include <string>
#include <boost/regex.hpp>

class LastNamePredicate
{
        boost::regex pattern;
public:
        explicit LastNamePredicate(const std::string &pattern);

        bool operator()(const ClientPtr &client) const;
};

#endif // LAST_NAME_PREDICATE_H
